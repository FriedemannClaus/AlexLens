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
    QLabel *label = new QLabel(this);
    label->setText("\n\n    Das Produkt dient zur Bilderklassifizierung auf heterogenen Plattformen mittels neuronaler\nNetze u.a. AlexNet. Es soll zwischen verschiedenen Betriebsmodi ausgewählt werden können.\nZudem gibt es die Möglichkeit das vorhandene neuronale Netz mittels Transfer Learning zu\ntrainieren.\n\n                   ist der Name eines konvolutionellen neuronalen Netzwerks, das von Alex Krizhevsky\nentworfen und mit Ilya Sutskever und Krizhevskys PhD-Berater Geoffrey Hinton veröffentlicht\nwurde. AlexNet nahm am 30. September 2012 an der ImageNet Large Scale Visual Recognition\nChallenge teil.\n\n    Unter                                  versteht man das Übertragen der Ergebnisse eines fertig trainierten\nneuronalen Netzes auf eine neue Aufgabe. Die fertig trainierten Layer werden dabei entweder\nkonstant gehalten und nur am Output-Layer nachtrainiert, oder es werden einige oder alle\nLayer auf Basis des aktuellen Trainings-Stands weiter trainiert.\n\n\n                                der optimale Modus, in dem GPU und Intel Movidius Neural Compute Stick\nbenutzt werden.\n\n                                      der schnellste und performanteste Modus, in dem alle verfügbaren\nheterogenen Plattformen benutzt werden.\n\n                                                       der Modus, in dem genau ein Intel Movidius Neural Compute\nStick benutzt wird.\n\n                                           der Modus, in dem alle verfügbaren Intel Movidius Neural Compute\nSticks benutzt werden.");
    QFont font_2;
    font_2.setPointSize(13);
    font_2.setBold(true);
    QLabel *label_2 = new QLabel(this);
    label_2->setText("AlexNet");
    label_2->setGeometry(QRect(14, 112, 51, 16));
    label_2->setFont(font_2);
    QLabel *label_3 = new QLabel(this);
    label_3->setText("Transfer Learning");
    label_3->setGeometry(QRect(51, 192, 151, 16));
    label_3->setFont(font_2);
    QFont font_4;
    font_4.setPointSize(13);
    font_4.setItalic(true);
    QLabel *label_4 = new QLabel(this);
    label_4->setText("Optimal Modus:");
    label_4->setGeometry(QRect(14, 288, 151, 16));
    label_4->setFont(font_4);
    QLabel *label_5 = new QLabel(this);
    label_5->setText("Hohe Performance:");
    label_5->setGeometry(QRect(14, 336, 151, 16));
    label_5->setFont(font_4);
    QLabel *label_6 = new QLabel(this);
    label_6->setText("Geringer Leistungsverbrauch:");
    label_6->setGeometry(QRect(14, 384, 191, 16));
    label_6->setFont(font_4);
    QLabel *label_7 = new QLabel(this);
    label_7->setText("Hohe Energieeffizient:");
    label_7->setGeometry(QRect(14, 432, 191, 16));
    label_7->setFont(font_4);
}

HelpPanel::~HelpPanel()
{

}
