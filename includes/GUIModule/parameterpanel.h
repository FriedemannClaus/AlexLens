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

class ParameterPanel : public QWidget, public IObserver
{
    Q_OBJECT

public:
    ParameterPanel(QWidget *parent = 0);
    ~ParameterPanel();

    void fillModes();
    void fillNeuralNets();

    inline void setClassifyTab(bool classifyTab) {this->classifyTab = classifyTab;}
    inline bool isClassifyTab() {return classifyTab;}

    inline void setManager(Manager* manager) {this->manager = manager;}

    inline void setInputPanel(InputPanel* inputPanel) {this->inputPanel = inputPanel;}

    inline void setOutputPanel(OutputClassifyPanel* outputPanel) {this->outputPanel = outputPanel;}
    void invokeUpdate() override;


    //inline void setInputTrainingPanel(InputPanel* inputTrainingPanel) {this->inputTrainingPanel = inputTrainingPanel;}

    //inline void setOutputTrainingPanel(OutputClassifyPanel* outputTrainingPanel) {this->outputTrainingPanel = outputTrainingPanel;}
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
    InputPanel* inputPanel;
    OutputClassifyPanel* outputPanel;
    bool runWasPushed = false;
    bool classifyTab = true;
    bool filesForTrainAdded = true;

};

#endif // WIDGET_H
