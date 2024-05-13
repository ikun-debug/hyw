#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QTimer>
#include <QMainWindow>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QPalette>
#include <QGuiApplication>
#include <QPainter>
#include <QToolBar>
#include<QStatusBar>
#include<QLabel>
#include <QMovie>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //创建第二个窗口链接
    mainwindow2 = new MainWindow2(this);
    //connect(mainwindow2,SIGNAL(bSignal()),this,SLOT(showAHideB()));


    //创建窗口四的链接
    mainwindow4 = new MainWindow4(this);


    //创建窗口五的链接
    mainwindow5 = new MainWindow5(this);



    //创建窗口三的链接
    mainwindow3 = new MainWindow3(this);




    //设置标题
    setWindowTitle("三维网格模型误差分析工具");

    //固定窗口大小
    setFixedSize(1300, 700); // 设置窗口大小为 1100x600 像素


    //设置gif图片
    // 获取指向QLabel的指针
    QLabel *label = ui->GIF3;

    // 创建一个QMovie对象并加载GIF图像
    QMovie *movie = new QMovie(":/demo/PATRICK.gif"); // 替换GIF图像路径

    // 将QMovie对象设置到QLabel中
    label->setMovie(movie);

//    // 调整GIF图像大小为原始大小的三分之一
//    QSize newSize = movie->scaledSize() / 3; // 将大小缩小为原始大小的三分之一
//    movie->setScaledSize(newSize);

    // 开始播放GIF
    movie->start();



    //设置背景图片
    //MainWindow.setStyleSheet("background-image: url(::/demo pic/to/bg1.jpg);");


    //窗口透明
    //QPalette pal = palette();
    //pal.setColor(QPalette::Background, QColor(0x00, 0xff, 0x00, 0x00));
    //setPalette(pal);



    //状态栏
    //QStatusBar *status = this‐>statusBar();
    //status‐>addWidget(new QLabel("状态"));//向状态添加控件

    //给label赋字
    //QString text = "Hello, World!"; // 要显示的文本
    //label->setText(text);


    //给菜单、按钮设置图标
    /*
    //open_input
    QAction *openAction1 = ui->open_input;
    openAction1->setIcon(QIcon(":/demo pic/FolderOpened.png"));



    //open_output
    QAction *openAction2 = ui->open_out;
    openAction2->setIcon(QIcon(":/demo pic/OpenFolder.png"));


    //clear_all
    QAction *openAction3 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));

    //action_input
    QAction *openAction4 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));


    //action_output
    QAction *openAction5 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));


    //error
    QAction *openAction6 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));

    //color
    QAction *openAction7 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));

    //about
    QAction *openAction8 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));

    //help
    QAction *openAction9 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));

    //others
    QAction *openAction10 = ui->clear_all;
    openAction3->setIcon(QIcon(":/demo pic/Run.png"));
    */

    //链接
    //链接open_input的QAction
    connect(ui->open_input,SIGNAL(triggered()),this,SLOT(open_input()));

    //链接open_out的QAction
    connect(ui->open_out,SIGNAL(triggered()),this,SLOT(open_out()));

    //链接clear_all的QAction
    connect(ui->clear_all,SIGNAL(triggered()),this,SLOT(clear_all()));

    //链接showInput的QButton
    connect(ui->showInput,SIGNAL(clicked()),this,SLOT(showInput()));

    //链接showOut的QButton
    connect(ui->showOut,SIGNAL(clicked()),this,SLOT(showOut()));

    //链接showError的QButton
    connect(ui->showError,SIGNAL(clicked()),this,SLOT(showError()));

    //链接showError的QButton  链接进第二个事件（槽函数）
    connect(ui->showError,SIGNAL(clicked()),this,SLOT(&MainWindow::on_showMessage_clicked));


    //链接showHelp的QButton
    connect(ui->showHelp,SIGNAL(clicked()),this,SLOT(showHelp()));

    //链接about的QAction
    connect(ui->about,SIGNAL(triggered(bool)),this, SLOT(show_about()));


    //链接color的QAction
    connect(ui->color,SIGNAL(triggered(bool)),this, SLOT(show_color()));

    //链接action_input的QAction
    connect(ui->action_input,SIGNAL(triggered(bool)), this, SLOT(on_action_input_triggered()));

    //链接action_output的QAction
    //connect((ui->action_output, SIGNAL(triggered(bool)), this, SLOT(on_action_output_triggered())));


    //链接action_error的QAction
    connect(ui->action_error,SIGNAL(triggered(bool)),this,SLOT(on_action_error_triggered()));


    //链接show_window3的QAction
    connect(ui->show_window3,SIGNAL(triggered(bool)),this,SLOT(show_window3()));

    //链接help的QAction
    connect(ui->help,SIGNAL(triggered(bool)),this,SLOT(help()));

    //视角调整范围
    //调整x、y、z滑动条的取值范围
    ui->Slider_xrot->setRange(-180,180);
    ui->Slider_yrot->setRange(-180,180);
    ui->Slider_zrot->setRange(-180,180);

    //调整xtrans、ytrans、ztrans滑动条的取值范围
    ui->Slider_xtrans->setRange(-500,500);
    ui->Slider_ytrans->setRange(-500,500);
    ui->Slider_ztrans->setRange(-500,500);

    //设置x、y、z的文本框的取值范围
    ui->xrot->setRange(-180,180);
    ui->yrot->setRange(-180,180);
    ui->zrot->setRange(-180,180);

    //设置xtrans、ytrans、ztrans文本框的取值范围
    ui->xtrans->setRange(-500,500);
    ui->ytrans->setRange(-500,500);
    ui->ztrans->setRange(-500,500);

    //视角调整
    //xtrans控件中输入数值时，对应的 QSlider 控件的值也会随之改变
    void(QDoubleSpinBox:: *ptrxtrans)(double)=&QDoubleSpinBox::valueChanged;
    //链接xtrans和Slider_xtrans
    connect(ui->xtrans,ptrxtrans,ui->Slider_xtrans,&QSlider::setValue);


    //ytrans控件中输入数值时，对应的 QSlider 控件的值也会随之改变
    void(QDoubleSpinBox:: *ptrytrans)(double)=&QDoubleSpinBox::valueChanged;
    //链接ytrans和Slider_ytrans
    connect(ui->ytrans,ptrytrans,ui->Slider_ytrans,&QSlider::setValue);


    //ztrans控件中输入数值时，对应的 QSlider 控件的值也会随之改变
    void(QDoubleSpinBox:: *ptrztrans)(double)=&QDoubleSpinBox::valueChanged;
    //链接ztrans和Slider_ztrans
    connect(ui->ztrans,ptrztrans,ui->Slider_ztrans,&QSlider::setValue);


    //xrot控件中输入数值时，对应的 QSlider 控件的值也会随之改变
    void(QDoubleSpinBox:: *ptrxrot)(double)=&QDoubleSpinBox::valueChanged;
    //链接xrot和Slider_xrot
    connect(ui->xrot,ptrxrot,ui->Slider_xrot,&QSlider::setValue);


    //yrot控件中输入数值时，对应的 QSlider 控件的值也会随之改变
    void(QDoubleSpinBox:: *ptryrot)(double)=&QDoubleSpinBox::valueChanged;
    //链接yrot和Slider_yrot
    connect(ui->yrot,ptryrot,ui->Slider_yrot,&QSlider::setValue);


    //zrot控件中输入数值时，对应的 QSlider 控件的值也会随之改变
    void(QDoubleSpinBox:: *ptrzrot)(double)=&QDoubleSpinBox::valueChanged;
    //链接zrot和Slider_zrot
    connect(ui->zrot,ptrzrot,ui->Slider_zrot,&QSlider::setValue);


    //将滑动条（QSlider）的值改变信号与对应的双精度浮点数输入框（QDoubleSpinBox）的设置值槽函数连接起来，实现滑动条的值改变时双精度浮点数输入框的值也随之改变
    //Slider_xtrans值更新时同时会传递给xtrans槽函数
    connect(ui->Slider_xtrans,&QSlider::valueChanged,ui->xtrans,&QDoubleSpinBox::setValue);

    //Slider_ytrans值更新时同时会传递给ytrans槽函数
    connect(ui->Slider_ytrans,&QSlider::valueChanged,ui->ytrans,&QDoubleSpinBox::setValue);

    //Slider_ztrans值更新时同时会传递给ztrans槽函数
    connect(ui->Slider_ztrans,&QSlider::valueChanged,ui->ztrans,&QDoubleSpinBox::setValue);

    //Slider_xrot值更新时同时会传递给xrot槽函数
    connect(ui->Slider_xrot,&QSlider::valueChanged,ui->xrot,&QDoubleSpinBox::setValue);

    //Slider_yrot值更新时同时会传递给yrot槽函数
    connect(ui->Slider_yrot,&QSlider::valueChanged,ui->yrot,&QDoubleSpinBox::setValue);

    //Slider_zrot值更新时同时会传递给zrot槽函数
    connect(ui->Slider_zrot,&QSlider::valueChanged,ui->zrot,&QDoubleSpinBox::setValue);

    //当 ui->Slider_xrot 的值改变时，会触发 Lambda 函数中的代码。
    //Lambda 函数中将 ui->openGLWidget 中的 xrot（x轴旋转角度）设置为 ui->xrot 控件的值，然后调用 update() 函数刷新 OpenGL 窗口，以更新 x 轴旋转角度的显示。
    connect(ui->Slider_xrot,&QSlider::valueChanged,[=](){
        ui->openGLWidget->xrot=ui->xrot->value();
        ui->openGLWidget->update();
    });

    //当 Slider_yrot 的值改变时，会触发 Lambda 函数中的代码。
    //Lambda 函数中将 ui->openGLWidget 中的 yrot（y轴旋转角度）设置为 ui->yrot 控件的值，然后调用 update() 函数刷新 OpenGL 窗口，以更新 x 轴旋转角度的显示。
    connect(ui->Slider_yrot,&QSlider::valueChanged,[=](){
        ui->openGLWidget->yrot=ui->yrot->value();
        ui->openGLWidget->update();
    });

    //当 Slider_zrot 的值改变时，会触发 Lambda 函数中的代码。
    //Lambda 函数中将 ui->openGLWidget 中的 zrot（z轴旋转角度）设置为 ui->zrot 控件的值，然后调用 update() 函数刷新 OpenGL 窗口，以更新 x 轴旋转角度的显示。
    connect(ui->Slider_zrot,&QSlider::valueChanged,[=](){
        ui->openGLWidget->zrot=ui->zrot->value();
        ui->openGLWidget->update();
    });


    //当 ui->Slider_xtrans 的值改变时，会触发 Lambda 函数中的代码。
    //Lambda 函数中将 ui->openGLWidget 中的 xtrans（ x 轴方向上的平移距离）设置为 ui->xtrans 控件的值，然后调用 update() 函数刷新 OpenGL 窗口，以更新 x 轴旋转角度的显示。
    connect(ui->Slider_xtrans,&QSlider::valueChanged,[=](){
        ui->openGLWidget->xtrans=ui->xtrans->value();
        ui->openGLWidget->update();
    });

    //当 Slider_ytrans 的值改变时，会触发 Lambda 函数中的代码。
    //Lambda 函数中将 ui->openGLWidget 中的 ytrans（ y 轴方向上的平移距离）设置为 ui->ytrans 控件的值，然后调用 update() 函数刷新 OpenGL 窗口，以更新 x 轴旋转角度的显示。
    connect(ui->Slider_ytrans,&QSlider::valueChanged,[=](){
        ui->openGLWidget->ytrans=ui->ytrans->value();
        ui->openGLWidget->update();
    });

    //当 Slider_ztrans 的值改变时，会触发 Lambda 函数中的代码。
    //Lambda 函数中将 ui->openGLWidget 中的 ztrans（ z 轴方向上的平移距离）设置为 ui->ztrans 控件的值，然后调用 update() 函数刷新 OpenGL 窗口，以更新 x 轴旋转角度的显示。
    connect(ui->Slider_ztrans,&QSlider::valueChanged,[=](){
        ui->openGLWidget->ztrans=ui->ztrans->value();
        ui->openGLWidget->update();
    });

}


//showhelp界面  关闭本界面打开showhelp界面
//界面切换
void MainWindow::showHelp()
{
    this->hide();
    mainwindow2->show();
}



//关于本软件的文档
void MainWindow::show_about()
{
    mainwindow5->show();
}


//着色器文档
void MainWindow::show_color()
{
    mainwindow4->show();
}


//问题文档
void MainWindow::show_window3()
{
    mainwindow3->show();
}


//帮助文档
void MainWindow::help()
{

    mainwindow2->show();
}


//showhelp文档
//void MainWindow::showHelp()
//{
//    this->hide();
//    mainwindow2->show();
//}


/*
//展示一个关闭一个
void MainWindow::showAHideB()
{
    this->show();
    mainwindow2->hide();
}
*/


//误差颜色标准窗口
//void MainWindow::on_showStandard_clicked()
//{
//    QMessageBox* msgBox = new QMessageBox(this);
//        msgBox->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时自动删除
//        msgBox->setText("误差的颜色标准为：");
//        msgBox->setIcon(QMessageBox::NoIcon);  // 设置图标为无图标
//        msgBox->setWindowTitle("Standard");
//        msgBox->show();
//}


//显示误差窗口
//void MainWindow::on_showData_clicked()
//{
//    QMessageBox* msgBox = new QMessageBox(this);
//        msgBox->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时自动删除
//        msgBox->setText("误差为：");
//        msgBox->setIcon(QMessageBox::NoIcon);  // 设置图标为无图标
//        msgBox->setWindowTitle("Data");
//        msgBox->show();
//}


MainWindow::~MainWindow()
{
    delete ui;
}


//open_input的槽函数
//选择文件
//OpenGl里加载文件并显示
void MainWindow::open_input()
{
    qDebug()<<"open_input";
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "./", tr("Images(*.obj)"));
    //ui->openGLWidget->model_input.load(":/res/model/input_muyulu.obj");
    ui->openGLWidget->model_input.load(filename);
    ui->openGLWidget->update();
}



//open_out的槽函数
//选择文件
//OpenGl里加载文件并显示
void MainWindow::open_out()
{
    qDebug()<<"open_out";
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "./", tr("Images(*.obj)"));
    ui->openGLWidget->model_out.load(filename);
    //ui->openGLWidget->model_out.load(":/res/model/out_muyulu.obj");
    ui->openGLWidget->update();
}



//clear_all的槽函数
//清屏
//调用LoadObj（）表示清除所有内容后重新加载另一个模型对象到输出模型中
void MainWindow::clear_all()
{

    qDebug()<<"clear_all";
    ui->openGLWidget->model_input=LoadObj();
    ui->openGLWidget->model_out=LoadObj();
    ui->openGLWidget->update();
}


//showInput的槽函数
//确定着色input拒绝着色out
void MainWindow::showInput()
{
    ui->openGLWidget->model_input.isDraw=true;
    ui->openGLWidget->model_out.isDraw=false;
    ui->openGLWidget->update();
    qDebug()<<"showInput";
}


//showOut的槽函数
//确定着色out拒绝着色input
void MainWindow::showOut()
{
    ui->openGLWidget->model_input.isDraw=false;
    ui->openGLWidget->model_out.isDraw=true;
    ui->openGLWidget->update();
    qDebug()<<"showOut";
}


//showError的槽函数
void MainWindow::showError()
{
    //获取两个文件的顶点信息以及error
    QVector<QVector3D> vertices_calulate_input=ui->openGLWidget->model_input.m_vertices_calculate;
    QVector<QVector3D> vertices_calulate_out=ui->openGLWidget->model_out.m_vertices_calculate;
    QVector<float> error;


    //计算模型输出顶点与输入顶点之间最小距离的过程，并将结果存储在 error 变量中
    //调整 error 变量的大小，使其与 vertices_calulate_input 中的顶点数量相匹配，以便存储每个输出顶点与输入顶点之间的最小距离
//    error.resize(vertices_calulate_input.size());

    //通过循环遍历 vertices_calulate_input 中的每个输出顶点
    //    for (int i = 0; i < vertices_calulate_input.size(); ++i) {

    //通过循环遍历 vertices_calulate_input 中的每个输出顶点

    //获取当前输出顶点
    //        QVector3D inputPoint = vertices_calulate_input.at(i);

    //初始化最小距离 minDistance 为一个很大的值
    //        float minDistance = std::numeric_limits<double>::max();

    //在内部循环中，遍历所有输入顶点
    //        for (const QVector3D& outputPoint : vertices_calulate_out) {

    //计算当前输入顶点与当前输出顶点之间的距离 currentDistance
    //            float currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);

    //计算实际距离并更新 distance
    //            float distance = sqrt(currentDistance);
//            //double distance = inputPoint.distanceTo(outputPoint);

    //如果当前距离小于 minDistance，则更新 minDistance 为当前距离
    //            if (distance < minDistance) {
//                minDistance = distance;
//            }
//        }

    //将计算得到的最小距离 minDistance 存储在 error 变量的相应位置 error[i] 中，以便后续使用
    //        error[i] = minDistance;
//    }

    //计算模型输出顶点与输入顶点之间最小距离的过程，并将结果存储在 error 变量中
    //调整 error 变量的大小，使其与 vertices_calulate_out 中的顶点数量相匹配，以便存储每个输出顶点与输入顶点之间的最小距离
    error.resize(vertices_calulate_out.size());

    //通过循环遍历 vertices_calulate_out 中的每个输出顶点
    for (int i = 0; i < vertices_calulate_out.size(); ++i) {

        //获取当前输出顶点 outputPoint = vertices_calulate_out.at(i);
        QVector3D outputPoint = vertices_calulate_out.at(i);

        //初始化最小距离 minDistance 为一个很大的值 std::numeric_limits<double>::max();
        double minDistance = std::numeric_limits<double>::max();

        //在内部循环中，遍历所有输入顶点 vertices_calulate_input
        for (const QVector3D& inputPoint : vertices_calulate_input) {
            //计算当前输入顶点与当前输出顶点之间的距离 currentDistance
            double currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);

            //计算实际距离并更新 distance
            double distance = sqrt(currentDistance);


            //double distance = inputPoint.distanceTo(outputPoint);
            //如果当前距离小于 minDistance，则更新 minDistance 为当前距离
            if (distance < minDistance) {
                minDistance = distance;
            }
        }

        //将计算得到的最小距离 minDistance 存储在 error 变量的相应位置 error[i] 中，以便后续使用
        error[i] = minDistance;
    }


    //ui->openGLWidget->model_input.m_error=error;
    //设置 model_out 对象的 isDrawerror 属性为 true。这个属性用于控制是否显示错误信息。
    ui->openGLWidget->model_out.isDrawerror=true;

    //调用 model_out 对象的 calculateError 函数，传递之前计算得到的错误信息 error。这个函数用于处理错误信息并进行进一步的计算或准备数据以便在 UI 中显示。
    ui->openGLWidget->model_out.calculateError(error);

    //更新 openGLWidget，这可能会触发重绘操作，以便显示最新的模型和错误信息。
    ui->openGLWidget->update();

    //输出调试信息，显示 "showError"。这个语句用于在调试过程中输出一条消息，以确认代码执行到了这一步。
    qDebug()<<"showError";
}




//showError的按钮
void MainWindow::on_showError_clicked()
{
    QMessageBox* msgBox = new QMessageBox(this);
    // 确保消息框关闭时自动删除
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setText("计算较慢 稍等！");


    // 设置图标为信息图标
    msgBox->setIcon(QMessageBox::Information);
    msgBox->setWindowTitle("Message");
    msgBox->show();

    QTimer::singleShot(2000, msgBox, &QMessageBox::accept);  // 在3秒后接受（关闭）消息框
}





//on_action_input的QAction
//input展示
//out不展示
void MainWindow::on_action_input_triggered()
{
    ui->openGLWidget->model_input.isDraw=true;
    ui->openGLWidget->model_out.isDraw=false;
    ui->openGLWidget->update();
    qDebug()<<"showInput";
}





//on_action_output的QAction
//input不展示
//out展示
void MainWindow::on_action_output_triggered()
{
    ui->openGLWidget->model_input.isDraw=false;
    ui->openGLWidget->model_out.isDraw=true;
    ui->openGLWidget->update();
    qDebug()<<"showOut";
}



//on_action_error的QAction
void MainWindow::on_action_error_triggered()
{
    //获取两个文件的顶点信息以及error
    QVector<QVector3D> vertices_calulate_input=ui->openGLWidget->model_input.m_vertices_calculate;
    QVector<QVector3D> vertices_calulate_out=ui->openGLWidget->model_out.m_vertices_calculate;
    QVector<float> error;

    //计算模型输出顶点与输入顶点之间最小距离的过程，并将结果存储在 error 变量中
    //调整 error 变量的大小，使其与 vertices_calulate_input 中的顶点数量相匹配，以便存储每个输出顶点与输入顶点之间的最小距离
//    error.resize(vertices_calulate_input.size());

    //通过循环遍历 vertices_calulate_input 中的每个输出顶点
    //    for (int i = 0; i < vertices_calulate_input.size(); ++i) {

    //通过循环遍历 vertices_calulate_input 中的每个输出顶点

    //获取当前输出顶点
    //        QVector3D inputPoint = vertices_calulate_input.at(i);

    //初始化最小距离 minDistance 为一个很大的值
    //        float minDistance = std::numeric_limits<double>::max();

    //在内部循环中，遍历所有输入顶点
    //        for (const QVector3D& outputPoint : vertices_calulate_out) {

    //计算当前输入顶点与当前输出顶点之间的距离 currentDistance
    //            float currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);

    //计算实际距离并更新 distance
    //            float distance = sqrt(currentDistance);
//            //double distance = inputPoint.distanceTo(outputPoint);

    //如果当前距离小于 minDistance，则更新 minDistance 为当前距离
    //            if (distance < minDistance) {
//                minDistance = distance;
//            }
//        }

    //将计算得到的最小距离 minDistance 存储在 error 变量的相应位置 error[i] 中，以便后续使用
    //        error[i] = minDistance;
//    }

    //计算模型输出顶点与输入顶点之间最小距离的过程，并将结果存储在 error 变量中
    //调整 error 变量的大小，使其与 vertices_calulate_out 中的顶点数量相匹配，以便存储每个输出顶点与输入顶点之间的最小距离
    error.resize(vertices_calulate_out.size());

    //通过循环遍历 vertices_calulate_out 中的每个输出顶点
    for (int i = 0; i < vertices_calulate_out.size(); ++i) {

        //获取当前输出顶点 outputPoint = vertices_calulate_out.at(i);
        QVector3D outputPoint = vertices_calulate_out.at(i);

        //初始化最小距离 minDistance 为一个很大的值 std::numeric_limits<double>::max();
        double minDistance = std::numeric_limits<double>::max();

        //在内部循环中，遍历所有输入顶点 vertices_calulate_input
        for (const QVector3D& inputPoint : vertices_calulate_input) {
            //计算当前输入顶点与当前输出顶点之间的距离 currentDistance
            double currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);

            //计算实际距离并更新 distance
            double distance = sqrt(currentDistance);


            //double distance = inputPoint.distanceTo(outputPoint);
            //如果当前距离小于 minDistance，则更新 minDistance 为当前距离
            if (distance < minDistance) {
                minDistance = distance;
            }
        }

        //将计算得到的最小距离 minDistance 存储在 error 变量的相应位置 error[i] 中，以便后续使用
        error[i] = minDistance;
    }


    //ui->openGLWidget->model_input.m_error=error;
    //设置 model_out 对象的 isDrawerror 属性为 true。这个属性可能用于控制是否显示错误信息。
    ui->openGLWidget->model_out.isDrawerror=true;

    //调用 model_out 对象的 calculateError 函数，传递之前计算得到的错误信息 error。这个函数可能用于处理错误信息并进行进一步的计算或准备数据以便在 UI 中显示。
    ui->openGLWidget->model_out.calculateError(error);

    //更新 openGLWidget，这可能会触发重绘操作，以便显示最新的模型和错误信息。
    ui->openGLWidget->update();

    //输出调试信息，显示 "showError"。这个语句用于在调试过程中输出一条消息，以确认代码执行到了这一步。
    qDebug()<<"showError";
}
