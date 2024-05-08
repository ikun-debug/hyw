#include "mainwindow3.h"
#include "ui_mainwindow3.h"
#include <QWindow>
#include <QWidget>


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
