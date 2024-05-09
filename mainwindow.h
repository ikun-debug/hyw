#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLShaderProgram>
#include <QtMath>
#include "ashopenglwidget.h"
#include "mainwindow2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    QVector<QVector<float>> path;
//    QVector<float> temp;
//    QVector<float> ini;
//    QVector<float> end;
    Ui::MainWindow *ui;
    MainWindow2 *mainwindow2;

private slots:
    void open_input();
    void open_out();
    void clear_all();
    void showInput();
    void showOut();
    void showError();

    void showHelp();
    //void showAHideB();




//    void showX_Y();
//    void showX_Z();
//    void showY_Z();
//    void show_user();
//    void ini_user();
//    void end_user();

    void on_showError_clicked();
//    void on_pushButton_clicked();

//    void on_showError_clicked();

//    void on_showError_2_clicked();

//    void on_showData_clicked();

//    void on_Standard_clicked();

//    void on_showStandard_clicked();

//    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

//    void on_open_input_triggered();

private:

};
#endif // MAINWINDOW_H
