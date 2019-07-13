#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFileDialog>
#include<QGraphicsScene>
#include "../ManagerModule/Manager.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(Manager* manager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    Manager* manager;
};

#endif // MAINWINDOW_H
