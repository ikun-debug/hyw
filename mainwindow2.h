#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include <mainwindow3.h>


class MainWindow;


namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();



private slots:
    void showBack();

    //void close();

    void showQuestion();


private:
    Ui::MainWindow2 *ui;
    MainWindow *mainwindow;

    MainWindow3 *mainwindow3;
};

#endif // MAINWINDOW2_H
