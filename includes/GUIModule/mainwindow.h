#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../src/ManagerModule/Manager.h"

namespace Ui {
    class MainWindow;
}

/**
 * Class MainWindow. The main window of software.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructor for class MainWindow.
     * @param parent
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * Constructor for class MainWindow.
     * @param manager main manager of program to set
     * @param subject ???
     * @param parent
     */
    MainWindow(Manager* manager, Subject* subject, QWidget *parent = nullptr);

    /**
     * Destructor for class MainWindow.
     */
    ~MainWindow();

private slots:
    /**
     * Show HelpFrom.
     */
    void on_actionHilfe_triggered();

    /**
     * Show StatisticForm.
     */
    void on_actionStatistiken_triggered();

private:
    Ui::MainWindow *ui; // Skeleton of MainWindow
    Manager* manager; // Main manager of program
};

#endif // MAINWINDOW_H
