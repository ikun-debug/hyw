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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainwindow2 = new MainWindow2(this);
    //connect(mainwindow2,SIGNAL(bSignal()),this,SLOT(showAHideB()));


    mainwindow4 = new MainWindow4(this);



    mainwindow5 = new MainWindow5(this);




    mainwindow3 = new MainWindow3(this);




    //设置标题
    setWindowTitle("三维网格模型误差分析工具");

    //固定窗口大小
    setFixedSize(1300, 700); // 设置窗口大小为 1100x600 像素



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
    connect(ui->open_input,SIGNAL(triggered()),this,SLOT(open_input()));
    connect(ui->open_out,SIGNAL(triggered()),this,SLOT(open_out()));
    connect(ui->clear_all,SIGNAL(triggered()),this,SLOT(clear_all()));
    connect(ui->showInput,SIGNAL(clicked()),this,SLOT(showInput()));
    connect(ui->showOut,SIGNAL(clicked()),this,SLOT(showOut()));
    connect(ui->showError,SIGNAL(clicked()),this,SLOT(showError()));
    connect(ui->showError,SIGNAL(clicked()),this,SLOT(&MainWindow::on_showMessage_clicked));


    connect(ui->showHelp,SIGNAL(clicked()),this,SLOT(showHelp()));

    connect(ui->about,SIGNAL(triggered(bool)),this, SLOT(show_about()));


    connect(ui->color,SIGNAL(triggered(bool)),this, SLOT(show_color()));

    connect(ui->action_input,SIGNAL(triggered(bool)), this, SLOT(on_action_input_triggered()));

    //connect((ui->action_output, SIGNAL(triggered(bool)), this, SLOT(on_action_output_triggered())));


    connect(ui->action_error,SIGNAL(triggered(bool)),this,SLOT(on_action_error_triggered()));


    connect(ui->show_window3,SIGNAL(triggered(bool)),this,SLOT(show_window3()));

    connect(ui->help,SIGNAL(triggered(bool)),this,SLOT(help()));

    //视角调整范围
    ui->Slider_xrot->setRange(-180,180);
    ui->Slider_yrot->setRange(-180,180);
    ui->Slider_zrot->setRange(-180,180);
    ui->Slider_xtrans->setRange(-500,500);
    ui->Slider_ytrans->setRange(-500,500);
    ui->Slider_ztrans->setRange(-500,500);
    ui->xrot->setRange(-180,180);
    ui->yrot->setRange(-180,180);
    ui->zrot->setRange(-180,180);
    ui->xtrans->setRange(-500,500);
    ui->ytrans->setRange(-500,500);
    ui->ztrans->setRange(-500,500);
    //视角调整
    void(QDoubleSpinBox:: *ptrxtrans)(double)=&QDoubleSpinBox::valueChanged;
    connect(ui->xtrans,ptrxtrans,ui->Slider_xtrans,&QSlider::setValue);
    void(QDoubleSpinBox:: *ptrytrans)(double)=&QDoubleSpinBox::valueChanged;
    connect(ui->ytrans,ptrytrans,ui->Slider_ytrans,&QSlider::setValue);
    void(QDoubleSpinBox:: *ptrztrans)(double)=&QDoubleSpinBox::valueChanged;
    connect(ui->ztrans,ptrztrans,ui->Slider_ztrans,&QSlider::setValue);
    void(QDoubleSpinBox:: *ptrxrot)(double)=&QDoubleSpinBox::valueChanged;
    connect(ui->xrot,ptrxrot,ui->Slider_xrot,&QSlider::setValue);
    void(QDoubleSpinBox:: *ptryrot)(double)=&QDoubleSpinBox::valueChanged;
    connect(ui->yrot,ptryrot,ui->Slider_yrot,&QSlider::setValue);
    void(QDoubleSpinBox:: *ptrzrot)(double)=&QDoubleSpinBox::valueChanged;
    connect(ui->zrot,ptrzrot,ui->Slider_zrot,&QSlider::setValue);
    connect(ui->Slider_xtrans,&QSlider::valueChanged,ui->xtrans,&QDoubleSpinBox::setValue);
    connect(ui->Slider_ytrans,&QSlider::valueChanged,ui->ytrans,&QDoubleSpinBox::setValue);
    connect(ui->Slider_ztrans,&QSlider::valueChanged,ui->ztrans,&QDoubleSpinBox::setValue);
    connect(ui->Slider_xrot,&QSlider::valueChanged,ui->xrot,&QDoubleSpinBox::setValue);
    connect(ui->Slider_yrot,&QSlider::valueChanged,ui->yrot,&QDoubleSpinBox::setValue);
    connect(ui->Slider_zrot,&QSlider::valueChanged,ui->zrot,&QDoubleSpinBox::setValue);
    connect(ui->Slider_xrot,&QSlider::valueChanged,[=](){
        ui->openGLWidget->xrot=ui->xrot->value();
        ui->openGLWidget->update();
    });
    connect(ui->Slider_yrot,&QSlider::valueChanged,[=](){
        ui->openGLWidget->yrot=ui->yrot->value();
        ui->openGLWidget->update();
    });
    connect(ui->Slider_zrot,&QSlider::valueChanged,[=](){
        ui->openGLWidget->zrot=ui->zrot->value();
        ui->openGLWidget->update();
    });

    connect(ui->Slider_xtrans,&QSlider::valueChanged,[=](){
        ui->openGLWidget->xtrans=ui->xtrans->value();
        ui->openGLWidget->update();
    });
    connect(ui->Slider_ytrans,&QSlider::valueChanged,[=](){
        ui->openGLWidget->ytrans=ui->ytrans->value();
        ui->openGLWidget->update();
    });
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



void MainWindow::show_color()
{
    mainwindow4->show();
}


void MainWindow::show_window3()
{
    mainwindow3->show();
}


void MainWindow::help()
{

    mainwindow2->show();
}



//void MainWindow::showHelp()
//{
//    this->hide();
//    mainwindow2->show();
//}


/*
void MainWindow::showAHideB()
{
    this->show();
    mainwindow2->hide();
}
*/

//void MainWindow::on_showStandard_clicked()
//{
//    QMessageBox* msgBox = new QMessageBox(this);
//        msgBox->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时自动删除
//        msgBox->setText("误差的颜色标准为：");
//        msgBox->setIcon(QMessageBox::NoIcon);  // 设置图标为无图标
//        msgBox->setWindowTitle("Standard");
//        msgBox->show();
//}



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


void MainWindow::open_input()
{
    qDebug()<<"open_input";
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "./", tr("Images(*.obj)"));
    //ui->openGLWidget->model_input.load(":/res/model/input_muyulu.obj");
    ui->openGLWidget->model_input.load(filename);
    ui->openGLWidget->update();
}

void MainWindow::open_out()
{
    qDebug()<<"open_out";
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "./", tr("Images(*.obj)"));
    ui->openGLWidget->model_out.load(filename);
    //ui->openGLWidget->model_out.load(":/res/model/out_muyulu.obj");
    ui->openGLWidget->update();
}

void MainWindow::clear_all()
{

    qDebug()<<"clear_all";
    ui->openGLWidget->model_input=LoadObj();
    ui->openGLWidget->model_out=LoadObj();
    ui->openGLWidget->update();
}

void MainWindow::showInput()
{
    ui->openGLWidget->model_input.isDraw=true;
    ui->openGLWidget->model_out.isDraw=false;
    ui->openGLWidget->update();
    qDebug()<<"showInput";
}

void MainWindow::showOut()
{
    ui->openGLWidget->model_input.isDraw=false;
    ui->openGLWidget->model_out.isDraw=true;
    ui->openGLWidget->update();
    qDebug()<<"showOut";
}

void MainWindow::showError()
{
    QVector<QVector3D> vertices_calulate_input=ui->openGLWidget->model_input.m_vertices_calculate;
    QVector<QVector3D> vertices_calulate_out=ui->openGLWidget->model_out.m_vertices_calculate;
    QVector<float> error;

//    error.resize(vertices_calulate_input.size());
//    for (int i = 0; i < vertices_calulate_input.size(); ++i) {
//        QVector3D inputPoint = vertices_calulate_input.at(i);
//        float minDistance = std::numeric_limits<double>::max();
//        for (const QVector3D& outputPoint : vertices_calulate_out) {
//            float currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);
//            float distance = sqrt(currentDistance);
//            //double distance = inputPoint.distanceTo(outputPoint);
//            if (distance < minDistance) {
//                minDistance = distance;
//            }
//        }
//        error[i] = minDistance;
//    }

    error.resize(vertices_calulate_out.size());
    for (int i = 0; i < vertices_calulate_out.size(); ++i) {
        QVector3D outputPoint = vertices_calulate_out.at(i);
        double minDistance = std::numeric_limits<double>::max();
        for (const QVector3D& inputPoint : vertices_calulate_input) {
            double currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);
            double distance = sqrt(currentDistance);
            //double distance = inputPoint.distanceTo(outputPoint);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
        error[i] = minDistance;
    }
    //ui->openGLWidget->model_input.m_error=error;
    ui->openGLWidget->model_out.isDrawerror=true;
    ui->openGLWidget->model_out.calculateError(error);
    ui->openGLWidget->update();

    qDebug()<<"showError";
}





void MainWindow::on_showError_clicked()
{
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时自动删除
    msgBox->setText("计算较慢 稍等！");
    msgBox->setIcon(QMessageBox::Information);  // 设置图标为信息图标
    msgBox->setWindowTitle("Message");
    msgBox->show();

    QTimer::singleShot(2000, msgBox, &QMessageBox::accept);  // 在3秒后接受（关闭）消息框
}






void MainWindow::on_action_input_triggered()
{
    ui->openGLWidget->model_input.isDraw=true;
    ui->openGLWidget->model_out.isDraw=false;
    ui->openGLWidget->update();
    qDebug()<<"showInput";
}






void MainWindow::on_action_output_triggered()
{
    ui->openGLWidget->model_input.isDraw=false;
    ui->openGLWidget->model_out.isDraw=true;
    ui->openGLWidget->update();
    qDebug()<<"showOut";
}

void MainWindow::on_action_error_triggered()
{
    QVector<QVector3D> vertices_calulate_input=ui->openGLWidget->model_input.m_vertices_calculate;
    QVector<QVector3D> vertices_calulate_out=ui->openGLWidget->model_out.m_vertices_calculate;
    QVector<float> error;

//    error.resize(vertices_calulate_input.size());
//    for (int i = 0; i < vertices_calulate_input.size(); ++i) {
//        QVector3D inputPoint = vertices_calulate_input.at(i);
//        float minDistance = std::numeric_limits<double>::max();
//        for (const QVector3D& outputPoint : vertices_calulate_out) {
//            float currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);
//            float distance = sqrt(currentDistance);
//            //double distance = inputPoint.distanceTo(outputPoint);
//            if (distance < minDistance) {
//                minDistance = distance;
//            }
//        }
//        error[i] = minDistance;
//    }

    error.resize(vertices_calulate_out.size());
    for (int i = 0; i < vertices_calulate_out.size(); ++i) {
        QVector3D outputPoint = vertices_calulate_out.at(i);
        double minDistance = std::numeric_limits<double>::max();
        for (const QVector3D& inputPoint : vertices_calulate_input) {
            double currentDistance = QVector3D::dotProduct(inputPoint - outputPoint, inputPoint - outputPoint);
            double distance = sqrt(currentDistance);
            //double distance = inputPoint.distanceTo(outputPoint);
            if (distance < minDistance) {
                minDistance = distance;
            }
        }
        error[i] = minDistance;
    }
    //ui->openGLWidget->model_input.m_error=error;
    ui->openGLWidget->model_out.isDrawerror=true;
    ui->openGLWidget->model_out.calculateError(error);
    ui->openGLWidget->update();

    qDebug()<<"showError";
}
