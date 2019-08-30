#include "GUIModule/mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <GUIModule/Subject.h>
#include "Manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_NUMERIC,"C");
    Subject* subject = new Subject();
    Manager* manager = new Manager(subject);
    a.setWindowIcon(QIcon(QString::fromStdString(manager->getProjectDir() + "Icon/iconLogo.png")));
    MainWindow* w = new MainWindow(manager, subject);
    w->show();

    return a.exec();
}