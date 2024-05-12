#include "mainwindow5.h"
#include "ui_mainwindow5.h"

MainWindow5::MainWindow5(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow5)
{
    ui->setupUi(this);

    //设置标题
    setWindowTitle("关于本软件");

    //固定窗口大小
    setFixedSize(500, 550); // 设置窗口大小为 900x400 像素





}

MainWindow5::~MainWindow5()
{
    delete ui;
}
