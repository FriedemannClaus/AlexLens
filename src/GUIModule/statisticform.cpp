#include "../../includes/GUIModule/statisticform.h"
#include "../../includes/GUIModule/ui_statisticform.h"

#include <QScrollBar>
#include <QHBoxLayout>
#include <QGroupBox>

#include <QString>
#include <string>
using namespace std;

StatisticForm::StatisticForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticForm)
{
    ui->setupUi(this);

    main_panel = new QGridLayout();
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollAreaWidgetContents = new QWidget();
    m_gridLayout_2 = new QGridLayout(m_scrollAreaWidgetContents);
    m_scrollArea->setWidget(m_scrollAreaWidgetContents);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    main_panel->addWidget(m_scrollArea, 0, 0, 1, 1);

}

StatisticForm::~StatisticForm()
{
    delete ui;
}

void StatisticForm::printStatistic() {

    list<Platform *> listPlatforms = platformManager->getAvailablePlatforms();

    QFont font;
    font.setBold(true);
    font.setPointSize(14);

    for (auto platform:listPlatforms)
    {
        QGroupBox *vertikalGroupBoxLabels = new QGroupBox(this);
        QVBoxLayout *labels = new QVBoxLayout(this);
        QLabel *name = new QLabel(this);
        name->setText(QString::fromStdString(toString(platform->getType()) + ' ' + platform->getId()));
        name->setAlignment(Qt::AlignCenter);
        name->setFont(font);
        PlatformStatistic platformStatistic = platform->getStatistic();
        QLabel *label = new QLabel(this);
        label->setText(QString::fromStdString("GFLOPS: " + to_string(platformStatistic.getFLOPS())));
        QLabel *label_2 = new QLabel(this);
        label_2->setText(QString::fromStdString("\nBandweite (Throughput): " + to_string(platformStatistic.getThroughput()) + " FPS"));
        QLabel *label_3 = new QLabel(this);
        label_3->setText(QString::fromStdString("\nLeistungsverbrauch: "+ to_string(platformStatistic.getEnergyConsum())+ " W"));
        QLabel *label_4 = new QLabel(this);
        label_4->setText(QString::fromStdString("\nGesamte Laufzeit: " + to_string(platformStatistic.getTotalInferenceTime())+ " ms"));
        QLabel *label_5 = new QLabel(this);
        label_5->setText(QString::fromStdString("\nDurchschnittliche Laufzeit einer Iteration: " + to_string(platformStatistic.getAvgIterationTime()) + " ms"));
        labels->addWidget(name);
        labels->addWidget(label);
        labels->addWidget(label_2);
        labels->addWidget(label_3);
        labels->addWidget(label_4);
        labels->addWidget(label_5);
        vertikalGroupBoxLabels->setLayout(labels);
        m_gridLayout_2->addWidget(vertikalGroupBoxLabels);
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