#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //创建QApplication对象a，初始化qt的底层资源和属性
    QApplication a(argc, argv);

    //初始化窗口、窗口显示
    MainWindow w;
    w.show();

    //启动qt的事件循环
    return a.exec();

    //QApplication::exec执行事件循环，等待可能到来的事件并分发它们到相应的控件。
    //这个函数会阻塞直到QApplication::quit被调用。
    //程序最后返回的是事件循环的退出代码。
}
