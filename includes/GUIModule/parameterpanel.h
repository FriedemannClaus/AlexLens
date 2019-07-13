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
#include "../ManagerModule/Manager.h"
using namespace std;

class ParameterPanel : public QWidget
{
    Q_OBJECT

public:
    ParameterPanel(QWidget *parent = 0);
    ~ParameterPanel();

    void fillModes();
    void fillNeuralNets();

    inline void setManager(Manager* manager) {this->manager = manager;};

private slots:
    void run();
    void beenden();

private:
    QGridLayout* m_gridLayout;
    QPushButton* m_pushButton;
    QPushButton* m_pushButton2;
    QListWidget* modList;
    QListWidget* neuralNetsList;
    Manager* manager;

};

#endif // WIDGET_H
