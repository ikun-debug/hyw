#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H

#include <QMainWindow>
#include <QSpinBox>


namespace Ui {
class MainWindow3;
}

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = 0);
    ~MainWindow3();

private:
    Ui::MainWindow3 *ui;

    //QSpinBox *spinBox;

private slots:
    //void spinBoxValueChanged(int);
};

#endif // MAINWINDOW3_H
