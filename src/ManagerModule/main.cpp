#include "GUIModule/mainwindow.h"
#include <QApplication>
#include<QFileDialog>
#include "Manager.h"
#include "TrainingModule/ITraining.h"
#include "../MathModule/Skalar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager* manager = new Manager();
    MainWindow* w = new MainWindow(manager);
    w->show();

    return a.exec();
}
