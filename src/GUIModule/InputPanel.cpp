#include "inputpanel.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QScrollBar>
#include <QDragEnterEvent>


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
    if(classifyTab) {

        QStringList fileNameList = QFileDialog::getOpenFileNames(this,
                                                                 "Open Files",
                                                                 QStandardPaths::displayName(QStandardPaths::HomeLocation),
                                                                 tr("Images (*.png *.PNG *.jpg *.JPG *.jpeg *.JPEG)"));
        int imageWidth = m_scrollArea->width() - 30;
        for (QString fileName : fileNameList) {
            QLabel* imageLabel = new QLabel(this);
            QPixmap pix(fileName);
            previewImages.append(qMakePair(imageLabel, pix));
            imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
            m_verticalLayout->addWidget(imageLabel);
            this->manager->addImage(fileName.toStdString()); // adding fileName to manager
        }
    } else {

        QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        QStandardPaths::displayName(QStandardPaths::HomeLocation)
                                                        );
        QStringList fileNameList = {QString::fromStdString(this->manager->getProjectDir() + "Icon/iconOrdner.png")};

        int imageWidth = m_scrollArea->width() - 30;

        for (QString fileName : fileNameList)
        {
            QLabel* imageLabel = new QLabel(this);
            QPixmap pix(fileName);
            previewImages.append(qMakePair(imageLabel, pix));
            imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
            m_verticalLayout->addWidget(imageLabel);
        }

        //int imageWidth = m_scrollArea->width() - 30;


        QLabel* dirLabel = new QLabel(this);
        string path = dir.toStdString();
        cout << "here" << endl;
        cout << path << endl;
        path = path.substr(path.rfind('/')+1, path.length()-path.rfind('/')+1);
        cout << path << endl;
        dirLabel->setText(QString::fromStdString(path));
        dirLabel->setAlignment(Qt::AlignCenter);
        //dirLabel->setPixmap(d.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(dirLabel);

        this->manager->addImage(dir.toStdString()); // adding directory to manager


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
    bool flag;
    if(classifyTab) {
        flag = true;
        foreach (const QUrl &url, e->mimeData()->urls()) {
            QFileInfo fileInfo(url.toLocalFile());
            QString fileExtension = fileInfo.suffix().toLower();
            if (!(fileExtension.contains("jpg") || fileExtension.contains("png") ||
            fileExtension.contains("jpeg"))) {
                flag = false;
            }
        }
    } else {
        flag = true;
        foreach (const QUrl &url, e->mimeData()->urls()) {
            QFileInfo fileInfo(url.toLocalFile());
            string path = url.toString().toLocal8Bit().constData();
            if ((path[path.length()-1] != '/') && (!(fileInfo.isDir()))) {
                flag = false;
            }
        }
    }
    if (flag) {
        e->acceptProposedAction();
    }
}

void InputPanel::dropEvent(QDropEvent *e)
{
    if(classifyTab) {

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
    } else {

        QStringList fileNameList = {QString::fromStdString(this->manager->getProjectDir() + "Icon/iconOrdner.png")};

        int imageWidth = m_scrollArea->width() - 30;

        for (QString fileName : fileNameList)
        {
            QLabel* imageLabel = new QLabel(this);
            QPixmap pix(fileName);
            previewImages.append(qMakePair(imageLabel, pix));
            imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
            m_verticalLayout->addWidget(imageLabel);
        }

        foreach (const QUrl &url, e->mimeData()->urls()) {
            QLabel* dirLabel = new QLabel(this);
            QString q_path = url.toString();
            string path = url.toString().toStdString();
            QString subPath = q_path.mid(7,path.length()-8);
            path = path.substr(0, path.length()-1);
            path = path.substr(path.rfind('/')+1, path.length()-path.rfind('/')+1);
            dirLabel->setText(QString::fromStdString(path));
            dirLabel->setAlignment(Qt::AlignCenter);
            m_verticalLayout->addWidget(dirLabel);
            this->manager->addImage(subPath.toStdString());
        }
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

