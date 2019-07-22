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
    ui->inputClassifyPanel->setClassifyTab(true);
    ui->inputTrainingPanel->setManager(manager);
    ui->inputTrainingPanel->setClassifyTab(false);

    ui->outputClassifyPanel->setManager(manager);

    ui->parameterClassifyPanel->fillModesClassify();
    ui->parameterClassifyPanel->fillNeuralNets();
    ui->parameterTrainingPanel->fillModesTraining();
    ui->parameterTrainingPanel->fillNeuralNets();

    ui->parameterClassifyPanel->setInputClassifyPanel(ui->inputClassifyPanel);
    ui->parameterClassifyPanel->setOutputClassifyPanel(ui->outputClassifyPanel);
    ui->parameterTrainingPanel->setInputTrainingPanel(ui->inputTrainingPanel);
    ui->parameterTrainingPanel->setOutputTrainingPanel(ui->outputTrainingPanel);

    //ATTCAHING OBSERVER
    this->manager->getSubject()->attachObserver(ui->outputClassifyPanel);
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
