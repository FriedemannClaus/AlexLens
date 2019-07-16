#include "../../includes/GUIModule/outputclassifypanel.h"

#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QScrollBar>

#include <QDebug>
#include <iostream>


OutputClassifyPanel::OutputClassifyPanel(QWidget *parent)
        : QWidget(parent)
{
    resize(640, 480);

    m_gridLayout = new QGridLayout(this);
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_scrollAreaWidgetContents = new QWidget();
    m_gridLayout_2 = new QGridLayout(m_scrollAreaWidgetContents);
    m_verticalLayout = new QVBoxLayout();
    m_gridLayout_2->addLayout(m_verticalLayout, 0, 0, 1, 1);
    m_scrollArea->setWidget(m_scrollAreaWidgetContents);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gridLayout->addWidget(m_scrollArea, 0, 0, 1, 1);
}

OutputClassifyPanel::~OutputClassifyPanel()
{

}

void OutputClassifyPanel::addPreviewImages(QVector<QPair<QLabel *, QPixmap> > previewImages)
{

    int imageWidth = m_scrollArea->width() - 30;

    this->classifyResults.clear();
    this->previewImages.clear();
    this->previewImages = previewImages;

    for (auto pairLabelMap : this->previewImages)
    {

        QLabel* imageLabel = pairLabelMap.first;
        QPixmap pix(pairLabelMap.second);
        previewImages.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);
        QLabel* resultLabel = new QLabel(this);
        resultLabel->setText("hier erscheint das Ergebnis \n");
        classifyResults.push_front(resultLabel);
        m_verticalLayout->addWidget(resultLabel);
    }
}

void OutputClassifyPanel::clearPanel()
{
    QLayoutItem *child;
    while ((child = this->m_verticalLayout->takeAt(0)) != nullptr)
        {
            if (child->widget()) {
                delete child->widget();
            }
            if (child->layout()) {
                delete child->layout();
            }
            delete child;
        }
}

void OutputClassifyPanel::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    int imageWidth = m_scrollArea->width() - 30;

    for (QPair<QLabel*, QPixmap> pair : previewImages)
    {
        pair.first->setPixmap(pair.second.scaledToWidth(imageWidth));
    }
}
