#include "../../includes/GUIModule/inputpanel.h"

#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QScrollBar>

#include <QDebug>
#include <iostream>


InputPanel::InputPanel(QWidget *parent)
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

    m_pushButton = new QPushButton("Bild einfügen", this);
    connect(m_pushButton, &QPushButton::clicked, this, &InputPanel::addImage);
    m_gridLayout->addWidget(m_pushButton, 1, 0);
}

InputPanel::~InputPanel()
{

}

void InputPanel::addImage()
{
    this->imageWasAdded = true;
    QStringList fileNameList = QFileDialog::getOpenFileNames(this,
                                                             "Open Files",
                                                             QStandardPaths::displayName(QStandardPaths::HomeLocation),
                                                             tr("Images (*.png *.jpg)"));

    int imageWidth = m_scrollArea->width() - 30;

    for (QString fileName : fileNameList)
    {
        QLabel* imageLabel = new QLabel(this);
        QPixmap pix(fileName);
        previewImages.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);

        this->manager->addImage(fileName.toStdString()); // adding fileName to manager
        std::cout << fileName.toStdString() << endl;
    }
}

void InputPanel::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    int imageWidth = m_scrollArea->width() - 30;

    for (QPair<QLabel*, QPixmap> pair : previewImages)
    {
        pair.first->setPixmap(pair.second.scaledToWidth(imageWidth));
    }
}
