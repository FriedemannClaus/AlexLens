#include "../../includes/GUIModule/mainwindow.h"
#include "../../includes/GUIModule/ui_mainwindow.h"
#include "../ManagerModule/Manager.h"
#include "../../includes/GUIModule/helpform.h"
#include "../../includes/GUIModule/statisticform.h"
#include <iostream>
#include <unistd.h>
#include "../../includes/GUIModule/Subject.h"
//#include "../ManagerModule/Executor.h"


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



MainWindow::MainWindow(Manager* manager, Subject* subject, QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{

    //Executor* executor = new Executor;
    //executor->panel = ui->outputClassifyPanel;
    //manager->executor = executor;

    //ui->outputClassifyPanel->setSubject(subject);

    ui->setupUi(this);
    this->manager = manager;

    ui->parameterClassifyPanel->setManager(manager);
    ui->parameterTrainingPanel->setManager(manager);
    ui->inputClassifyPanel->setManager(manager);
    ui->outputClassifyPanel->setManager(manager);
    ui->outputTrainingPanel->setManager(manager);

    ui->inputClassifyPanel->setClassifyTab(true);
    ui->inputTrainingPanel->setManager(manager);
    ui->inputTrainingPanel->setClassifyTab(false);
    ui->parameterClassifyPanel->setClassifyTab(true);
    ui->parameterTrainingPanel->setClassifyTab(false);
    ui->outputClassifyPanel->setClassifyTab(true);
    ui->outputTrainingPanel->setClassifyTab(false);

    ui->outputClassifyPanel->setManager(manager);

    ui->parameterClassifyPanel->fillModes();
    ui->parameterClassifyPanel->fillNeuralNets();
    ui->parameterTrainingPanel->fillModes();
    ui->parameterTrainingPanel->fillNeuralNets();

    ui->parameterClassifyPanel->setInputPanel(ui->inputClassifyPanel);
    ui->parameterClassifyPanel->setOutputPanel(ui->outputClassifyPanel);
    ui->parameterTrainingPanel->setInputPanel(ui->inputTrainingPanel);
    ui->parameterTrainingPanel->setOutputPanel(ui->outputTrainingPanel);

    //ATTCAHING OBSERVER
    this->manager->getSubject()->attachObserver(ui->outputClassifyPanel);
    this->manager->getSubject()->attachObserver(ui->outputTrainingPanel);
    this->manager->getSubject()->attachObserver(ui->parameterClassifyPanel);
    this->manager->getSubject()->attachObserver(ui->parameterTrainingPanel);
    // = ui->outputClassifyPanel;
}

void MainWindow::on_actionHilfe_triggered()
{
    //ui->statusBar->showMessage("Hilfe");

    HelpForm* h = new HelpForm();
    h->adjustSize();
    //h->setFixedSize(QSize(650, 500));
    h->show();
    //this->hide();
}

void MainWindow::on_actionStatistiken_triggered()
{
    //ui->statusBar->showMessage("Statistiken");

    StatisticForm* s = new StatisticForm();
    s->adjustSize();
    //s->setFixedSize(QSize(590, 460));
    s->show();
}
