#include "parameterpanel.h"
#include "../PlatformModule/ModeUtil.h"

#include <QHBoxLayout>
#include <QGroupBox>
#include <QListWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <string>
#include <QApplication>

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

    m_pushButton = new QPushButton("Reset", this);
    m_pushButton2 = new QPushButton("Start", this);

    connect(m_pushButton, &QPushButton::clicked, this, &ParameterPanel::reset);
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
    if((classifyTab && inputPanel->isImageAdded()) || (!classifyTab && inputPanel->isImageAdded())) {
        string currentMode = this->modList->currentItem()->text().toStdString();
        string currentNeuralNet = this->neuralNetsList->currentItem()->text().toStdString();
        this->manager->setMode(ModeUtil::whichModeClassify(currentMode));
        this->manager->setNeuralNet(currentNeuralNet);
        if (!this->manager->isRunnable()) {
            this->manager->clearImagePaths();
            this->inputPanel->clearPanel();
            this->inputPanel->clearPreviewImages();
            this->outputPanel->clearPanel();
            QMessageBox::warning(this, "Start", "Diese Auswahl von Parametern ist nicht ausführbar!" );
            return;
        }
        this->runWasPushed = true;


        if (classifyTab) {
            this->outputPanel->clearPanel();
            this->outputPanel->addPreviewImages(this->inputPanel->getPreviewImages());
            //reloading the gui
            this->outputPanel->setVisible(false);
            this->outputPanel->repaint();
            this->outputPanel->setVisible(true);
            QCoreApplication::processEvents();

            this->manager->runClassify();

            this->inputPanel->clearPreviewImages();

        } else {
            this->outputPanel->clearPanel();
            this->outputPanel->addLoadingIcon();
            this->inputPanel->clearPreviewImages();
            //reloading the gui
            this->outputPanel->setVisible(false);
            this->outputPanel->repaint();
            this->outputPanel->setVisible(true);
            QCoreApplication::processEvents();

            this->manager->runTraining();
        }
        this->manager->clearImagePaths();
        this->inputPanel->clearPanel();


    } else {
        if(classifyTab) {
            QMessageBox::warning(this, "Start", "Fügen Sie zumindest ein Bild ein" );
        } else {
            QMessageBox::warning(this, "Start", "Fügen Sie zumindest ein Datensatz ein");
        }
    }

}

void ParameterPanel::reset()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Reset");
    msgBox.setText("Sollten die Panels resettet werden?");
    //msgBox.setInformativeText("Die Panels links und rechts werden leer");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Reset);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch(ret) {
        case QMessageBox::Reset:
            if (classifyTab) {
                //classify tab resetting
                this->inputPanel->clearPanel();
                this->inputPanel->clearPreviewImages();
                this->outputPanel->clearPanel();
                this->manager->clearImagePaths();

            } else {
                //training tab resetting
                this->inputPanel->clearPanel();
                this->inputPanel->clearPreviewImages();
                this->outputPanel->clearPanel();
                this->manager->setDatasetPath("");
            }
            break;
        case QMessageBox::Cancel:
            //do not nothing
            break;
        default:
            //should never be reached
            break;
    }

    /*
    if (runWasPushed) {
        QMessageBox::warning(this, "Beenden", "Prozess wird beendet!");
    } else {
        QMessageBox::warning(this, "Beenden", "Nichts zu beenden!");
    }*/
}

void ParameterPanel::fillModes() {
    list<string> modes;
    if (classifyTab) {
        modes = this->manager->getDefaultModesClassify();
    }else {
        modes = this->manager->getDefaultModesTraining();
    }
    list<string>::iterator it;
    for (it = modes.begin(); it != modes.end(); ++it) {
        string item_str = *it;
        string item_name = item_str.substr(0,item_str.find(':'));
        string item_toolTip = item_str.substr(item_str.find(':')+2);
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(item_name));
        item->setToolTip(QString::fromStdString(item_toolTip));
        modList->addItem(item);
    }
    modList->setCurrentRow(0);
}

void ParameterPanel::fillNeuralNets() {
    if(!classifyTab) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString("alexnet"));
        neuralNetsList->addItem(item);
        neuralNetsList->setCurrentRow(0);
        return;
    }
    list<string> nets = this->manager->getDeafaultNeuralNets();
    list<string>::iterator it;
    for (it = nets.begin(); it != nets.end(); ++it) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(*it));
        neuralNetsList->addItem(item);
    }
    neuralNetsList->setCurrentRow(0);
}

void ParameterPanel::invokeUpdate() {
    if(classifyTab) {
        int i = 0;
        neuralNetsList->clear();
        for (string net:this->manager->getDeafaultNeuralNets()) {
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(net));
            neuralNetsList->addItem(item);
            i++;
        }
        neuralNetsList->setCurrentRow(0);
    }
}
