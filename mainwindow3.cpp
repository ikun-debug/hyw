#include "mainwindow3.h"
#include "ui_mainwindow3.h"
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
#include <QString>
#include <QHBoxLayout>



MainWindow3::MainWindow3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow3)
{
    ui->setupUi(this);

    this->setGeometry(600, 300, 800, 480);

    //设置标题
    setWindowTitle("疑难杂症");

    //固定窗口大小
    setFixedSize(800, 450); // 设置窗口大小为 900x400 像素

    // 获取指向QLabel的指针
    QLabel *label = ui->GIF2;

    // 创建一个QMovie对象并加载GIF图像
    QMovie *movie = new QMovie(":/demo/study .gif"); // 替换为GIF图像路径

    // 将QMovie对象设置到QLabel中
    label->setMovie(movie);

    // 开始播放GIF
    movie->start();


//    QWidget *box = new QWidget(this);
//    box->setObjectName("box");
//    box->setGeometry(300, 150, 200, 200);

//    QSpinBox *spinBox = new QSpinBox(box);

//    spinBox->setGeometry(50, 50, 150, 30);
//        /* 设置主窗口背景颜色，rgb颜色标准，a代表不透明度（0～100）*/
//        this->setStyleSheet("QWidget#bg{"
//                            "background-image: url(:/demo/4.png);"
//                            "background-color: rgba(100, 100, 100, 100%) "
//                            "}");

//        //spinBox = new QSpinBox(this);
//        //spinBox->setGeometry(350, 200, 150, 30);

//        /* 设置范围0～100 */
//        spinBox->setRange(0, 100);

//        /* 设置步长为10 */
//        spinBox->setSingleStep(10);

//        /* 设置初始值为100 */
//        spinBox->setValue(100);

//        /* 设置后缀 */
//        spinBox->setSuffix("%不透明度");

//        /* 信号槽连接 */
//        connect(spinBox,SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChanged(int)));


}

MainWindow3::~MainWindow3()
{
    delete ui;
}


//void MainWindow3::spinBoxValueChanged(int opacity)
//{
//   /* 转换为double数据类型 */
//   double  dobleopacity = (double)opacity / 100;

//   /* 设置窗体不透明度，范围是0.0～1.0。1则为不透明，0为全透明 */
//   this->setWindowOpacity(dobleopacity);
//}

//void MainWindow3::on_pushButton_clicked()
//{
//    QMessageBox* msgBox = new QMessageBox(this);
//    // 确保消息框关闭时自动删除
//    msgBox->setAttribute(Qt::WA_DeleteOnClose);


//    // 创建一个QLabel用于显示GIF图片
//    QLabel* label = new QLabel(msgBox);
//    QMovie* movie = new QMovie(":/demo/cheat.gif"); // 替换为你的GIF图片路径
//    label->setMovie(movie);
//    movie->start();


//    // 设置消息框内容
//    //\n可以显示下一行内容
//    QString message = "作者的邮箱是：******\n作者的电话是：******";

//    // 创建一个QLabel用于显示文本
//    QLabel* textLabel = new QLabel(message, msgBox);


//    // 不设置图标
//    msgBox->setIcon(QMessageBox::NoIcon);

//    // 设置消息框标题为自定义标题
//    msgBox->setWindowTitle("联系方式");

//    //将图片和文字放两边
//    QHBoxLayout* layout = new QHBoxLayout;
//    layout->addWidget(label);
//    layout->addWidget(textLabel);

//    msgBox->setLayout(layout);


//    // 设置消息框的大小
//    msgBox->resize(3000, 1200); // 设置宽度为600，高度为400

//    //设置消息框的最小的大小
//    msgBox->setMinimumSize(600, 400);

//    //根据消息框的大小策略为固定大小
//    msgBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

//    //msgBox->setWindowTitle("Message");
//    msgBox->show();

//    //QTimer::singleShot(2000, msgBox, &QMessageBox::accept);  // 在3秒后接受（关闭）消息框
//}

void MainWindow3::on_pushButton_clicked()
{
    QMessageBox* msgBox = new QMessageBox(this);
    // 确保消息框关闭时自动删除
    msgBox->setAttribute(Qt::WA_DeleteOnClose);

//    // 创建一个QLabel用于显示GIF图片
//    QLabel* label = new QLabel(msgBox);
//    QMovie* movie = new QMovie("path/to/your/gif/image.gif"); // 替换为你的GIF图片路径
//    label->setMovie(movie);
//    movie->start();

    // 设置消息框内容
    QString message = "作者的邮箱是：******\n作者的电话是：******";
    msgBox->setText(message);

    // 不设置图标
    msgBox->setIcon(QMessageBox::NoIcon);

    // 设置消息框标题为自定义标题
    msgBox->setWindowTitle("联系方式");

//    QVBoxLayout* layout = new QVBoxLayout;
//    layout->addWidget(label);
//    msgBox->setLayout(layout);

    msgBox->show();

    //QTimer::singleShot(2000, msgBox, &QMessageBox::accept);  // 在3秒后接受（关闭）消息框
}
