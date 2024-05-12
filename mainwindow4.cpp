#include "mainwindow4.h"
#include "ui_mainwindow4.h"

MainWindow4::MainWindow4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow4)
{
    ui->setupUi(this);


    //设置标题
    setWindowTitle("色差表");

    //固定窗口大小
    setFixedSize(700, 400); // 设置窗口大小为 1100x600 像素


}

MainWindow4::~MainWindow4()
{
    delete ui;
}
