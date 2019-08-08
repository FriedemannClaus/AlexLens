#include "../../includes/GUIModule/inputpanel.h"

#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QScrollBar>
#include <QDragEnterEvent>

#include <QDebug>
#include <iostream>


InputPanel::InputPanel(QWidget *parent)
        : QWidget(parent)
{
    resize(640, 480);

    setAcceptDrops(true);

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

    if (fileNameList.size() == 0) this->imageWasAdded = false;

    int imageWidth = m_scrollArea->width() - 30;

    for (QString fileName : fileNameList)
    {
        QLabel* imageLabel = new QLabel(this);
        QPixmap pix(fileName);
        previewImages.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);

        this->manager->addImage(fileName.toStdString()); // adding fileName to manager

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

void InputPanel::dragEnterEvent(QDragEnterEvent *e)
{
    bool flag = true;
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QFileInfo fileInfo(url.toLocalFile());
        QString fileExtension = fileInfo.suffix().toLower();
        if (!(fileExtension.contains("jpg") || fileExtension.contains("png"))) {
            flag = false;
        }
    }
    if (flag) {
        e->acceptProposedAction();
    }
}

void InputPanel::dropEvent(QDropEvent *e)
{
    this->imageWasAdded = true;
    int imageWidth = m_scrollArea->width() - 30;

    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        QLabel* imageLabel = new QLabel(this);
        QPixmap pix(fileName);
        previewImages.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);

        this->manager->addImage(fileName.toStdString()); // adding fileName to manager
    }
}

void InputPanel::clearPanel()
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
