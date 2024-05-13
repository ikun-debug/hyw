#include "mainwindow5.h"
#include "ui_mainwindow5.h"
#include <QLabel>
#include <QMovie>

MainWindow5::MainWindow5(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow5)
{
    ui->setupUi(this);

    //设置标题
    setWindowTitle("关于本软件");

    //固定窗口大小
    setFixedSize(600, 550); // 设置窗口大小为 900x400 像素


    // 获取指向QLabel的指针
    QLabel *label = ui->GIF1;

    // 创建一个QMovie对象并加载GIF图像
    QMovie *movie = new QMovie(":/demo/cheat.gif"); // 替换为GIF图像路径

    // 将QMovie对象设置到QLabel中
    label->setMovie(movie);

    // 开始播放GIF
    movie->start();

}

MainWindow5::~MainWindow5()
{
    delete ui;
}
