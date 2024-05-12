#ifndef MAINWINDOW4_H
#define MAINWINDOW4_H

#include <QMainWindow>

namespace Ui {
class MainWindow4;
}

class MainWindow4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow4(QWidget *parent = 0);
    ~MainWindow4();

private:
    Ui::MainWindow4 *ui;
};

#endif // MAINWINDOW4_H
