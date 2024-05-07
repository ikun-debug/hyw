#include "ashopenglwidget.h"
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QtMath>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>

ASHOpenglWidget::ASHOpenglWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    //,VBO(QOpenGLBuffer::VertexBuffer)
    ,xtrans(0.0),ytrans(0.0),ztrans(0.0)
{
    QSurfaceFormat format;
    format.setAlphaBufferSize(24);  //设置alpha缓冲大小
    format.setVersion(3,3);         //设置版本号
    format.setSamples(10);          //设置重采样次数，用于反走样

    this->setFormat(format);
    //model_out.load(":/res/model/out_muyulu.obj");
}



ASHOpenglWidget::~ASHOpenglWidget()
{
    makeCurrent();
}


void ASHOpenglWidget::initializeGL()
{
    this->initializeOpenGLFunctions();//初始化opengl函数
    initializeInputobj();
    initializeOutobj();
}
void ASHOpenglWidget::resizeGL(int w,int h)
{
    this->glViewport(0,0,w,h);
    projection.setToIdentity();
    projection.perspective(90.0f, (GLfloat)w/(GLfloat)h, 0.001f, 1000.0f);
    //projection.ortho(-100,100,-100,100,-100,100);
    //shaderprogram.setUniformValue("projection", projection);
}

void ASHOpenglWidget::paintGL()
{
    this->glClearColor(0.0f,0.0f,0.0f,1.0f);//设置清屏颜色
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//
    this->glDisable(GL_CULL_FACE);
    if(model_input.isDraw)
    {

        shaderprogram_input.bind();
        VAO_input.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id
        VBOPosition_input.bind();
        VBOPosition_input.allocate(model_input.vertices().data(),3*sizeof(float)*model_input.vertices().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
        shaderprogram_input.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
        shaderprogram_input.enableAttributeArray("aPos");
        VBONormal_input.bind();
        VBONormal_input.allocate(model_input.normals().data(),3*sizeof(float)*model_input.normals().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
        shaderprogram_input.setAttributeBuffer("aNormal", GL_FLOAT,0, 3, sizeof(GLfloat)*3);
        shaderprogram_input.enableAttributeArray("aNormal");

        if(model_input.isDrawerror)
        {
            VBOError_input.bind();
            VBOError_input.allocate(model_input.m_error.data(),sizeof(float)*model_input.m_error.size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
            shaderprogram_input.setAttributeBuffer("aError", GL_FLOAT,0, 1, sizeof(GLfloat));
            shaderprogram_input.enableAttributeArray("aError");

        }

        //将此着色器程序绑定到活动的qopenglcontext，并使其成为当前着色器程序。任何先前绑定的着色器程序都将被释放
        //成功绑定返回ture,反之，返回false.

        QVector3D lightColor(1.0f,1.0f,1.0f);
        QVector3D objectColor(1.0f,0.5f,0.31f);
        QVector3D lightPos(0.0f,0.0f,50.0f);

        shaderprogram_input.setUniformValue("objectColor",objectColor);
        shaderprogram_input.setUniformValue("lightColor",lightColor);
        shaderprogram_input.setUniformValue("lightPos", lightPos);
        //model.rotate(rotation);

        model.setToIdentity();

        model.translate(xtrans, ytrans, ztrans);
        model.rotate(xrot,1.0f,0.0f,0.0f);
        model.rotate(yrot,0.0f,1.0f,0.0f);
        model.rotate(zrot,0.0f,0.0f,1.0f);


        shaderprogram_input.setUniformValue("view", view);
        shaderprogram_input.setUniformValue("projection", projection);
        shaderprogram_input.setUniformValue("model", model);

        int n = model_input.vertices().size()*3;
        qDebug() << n;
        QOpenGLVertexArrayObject::Binder bind(&VAO_input);//绑定VAO
        this->glDrawArrays(GL_TRIANGLES,0,n);

        qDebug()<<"draw done model_input";
    }


    if(model_out.isDraw)
    {

        shaderprogram_out.bind();
        VAO_out.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id
        VBOPosition_out.bind();
        VBOPosition_out.allocate(model_out.vertices().data(),3*sizeof(float)*model_out.vertices().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
        shaderprogram_out.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
        shaderprogram_out.enableAttributeArray("aPos");
        VBONormal_out.bind();
        VBONormal_out.allocate(model_out.normals().data(),3*sizeof(float)*model_out.normals().size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
        shaderprogram_out.setAttributeBuffer("aNormal", GL_FLOAT,0, 3, sizeof(GLfloat)*3);
        shaderprogram_out.enableAttributeArray("aNormal");

        if(model_out.isDrawerror)
        {
            VBOError_out.bind();
            VBOError_out.allocate(model_out.m_error.data(),sizeof(float)*model_out.m_error.size());//将顶点数据分配到VBO中，第一个参数为数据指针，第二个参数为数据的字节长度
            shaderprogram_out.setAttributeBuffer("aError", GL_FLOAT,0, 1, sizeof(GLfloat));
            shaderprogram_out.enableAttributeArray("aError");

        }

        //将此着色器程序绑定到活动的qopenglcontext，并使其成为当前着色器程序。任何先前绑定的着色器程序都将被释放
        //成功绑定返回ture,反之，返回false.
        QVector3D lightColor(1.0f,1.0f,1.0f);
        QVector3D objectColor(1.0f,0.5f,0.31f);
        QVector3D lightPos(0.0f,10.0f,30.0f);

        shaderprogram_out.setUniformValue("objectColor",objectColor);
        shaderprogram_out.setUniformValue("lightColor",lightColor);
        shaderprogram_out.setUniformValue("lightPos", lightPos);
        //model.rotate(rotation);

        model.setToIdentity();

        model.translate(xtrans, ytrans, ztrans);
        model.rotate(xrot,1.0f,0.0f,0.0f);
        model.rotate(yrot,0.0f,1.0f,0.0f);
        model.rotate(zrot,0.0f,0.0f,1.0f);


        shaderprogram_out.setUniformValue("view", view);
        shaderprogram_out.setUniformValue("projection", projection);
        shaderprogram_out.setUniformValue("model", model);

        int n = model_out.vertices().size()*3;
        qDebug() << n;
        QOpenGLVertexArrayObject::Binder bind(&VAO_out);//绑定VAO
        this->glDrawArrays(GL_TRIANGLES,0,n);
        qDebug()<<"draw done model_out";
    }
}

void ASHOpenglWidget::mousePressEvent(QMouseEvent *event)
{
    mousePos = QVector2D(event->pos());
    event->accept();
}

void ASHOpenglWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QVector2D newPos = (QVector2D)event->pos();
        QVector2D diff = newPos - mousePos;
        qreal angle = (diff.length())/3.6;
        // Rotation axis is perpendicular to the mouse position difference
        // vector
        QVector3D rotationAxis = QVector3D(diff.y(), diff.x(), 0.0).normalized();
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
        mousePos = newPos;
        this->update();
    }
    event->accept();
}

void ASHOpenglWidget::wheelEvent(QWheelEvent *event)
{
    QPoint numDegrees = event->angleDelta() / 2;

    if (numDegrees.y() > 0) {
        ztrans += 2.5f;
    } else if (numDegrees.y() < 0) {
        ztrans -= 2.5f;
    }
    //glTranslatef(ztrans, 0, 0);

    this->update();
    event->accept();
}

void ASHOpenglWidget::initializeInputobj()
{
    shaderprogram_input.create();//生成着色器程序
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

    VAO_input.create();// 创建一个VAO对象，OpenGL会给它（顶点数组缓存对象）分配一个id
    VAO_input.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id
    VBOPosition_input.create();
    VBONormal_input.create();
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

void ASHOpenglWidget::initializeOutobj()
{
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
//    QOpenGLVertexArrayObject::Binder{&VAO};

    VAO_out.create();// 创建一个VAO对象，OpenGL会给它（顶点数组缓存对象）分配一个id
    VAO_out.bind();//将RC中的当前顶点数组缓存对象Id设置为VAO的id
    VBOPosition_out.create();
    VBONormal_out.create();
    VBOError_out.create();
    this->glEnable(GL_DEPTH_TEST);
    view.setToIdentity();
    view.lookAt(QVector3D(0.0f, 0.0f, 3.0f), QVector3D(0.0f,0.0f,0.0f), QVector3D(0.0f,1.0f,0.0f));   //原始视角
}

