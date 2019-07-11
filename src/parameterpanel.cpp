#include "parameterpanel.h"
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

ParameterPanel::ParameterPanel(QWidget *parent)
        : QWidget(parent)
{
    //resize(640, 480);

    m_gridLayout = new QGridLayout(this);


    QGroupBox *vertikalGroupBox = new QGroupBox(this);
    QVBoxLayout *parameterList = new QVBoxLayout;

    QListWidget *modList = new QListWidget;
    modList->addItem("Optimal");
    modList->addItem("Hohe Perfomance");
    modList->addItem("Geringer Leistungsverbrauch");
    modList->addItem("Hohe Energieeffizienz");

    QListWidget *nnList = new QListWidget(this);
    nnList->addItem("AlexNet");

    parameterList->addWidget(modList);
    parameterList->addWidget(nnList);

    vertikalGroupBox->setLayout(parameterList);

    m_gridLayout->addWidget(vertikalGroupBox);

    m_pushButton = new QPushButton("run", this);
    m_pushButton2 = new QPushButton("Beenden", this);

    connect(m_pushButton, &QPushButton::clicked, this, &ParameterPanel::run);
    connect(m_pushButton2, &QPushButton::clicked, this, &ParameterPanel::beenden);

    QGroupBox *horizonatlGroupBox = new QGroupBox(this);
    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(m_pushButton2);
    buttons->addWidget(m_pushButton);
    horizonatlGroupBox->setLayout(buttons);
    m_gridLayout->addWidget(horizonatlGroupBox);
    //m_gridLayout->addWidget(m_pushButton, 2, 0);
    //m_gridLayout->addWidget(m_pushButton2, 1, 0);
}

ParameterPanel::~ParameterPanel()
{

}

void ParameterPanel::run()
{
    QMessageBox::warning(this, "RUN", "RUN" );

}

void ParameterPanel::beenden()
{
    QMessageBox::warning(this, "BEENDEN", "BEENDEN" );
}


