#include "parameterpanel.h"
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QString>

using namespace std;

ParameterPanel::ParameterPanel(QWidget *parent)
        : QWidget(parent)
{
    //resize(640, 480);

    m_gridLayout = new QGridLayout(this);

    QGroupBox *vertikalGroupBox = new QGroupBox(this);
    QVBoxLayout *parameterList = new QVBoxLayout;

    modList = new QListWidget; //will be filled in fillModes()
    neuralNetsList = new QListWidget; // will be filled in fillNeuralNets()

    parameterList->addWidget(modList);
    parameterList->addWidget(neuralNetsList);

    vertikalGroupBox->setLayout(parameterList);

    m_gridLayout->addWidget(vertikalGroupBox);

    m_pushButton = new QPushButton("run", this);
    m_pushButton2 = new QPushButton("Beenden", this);

    connect(m_pushButton, &QPushButton::clicked, this, &ParameterPanel::run);
    connect(m_pushButton2, &QPushButton::clicked, this, &ParameterPanel::beenden);

    QGroupBox *horizonatlGroupBox = new QGroupBox(this);
    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(m_pushButton2);
    buttons->addWidget(m_pushButton);
    horizonatlGroupBox->setLayout(buttons);
    m_gridLayout->addWidget(horizonatlGroupBox);
}

ParameterPanel::~ParameterPanel()
{

}

void ParameterPanel::run()
{
    QMessageBox::warning(this, "RUN", "RUN" );

}

void ParameterPanel::beenden()
{
    QMessageBox::warning(this, "BEENDEN", "BEENDEN" );
}

void ParameterPanel::fillModes() {
    list<string> modes = this->manager->getDefaultModes();
    list<string>::iterator it;
    for (it = modes.begin(); it != modes.end(); ++it) {
        string item = *it;
        modList->addItem(QString::fromStdString(item));
    }
}

void ParameterPanel::fillNeuralNets() {
    list<string> nets = this->manager->getDeafaultNeuralNets();
    list<string>::iterator it;
    for (it = nets.begin(); it != nets.end(); ++it) {
        string item = *it;
        neuralNetsList->addItem(QString::fromStdString(item));
    }
}