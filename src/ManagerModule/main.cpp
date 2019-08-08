#include "../../includes/GUIModule/mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <GUIModule/Subject.h>
#include "Manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Subject* subject = new Subject();
    Manager* manager = new Manager(subject);
    MainWindow* w = new MainWindow(manager, subject);
    w->show();

    return a.exec();
}