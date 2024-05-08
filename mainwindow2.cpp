#include "mainwindow2.h"
#include "ui_mainwindow2.h"
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


#include "mainwindow.h"


MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);

    //设置标题
    setWindowTitle("帮助");

    //固定窗口大小
    setFixedSize(1000, 550); // 设置窗口大小为 900x400 像素



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


    this->setStyleSheet("QWidget#bgWidget{"
                        "background-image: url(:/demo/4.png);"
                        "background-color: rgba(100, 100, 100, 50%) "
                        "}");



    //要让两个对象之间建立父子关系
    mainwindow = dynamic_cast<MainWindow*>(this->parent());


    //链接
    //返回界面1的按钮
    connect(ui->Back,SIGNAL(clicked()),this,SLOT(showBack()));

    //关闭按钮
    connect(ui->close, &QPushButton::clicked, this, &MainWindow2::close);



    //链接界面3
    mainwindow3 = new MainWindow3(this);
    connect(ui->showQuestion,SIGNAL(clicked()),this,SLOT(showQuestion()));

}



MainWindow2::~MainWindow2()
{
    delete ui;
}



//点击按钮返回第一个界面
void MainWindow2::showBack()
{
    mainwindow->show();
    this->close();
}


//第二种方法关闭界面
/*
void MainWindow2::close()
{
    close();
}
*/


//第三个界面
void MainWindow2::showQuestion()
{
    mainwindow3->show();
    //this->close();
}



/*
实现两个界面相互切换的小细节

自由跳转不卡死！

1.关键在创建B对象时一定要传入“this”,让A和B二者之间建立父子关系！！！

2.互相之间不可相互包含！所以，头文件只能包含一次（A包含B），另一个采用前置（即在B的头文件中只是声明class A,而不直接包含A的头文件），但是在cpp中还是需要包含A的头文件。

3.

setHidden(true);有先后顺序，不然跳转的时候会黑屏；

4.

 这里要用this->close(); 而deleteLater()会莫名其妙崩溃！;
*/
