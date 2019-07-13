#include "../../includes/GUIModule/mainwindow.h"
#include "../../includes/GUIModule/ui_mainwindow.h"
//#include "ui_mainwindow.h"
#include "../../includes/ManagerModule/Manager.h"
#include "../../includes/GUIModule/helpform.h"
#include <iostream>
#include <unistd.h>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}



MainWindow::MainWindow(Manager* manager, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->manager = manager;
    //ui->parameterPanel->setManager(manager);
    //ui->parameterPanel->fillModes();
    //ui->parameterPanel->fillNeuralNets();
    ui->parameterClassifyPanel->setManager(manager);
    ui->parameterTrainingPanel->setManager(manager);

    ui->parameterClassifyPanel->fillModes();
    ui->parameterClassifyPanel->fillNeuralNets();

    ui->parameterTrainingPanel->fillModes();
    ui->parameterTrainingPanel->fillNeuralNets();
}

void MainWindow::on_actionStatistiken_triggered()
{
    ui->statusBar->showMessage("Statistiken ");
}

void MainWindow::on_actionHilfe_triggered()
{
    ui->statusBar->showMessage("Hilfe ");

    HelpForm* h = new HelpForm();
    h->show();
    //hide();
}
