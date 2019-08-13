#include "../../includes/GUIModule/helpform.h"
#include "../../includes/GUIModule/ui_helpform.h"

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
                   "\nLayer auf Basis des aktuellen Trainings-Stands weiter trainiert.\n\n\n     Optimal Modus: der optimale Modus, in "
                   "dem ausschließlich CPU benutzt wird.\n\n     Hohe Performance: der schnellste und "
                   "performanteste Modus, in dem alle verfügbaren\nheterogenen Plattformen benutzt werden.\n\n     "
                   "Geringer Leistungsverbrauch: der Modus, in dem genau ein Intel Movidius Neural Compute\nStick benutzt wird."
                   "\n\n     Hohe Energieefizient: der Modus, in dem alle verfügbaren Intel Movidius Neural Compute\nSticks benutzt werden.");

    h_panel->addWidget(label);
    this->setLayout(h_panel);
}

HelpForm::~HelpForm()
{
    delete ui;
}

