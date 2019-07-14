#include "../../includes/GUIModule/parameterpanel.h"
#include "../PlatformModule/ModeUtil.h"
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
#include <string>

using namespace std;

ParameterPanel::ParameterPanel(QWidget *parent)
        : QWidget(parent)
{
    //resize(640, 480);

    m_gridLayout = new QGridLayout(this);

    QGroupBox *vertikalGroupBox = new QGroupBox(this);
    QVBoxLayout *parameterList = new QVBoxLayout;

    QLabel *label = new QLabel(this);
    label->setText("Betriebsmodus");
    parameterList->addWidget(label);

    modList = new QListWidget; //will be filled in fillModes()
    neuralNetsList = new QListWidget; // will be filled in fillNeuralNets()

    parameterList->addWidget(modList);

    QLabel *label_2 = new QLabel(this);
    label_2->setText("Neuronales Netz");
    parameterList->addWidget(label_2);

    parameterList->addWidget(neuralNetsList);

    vertikalGroupBox->setLayout(parameterList);

    m_gridLayout->addWidget(vertikalGroupBox);

    m_pushButton = new QPushButton("Beenden", this);
    m_pushButton2 = new QPushButton("Start", this);

    connect(m_pushButton, &QPushButton::clicked, this, &ParameterPanel::beenden);
    connect(m_pushButton2, &QPushButton::clicked, this, &ParameterPanel::start);

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

void ParameterPanel::start()
{
    string currentMode = this->modList->currentItem()->text().toStdString();
    string currentNeuralNet = this->neuralNetsList->currentItem()->text().toStdString();
    //cout << currentMode << endl;
    this->manager->setMode(ModeUtil::whichMode(currentMode));
    this->manager->setNeuralNet(currentNeuralNet);
    this->runWasPushed = true;
    QMessageBox::warning(this, "Start", "Start" );

}

void ParameterPanel::beenden()
{
    if (runWasPushed) {
        QMessageBox::warning(this, "Beenden", "Prozess wird beendet!" );
    } else {
        QMessageBox::warning(this, "Beenden", "Nichts zu beenden!" );
    }
}

void ParameterPanel::fillModes() {
    list<string> modes = this->manager->getDefaultModes();
    list<string>::iterator it;
    for (it = modes.begin(); it != modes.end(); ++it) {
        string item = *it;
        modList->addItem(QString::fromStdString(item));
    }
    modList->setCurrentRow(0);
}

void ParameterPanel::fillNeuralNets() {
    list<string> nets = this->manager->getDeafaultNeuralNets();
    list<string>::iterator it;
    for (it = nets.begin(); it != nets.end(); ++it) {
        string item = *it;
        neuralNetsList->addItem(QString::fromStdString(item));
    }
    neuralNetsList->setCurrentRow(0);
}
