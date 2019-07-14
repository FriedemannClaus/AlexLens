#include "../../includes/GUIModule/helppanel.h"

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


HelpPanel::HelpPanel(QWidget *parent)
        : QWidget(parent)
{
    //QVBoxLayout *parameterList = new QVBoxLayout;

    //QLabel *label = new QLabel(this);
    //label->setText("Das Produkt dient zur Bilderklassifizierung auf heterogenen Plattformen mittels neuronaler Netze u.a. AlexNet. Es soll zwischen verschiedenen Betriebsmodi ausgewählt werden können. Zudem gibt es die Möglichkeit das vorhandene neuronale Netz mittels Transfer Learning zu trainieren. AlexNet ist der Name eines konvolutionellen neuronalen Netzwerks, das von Alex Krizhevsky entworfen und mit Ilya Sutskever und Krizhevskys PhD-Berater Geoffrey Hinton veröffentlicht wurde. AlexNet nahm am 30. September 2012 an der ImageNet Large Scale Visual Recognition Challenge teil. Unter Transfer Learning versteht man das Übertragen der Ergebnisse eines fertig trainierten neuronalen Netzes auf eine neue Aufgabe. Die fertig trainierten Layer werden dabei entweder konstant gehalten und nur am Output-Layer nachtrainiert, oder es werden einige oder alle Layer auf Basis des aktuellen Trainings-Stands weiter trainiert. Optimal Modus: der optimale Modus, in dem GPU und Intel Movidius Neural Compute Stick benutzt werden. Hohe Performance: der schnellste und performanteste Modus, in dem alle verfügbaren heterogenen Plattformen benutzt werden. Geringer Leistungsverbrauch: der Modus, in dem genau ein Intel Movidius Neural Compute Stick benutzt wird. Hohe Energieeffizient: der Modus, in dem alle verfügbaren Intel Movidius Neural Compute Sticks benutzt werden.");
    //QString* str = new QString("abs");

    //parameterList->addWidget(str);
}

HelpPanel::~HelpPanel()
{

}
