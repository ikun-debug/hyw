#ifndef MAINWINDOW5_H
#define MAINWINDOW5_H

#include <QMainWindow>

namespace Ui {
class MainWindow5;
}

class MainWindow5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow5(QWidget *parent = 0);
    ~MainWindow5();

private:
    Ui::MainWindow5 *ui;
};

#endif // MAINWINDOW5_H
