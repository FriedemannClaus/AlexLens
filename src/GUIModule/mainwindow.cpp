#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpform.h"
#include "statisticform.h"
#include "Subject.h"


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

    //TODO
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
    ui->inputTrainingPanel->setButtonText("Datensatz einfügen");
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
}

void MainWindow::on_actionHilfe_triggered()
{
    HelpForm* h = new HelpForm();
    h->adjustSize();
    h->show();
}

void MainWindow::on_actionStatistiken_triggered()
{
    StatisticForm* s = new StatisticForm();
    s->setPlatformManager(this->manager->getExecutor()->getPlatformManager());
    s->printStatistic();
    s->adjustSize();
    s->show();
}
