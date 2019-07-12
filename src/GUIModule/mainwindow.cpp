#include "GUIModule/mainwindow.h"
#include "GUIModule/ui_mainwindow.h"
#include<iostream>
#include<unistd.h>


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
