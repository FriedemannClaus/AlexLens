#include "helpform.h"
#include "ui_helpform.h"

HelpForm::HelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpForm)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    //setWindowFlags( Qt::Window | Qt::MSWindowsFixedSizeDialogHint| Qt::WindowTitleHint | Qt::CustomizeWindowHint );

    h_panel = new QGridLayout();

    label = new QLabel(this);
    label->setText("\n    Das Produkt dient zur Bilderklassifizierung auf heterogenen Plattformen mittels neuronaler"
                   "\nNetze u.a. AlexNet. Es soll zwischen verschiedenen Betriebsmodi ausgewählt werden können:"
                   " \n\n     Optimal Modus: der optimale Modus, in "
                   "dem die CPU (im Falle AlexNet GPU) benutzt wird.\n\n     Hohe Performance: der schnellste und "
                   "performanteste Modus, in dem alle verfügbaren\nheterogenen Plattformen benutzt werden.\n\n     "
                   "Geringer Leistungsverbrauch: der Modus, in dem genau ein Intel Movidius Neural Compute\nStick benutzt wird."
                   "\n\n     Hohe Energieefizient: der Modus, in dem alle verfügbaren Intel Movidius Neural Compute\nSticks benutzt werden."
                   "\n\n\n     Zudem gibt es die Möglichkeit das vorhandene neuronale Netz mittels Transfer Learning zu"
                   "\ntrainieren.\n    Unter Transfer Learning versteht man das Übertragen der Ergebnisse eines fertig trainierten"
                   "\nneuronalen Netzes auf eine neue Aufgabe.\n   Beim Trainieren gibt es nur einen Modus, bei dem die CPU verwendet wird. Dieser ist somit\n"
                   " der optimale Modus. Beim Trainieren muss der Datensatz folgendendermaßen formatiert sein:"
                   "\n     Ausgewählt wird ein Ordner, der die Ordner test, train und valid enthält. Diese wiederum"
                   "\n enthalten die (gleichen) Objektklassen als Ordner, welche wiederum Bilder der\n jeweiligen Objekte enthalten."
                   "\n\n    Zur Veranschaulichung kann man sich einen Beispieldatensatz herunterladen unter"
                   "\nhttps://cloud.viet-pham.de/s/eKRM5JyxBpAAjEn?path=%2F"
                   "\n\n    Der Open-Source-Code dieses Programms ist zu finden unter"
                   "\nhttps://github.com/FriedemannClaus/AlexLens");

    h_panel->addWidget(label);
    this->setLayout(h_panel);
}

HelpForm::~HelpForm()
{
    delete ui;
}

