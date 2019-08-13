#include "../../includes/GUIModule/statisticform.h"
#include "../../includes/GUIModule/ui_statisticform.h"
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <string>
#include <iostream>
using namespace std;

StatisticForm::StatisticForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticForm)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

}

StatisticForm::~StatisticForm()
{
    delete ui;
}

void StatisticForm::printStatistic() {

    list<Platform *> listPlatforms = platformManager->getAvailablePlatforms();

    main_panel = new QGridLayout();

    for (auto platform:listPlatforms)
    {
        QGroupBox *horizontalGroupBoxPlatform = new QGroupBox(this);
        QHBoxLayout *labelsAndGraphs = new QHBoxLayout();

        QGroupBox *vertikalGroupBoxLabels = new QGroupBox(this);
        QVBoxLayout *labels = new QVBoxLayout(this);
        QLabel *name = new QLabel(this);
        name->setText(QString::fromStdString(toString(platform->getType()) + ' ' + platform->getId()));
        name->setAlignment(Qt::AlignCenter);
        PlatformStatistic platformStatistic = platform->getStatistic();
        QLabel *label = new QLabel(this);
        label->setText(QString::fromStdString("FLOPS: " + to_string(platformStatistic.getFLOPS())));
        QLabel *label_2 = new QLabel(this);
        label_2->setText(QString::fromStdString("\nThroughput (Bandweite): " + to_string(platformStatistic.getThroughput()) + " FPS"));
        QLabel *label_3 = new QLabel(this);
        label_3->setText(QString::fromStdString("\nLeistungsverbrauch: "+ to_string(platformStatistic.getEnergyConsum())));
        QLabel *label_4 = new QLabel(this);
        label_4->setText(QString::fromStdString("\nGesamte Laufzeit: " + to_string(platformStatistic.getTotalInferenceTime())));
        QLabel *label_5 = new QLabel(this);
        label_5->setText(QString::fromStdString("\nDurchschnittliche Laufzeit einer Iteration: " + to_string(platformStatistic.getAvgIterationTime()) + " ms"));
        labels->addWidget(name);
        labels->addWidget(label);
        labels->addWidget(label_2);
        labels->addWidget(label_3);
        labels->addWidget(label_4);
        labels->addWidget(label_5);
        vertikalGroupBoxLabels->setLayout(labels);

        labelsAndGraphs->addWidget(vertikalGroupBoxLabels);

        horizontalGroupBoxPlatform->setLayout(labelsAndGraphs);

        main_panel->addWidget(horizontalGroupBoxPlatform);
    }

    /*QGroupBox *horizontalGroupBoxGraph = new QGroupBox(this);
    QHBoxLayout *graph = new QHBoxLayout();
    QLabel *label_6 = new QLabel(this);
    label_6->setText("graph:");
    graph->addWidget(label_6);
    horizontalGroupBoxGraph->setLayout(graph);

    main_panel->addWidget(horizontalGroupBoxGraph);*/

    this->setLayout(main_panel);
}