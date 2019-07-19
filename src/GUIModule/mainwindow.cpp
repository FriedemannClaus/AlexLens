#include "../../includes/GUIModule/mainwindow.h"
#include "../../includes/GUIModule/ui_mainwindow.h"
#include "../ManagerModule/Manager.h"
#include "../../includes/GUIModule/helpform.h"
#include "../../includes/GUIModule/statisticform.h"
#include <iostream>
#include <unistd.h>


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

    ui->parameterClassifyPanel->setManager(manager);
    ui->parameterTrainingPanel->setManager(manager);
    ui->inputClassifyPanel->setManager(manager);

    ui->parameterClassifyPanel->fillModes();
    ui->parameterClassifyPanel->fillNeuralNets();

    ui->parameterTrainingPanel->fillModes();
    ui->parameterTrainingPanel->fillNeuralNets();

    ui->parameterClassifyPanel->setInputClassifyPanel(ui->inputClassifyPanel);
    ui->parameterClassifyPanel->setOutputClassifyPanel(ui->outputClassifyPanel);
}

void MainWindow::on_actionHilfe_triggered()
{
    ui->statusBar->showMessage("Hilfe");

    HelpForm* h = new HelpForm();
    h->setFixedSize(QSize(650, 500));
    h->show();
    //this->hide();
}

void MainWindow::on_actionStatistiken_triggered()
{
    ui->statusBar->showMessage("Statistiken");

    StatisticForm* s = new StatisticForm();
    s->setFixedSize(QSize(590, 460));
    s->show();
}
