#include "../../includes/GUIModule/inputpanel.h"

#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QScrollBar>

#include <QDebug>


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

    m_pushButton = new QPushButton("Add Image", this);
    connect(m_pushButton, &QPushButton::clicked, this, &InputPanel::addImage);
    m_gridLayout->addWidget(m_pushButton, 1, 0);
}

InputPanel::~InputPanel()
{

}

void InputPanel::addImage()
{
    QStringList fileNameList = QFileDialog::getOpenFileNames(this,
                                                             "Open Files",
                                                             QStandardPaths::displayName(QStandardPaths::HomeLocation),
                                                             tr("Images (*.png *.jpg)"));

    int imageWidth = m_scrollArea->width() - 30;

    for (QString fileName : fileNameList)
    {
        QLabel* imageLabel = new QLabel(this);
        QPixmap pix(fileName);
        m_imagesVector.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);
    }
}

void InputPanel::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    int imageWidth = m_scrollArea->width() - 30;

    for (QPair<QLabel*, QPixmap> pair : m_imagesVector)
    {
        pair.first->setPixmap(pair.second.scaledToWidth(imageWidth));
    }
}
