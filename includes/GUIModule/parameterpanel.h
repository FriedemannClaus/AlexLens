#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include <QWidget>

#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QListWidget>

#include <list>
#include <iterator>
#include <iostream>
#include "../../src/ManagerModule/Manager.h"
#include "inputpanel.h"
#include "outputclassifypanel.h"

using namespace std;

class ParameterPanel : public QWidget
{
    Q_OBJECT

public:
    ParameterPanel(QWidget *parent = 0);
    ~ParameterPanel();

    void fillModesClassify();
    void fillModesTraining();
    void fillNeuralNets();

    inline void setManager(Manager* manager) {this->manager = manager;}

    inline void setInputClassifyPanel(InputPanel* inputClassifyPanel) {this->inputClassifyPanel = inputClassifyPanel;}

    inline void setOutputClassifyPanel(OutputClassifyPanel* outputClassifyPanel) {this->outputClassifyPanel = outputClassifyPanel;}
private slots:
    void start();
    void beenden();

private:
    QGridLayout* m_gridLayout;
    QPushButton* m_pushButton;
    QPushButton* m_pushButton2;
    QListWidget* modList;
    QListWidget* neuralNetsList;
    Manager* manager;
    InputPanel* inputClassifyPanel;
    OutputClassifyPanel* outputClassifyPanel;
    bool runWasPushed = false;

};

#endif // WIDGET_H
