#include "ashopenglwidget.h"
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QtMath>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>

//继承自QOpenGlWidget
//用于显示OpenGl的内容
//xtrans(0.0)：x轴平移值
//ytrans(0.0)：y轴平移值
//ztrans(0.0)：z轴平移值

ASHOpenglWidget::ASHOpenglWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    //,VBO(QOpenGLBuffer::VertexBuffer)
    ,xtrans(0.0),ytrans(0.0),ztrans(0.0)
{
    // 创建一个 Surface 格式对象
    QSurfaceFormat format;

    //设置alpha缓冲大小
    format.setAlphaBufferSize(24);
    //设置OpenGl版本号
    format.setVersion(3,3);
    //设置重采样次数，用于反走样
    format.setSamples(10);

    //设置OpenGl格式
    this->setFormat(format);


    //加载模型文件
    //model_out.load(":/res/model/out_muyulu.obj");
}


//析构函数

ASHOpenglWidget::~ASHOpenglWidget()
{
    //使当前OpenGl上下文为当前上下文
    makeCurrent();
}



//初始化OpenGl函数
void ASHOpenglWidget::initializeGL()
{
    this->initializeOpenGLFunctions();//初始化opengl函数

    //输入对象
    initializeInputobj();

    //输出对象
    initializeOutobj();
}



//调整OpenGl视口大小
//w：整数类型，表示窗口的新宽度。
//h：整数类型，表示窗口的新高度。
//projection：用于存储投影矩阵

void ASHOpenglWidget::resizeGL(int w,int h)
{
    //设置视口大小
    this->glViewport(0,0,w,h);

    // 将投影矩阵设置为单位矩阵
    projection.setToIdentity();

    // 设置透视投影矩阵
    projection.perspective(90.0f, (GLfloat)w/(GLfloat)h, 0.001f, 1000.0f);


    //用于设置正交投影矩阵和更新着色器程序中的投影矩阵
    //projection.ortho(-100,100,-100,100,-100,100);
    //shaderprogram.setUniformValue("projection", projection);
}



// 绘制 OpenGL 场景
void ASHOpenglWidget::paintGL()
{
    // 设置清屏颜色
    this->glClearColor(0.0f,0.0f,0.0f,1.0f);

    // 清除颜色缓冲区和深度缓冲区
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 禁用面剔除
    this->glDisable(GL_CULL_FACE);


    // 如果输入模型需要绘制
    if(model_input.isDraw)
    {
        // 绑定输入模型的着色器程序和顶点数组对象

        //shaderprogram_input：输入模型的着色器程序
        shaderprogram_input.bind();

        //VAO_input：输入模型的顶点数组对象
        VAO_input.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id

        //VBOPosition_input：输入模型顶点位置的顶点缓冲对象
        VBOPosition_input.bind();
        VBOPosition_input.allocate(model_input.vertices().data(),3*sizeof(float)*model_input.vertices().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度

        //shaderprogram_input：输入模型的着色器程序
        shaderprogram_input.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
        shaderprogram_input.enableAttributeArray("aPos");

        //VBONormal_input：输入模型法线信息的顶点缓冲对象
        VBONormal_input.bind();
        VBONormal_input.allocate(model_input.normals().data(),3*sizeof(float)*model_input.normals().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度

        //shaderprogram_input：输入模型的着色器程序
        shaderprogram_input.setAttributeBuffer("aNormal", GL_FLOAT,0, 3, sizeof(GLfloat)*3);
        shaderprogram_input.enableAttributeArray("aNormal");


        // 如果输入模型绘制错误
        if(model_input.isDrawerror)
        {
            //VBOError_input：输入模型错误信息的顶点缓冲对象。
            VBOError_input.bind();
            VBOError_input.allocate(model_input.m_error.data(),sizeof(float)*model_input.m_error.size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度

            //shaderprogram_input：输入模型的着色器程序
            shaderprogram_input.setAttributeBuffer("aError", GL_FLOAT,0, 1, sizeof(GLfloat));
            shaderprogram_input.enableAttributeArray("aError");

        }

        //将此着色器程序绑定到活动的qopenglcontext，并使其成为当前着色器程序。任何先前绑定的着色器程序都将被释放
        //成功绑定返回ture,反之，返回false.


        // 设置光照和模型变换
        QVector3D lightColor(1.0f,1.0f,1.0f);
        QVector3D objectColor(1.0f,0.5f,0.31f);
        QVector3D lightPos(0.0f,0.0f,50.0f);


        // 设置着色器程序的 uniform 变量
        //shaderprogram_input：输入模型的着色器程序
        shaderprogram_input.setUniformValue("objectColor",objectColor);
        shaderprogram_input.setUniformValue("lightColor",lightColor);
        shaderprogram_input.setUniformValue("lightPos", lightPos);
        //model.rotate(rotation);


        // 设置模型变换
         //这些操作用于控制模型矩阵，实现对模型的平移和旋转操作。
         //通过设置模型矩阵的平移和旋转，可以改变模型在场景中的位置和方向，从而实现模型的移动和旋转效果。
         //根据给定的平移和旋转参数，对模型进行相应的变换，以便在渲染时显示出正确的位置和方向。
        //model：模型矩阵
        //将模型矩阵设为单位矩阵
        model.setToIdentity();

        model.translate(xtrans, ytrans, ztrans);
        model.rotate(xrot,1.0f,0.0f,0.0f);
        model.rotate(yrot,0.0f,1.0f,0.0f);
        model.rotate(zrot,0.0f,0.0f,1.0f);


        //shaderprogram_input：输入模型的着色器程序
        shaderprogram_input.setUniformValue("view", view);
        shaderprogram_input.setUniformValue("projection", projection);
        shaderprogram_input.setUniformValue("model", model);

        int n = model_input.vertices().size()*3;
        qDebug() << n;
        QOpenGLVertexArrayObject::Binder bind(&VAO_input);//绑定VAO

        // 绘制三角形
        this->glDrawArrays(GL_TRIANGLES,0,n);

        qDebug()<<"draw done model_input";
    }


    //model_out：输出模型对象
    if(model_out.isDraw)
    {
        // 绑定输出模型的着色器程序和顶点数组对象
        //shaderprogram_out：输出模型的着色器程序
        shaderprogram_out.bind();

        //VAO_out：输出模型的顶点数组对象
        VAO_out.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id

        //VBOPosition_out：输出模型顶点位置的顶点缓冲对象
        VBOPosition_out.bind();
        VBOPosition_out.allocate(model_out.vertices().data(),3*sizeof(float)*model_out.vertices().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度

        //shaderprogram_out：输出模型的着色器程序
        shaderprogram_out.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
        shaderprogram_out.enableAttributeArray("aPos");

        //VBONormal_out：输出模型法线信息的顶点缓冲对象
        VBONormal_out.bind();
        VBONormal_out.allocate(model_out.normals().data(),3*sizeof(float)*model_out.normals().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度

        //shaderprogram_out：输出模型的着色器程序
        shaderprogram_out.setAttributeBuffer("aNormal", GL_FLOAT,0, 3, sizeof(GLfloat)*3);
        shaderprogram_out.enableAttributeArray("aNormal");


        // 如果输出模型绘制错误
        if(model_out.isDrawerror)
        {
            //VBOError_out：输出模型错误信息的顶点缓冲对象
            VBOError_out.bind();
            VBOError_out.allocate(model_out.m_error.data(),sizeof(float)*model_out.m_error.size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度

            //shaderprogram_out：输出模型的着色器程序
            shaderprogram_out.setAttributeBuffer("aError", GL_FLOAT,0, 1, sizeof(GLfloat));
            shaderprogram_out.enableAttributeArray("aError");

        }

        //将此着色器程序绑定到活动的qopenglcontext，并使其成为当前着色器程序。任何先前绑定的着色器程序都将被释放
        //成功绑定返回ture,反之，返回false.

        // 设置光照和模型变换
        QVector3D lightColor(1.0f,1.0f,1.0f);
        QVector3D objectColor(1.0f,0.5f,0.31f);
        QVector3D lightPos(0.0f,10.0f,30.0f);


        // 设置着色器程序的 uniform 变量
        //shaderprogram_out：输出模型的着色器程序
        shaderprogram_out.setUniformValue("objectColor",objectColor);
        shaderprogram_out.setUniformValue("lightColor",lightColor);
        shaderprogram_out.setUniformValue("lightPos", lightPos);
        //model.rotate(rotation);



        // 设置模型变换
        //model：模型矩阵
        model.setToIdentity();

        model.translate(xtrans, ytrans, ztrans);
        model.rotate(xrot,1.0f,0.0f,0.0f);
        model.rotate(yrot,0.0f,1.0f,0.0f);
        model.rotate(zrot,0.0f,0.0f,1.0f);


        //shaderprogram_out：输出模型的着色器程序
        shaderprogram_out.setUniformValue("view", view);
        shaderprogram_out.setUniformValue("projection", projection);
        shaderprogram_out.setUniformValue("model", model);

        int n = model_out.vertices().size()*3;
        qDebug() << n;
        QOpenGLVertexArrayObject::Binder bind(&VAO_out);//绑定VAO

        // 绘制三角形
        this->glDrawArrays(GL_TRIANGLES,0,n);
        qDebug()<<"draw done model_out";
    }
}



//处理鼠标按下事件
void ASHOpenglWidget::mousePressEvent(QMouseEvent *event)
{
    //将鼠标事件的位置信息转换为一个 QVector2D 对象，用于记录鼠标的当前位置
    mousePos = QVector2D(event->pos());

    //返回鼠标事件发生时的位置，这个位置是相对于接收事件的窗口或控件的坐标
    event->accept();
}


// 处理鼠标移动事件
//首先判断鼠标事件是否是左键按下的移动事件。
//计算鼠标移动的位移向量，并根据其长度计算旋转角度。
//根据位移向量确定旋转轴，这里选择了一个与位移向量垂直的向量作为旋转轴。
//根据旋转轴和角度计算新的旋转状态，并更新 rotation 变量。
//更新 mousePos 为当前鼠标位置，以备下一次移动事件使用。
//最后调用 update() 函数，通知系统需要更新窗口内容，以显示新的旋转效果。
void ASHOpenglWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        //newPos：记录鼠标移动后的新位置，通过将鼠标事件的位置信息转换为 QVector2D 对象得到
        QVector2D newPos = (QVector2D)event->pos();

        //diff：表示鼠标移动前后的位置差，即鼠标移动的位移向量
        QVector2D diff = newPos - mousePos;

        //angle：计算出的旋转角度，根据鼠标移动的位移向量长度计算得到
        qreal angle = (diff.length())/3.6;
        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();

        //rotationAxis：旋转轴，根据鼠标移动的位移向量确定，是位移向量在 x-y 平面上的法向量，并进行了归一化处理
        //rotation：用于记录当前的旋转状态，通过 QQuaternion::fromAxisAndAngle() 方法根据旋转轴和角度计算新的旋转状态
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
        mousePos = newPos;
        this->update();
    }
    event->accept();
}


// 处理滚轮事件
//获取滚轮滚动的角度变化，并将其除以2得到实际的角度变化。
//根据滚轮滚动的方向，调整沿着 z 轴的平移距离 ztrans。如果是向上滚动，则增加 ztrans 值；如果是向下滚动，则减小 ztrans 值。
//调用 update() 函数，通知系统需要更新窗口内容，以显示新的平移效果。
//最后调用 event->accept()，标记该事件已经被处理。
void ASHOpenglWidget::wheelEvent(QWheelEvent *event)
{
    //numDegrees：记录滚轮滚动的角度变化
    QPoint numDegrees = event->angleDelta() / 2;

    //ztrans：记录沿着 z 轴的平移距离，根据滚轮滚动的方向进行调整
    if (numDegrees.y() > 0) {
        ztrans += 2.5f;
    } else if (numDegrees.y() < 0) {
        ztrans -= 2.5f;
    }
    //glTranslatef(ztrans, 0, 0);

    this->update();
    event->accept();
}


// 初始化输入对象
void ASHOpenglWidget::initializeInputobj()
{
    //生成着色器程序
    //shaderprogram_input：表示着色器程序对象，用于管理顶点着色器和片段着色器的加载、编译和链接
    shaderprogram_input.create();
    if(!shaderprogram_input.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/model_input.vert")){
        qDebug()<<"ERROR:"<<shaderprogram_input.log();    //如果编译出错,打印报错信息
    }
    if(!shaderprogram_input.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/model_input.frag")){
        qDebug()<<"ERROR:"<<shaderprogram_input.log();    //如果编译出错,打印报错信息
    }
    //将添加到此程序的着色器与addshader链接在一起
     if(!shaderprogram_input.link()){
         qDebug()<<"ERROR:"<<shaderprogram_input.log();    //如果链接出错,打印报错信息
     }
//    QOpenGLVertexArrayObject::Binder{&VAO};

    //VAO_input：表示顶点数组对象，用于管理顶点数据的状态
    VAO_input.create();// 创建一个VAO对象，OpenGL会给它（顶点数组缓存对象）分配一个id
    VAO_input.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id

    //VBOPosition_input：用于存储顶点位置数据的顶点缓冲对象
    VBOPosition_input.create();

    //VBONormal_input：用于存储法线数据的顶点缓冲对象
    VBONormal_input.create();

    //VBOError_input：用于存储错误数据的顶点缓冲对象
    VBOError_input.create();


//    VBOPosition_input.bind();
//    VBOPosition_input.allocate(model_input.vertices().data(),3*sizeof(float)*model_input.vertices().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
//    shaderprogram_input.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
//    shaderprogram_input.enableAttributeArray("aPos");

//    VBONormal_input.bind();
//    VBONormal_input.allocate(model_input.normals().data(),3*sizeof(float)*model_input.normals().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
//    shaderprogram_input.setAttributeBuffer("aNormal", GL_FLOAT,0, 3, sizeof(GLfloat)*3);
//    shaderprogram_input.enableAttributeArray("aNormal");
    this->glEnable(GL_DEPTH_TEST);
//    VAO.release();//释放
//    VBO.release();

    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));   //原始视角
}


// 初始化输出对象
void ASHOpenglWidget::initializeOutobj()
{
    //shaderprogram_out：用于处理输出模型的着色器程序
    shaderprogram_out.create();//生成着色器程序


    if(!shaderprogram_out.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/model_out.vert")){
        qDebug()<<"ERROR:"<<shaderprogram_out.log();    //如果编译出错,打印报错信息
    }

    if(!shaderprogram_out.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/model_out.frag")){
        qDebug()<<"ERROR:"<<shaderprogram_out.log();    //如果编译出错,打印报错信息
    }


    //将添加到此程序的着色器与addshader链接在一起
    if(!shaderprogram_out.link()){
         qDebug()<<"ERROR:"<<shaderprogram_out.log();    //如果链接出错,打印报错信息
     }


    //QOpenGLVertexArrayObject::Binder{&VAO};


    // 创建一个VAO对象，OpenGL会给它（顶点数组缓存对象）分配一个id
    //VAO_out：用于输出模型的顶点数组对象
    VAO_out.create();

    //将RC中的当前顶点数组缓存对象Id设置为VAO的id
    VAO_out.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id

    //VBOPosition_out：用于输出模型的顶点位置缓冲区对象
    VBOPosition_out.create();

    //VBONormal_out：用于输出模型的顶点法线缓冲区对象
    VBONormal_out.create();

    //VBOError_out：用于输出模型的错误信息缓冲区对象
    VBOError_out.create();

    this->glEnable(GL_DEPTH_TEST);

    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));   //原始视角
}

