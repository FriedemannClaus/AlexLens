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
                   "\nNetze u.a. AlexNet. Es soll zwischen verschiedenen Betriebsmodi ausgewählt werden können."
                   "\nZudem gibt es die Möglichkeit das vorhandene neuronale Netz mittels Transfer Learning zu"
                   "\ntrainieren.\n\n    AlexNet ist der Name eines konvolutionellen neuronalen Netzwerks, das von Alex Krizhevsky"
                   "\nentworfen und mit Ilya Sutskever und Krizhevskys PhD-Berater Geoffrey Hinton veröffentlicht"
                   "\nwurde. AlexNet nahm am 30. September 2012 an der ImageNet Large Scale Visual Recognition"
                   "\nChallenge teil.\n\n    Unter Transfer Learning versteht man das Übertragen der Ergebnisse eines fertig trainierten"
                   "\nneuronalen Netzes auf eine neue Aufgabe. Die fertig trainierten Layer werden dabei entweder"
                   "\nkonstant gehalten und nur am Output-Layer nachtrainiert, oder es werden einige oder alle"
                   "\nLayer auf Basis des aktuellen Trainings-Stands weiter trainiert."
                   "\n\n    Die verschiedenen Betriebsmodi des Programms sind:"
                   "\nOptimal: Der optimale Modus, in dem so viel eigener Code benutzt wird, wie möglich. Es wird also die CPU benutzt. Ist AlexNet ausgewählt, wird zusätzlich die GPU verwendet."
                   "\nHohe Perfomance: Der schnellste und performanteste Modus, in dem alle verfügbaren heterogenen Plattformen benutzt werden."
                   "\nGeringer Leistungsverbrauch: Der Modus mit der geringsten maximalen Last, in dem genau ein Intel Movidius Neural Compute Stick benutzt wird."
                   "\nHohe Energieeffizienz: Der Modus, in dem alle verfügbaren Intel Movidius Neural Compute Sticks benutzt werden."
                   "\nBeim Trainieren gibt es nur einen Modus, bei dem die CPU verwendet wird. Dieser ist somit der optimale Modus."
                   "\n\n    Beim Trainieren muss der Datensatz folgendendermaßen formatiert sein:"
                   "\nAusgewählt wird ein Ordner, der die Ordner test, train und valid enthält. Diese wiederum enthalten die (gleichen) Objektklassen als Ordner, welche wiederum Bilder der jeweiligen Objekte enthalten."
                   "\nZur Veranschaulichung kann man sich unter https://cloud.viet-pham.de/s/eKRM5JyxBpAAjEn?path=%2F einen Beispieldatensatz herunterladen."
                   "\n\n    Der Open-Source-Code dieses Programms ist unter https://github.com/FriedemannClaus/AlexLens zu finden.");

    h_panel->addWidget(label);
    this->setLayout(h_panel);
}

HelpForm::~HelpForm()
{
    delete ui;
}

