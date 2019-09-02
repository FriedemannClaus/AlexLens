#include "inputpanel.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QScrollBar>
#include <QDragEnterEvent>
#include <QMessageBox>


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
        if(previewImages.size() >= 1) {
            QMessageBox::warning(this, "Datensatz einfügen", "Nur ein Datensatz kann eingefügt werden!" );
            return;
        }
        QString dir = "";
        dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        QStandardPaths::displayName(QStandardPaths::HomeLocation)
                                                        );
        if (dir == "") return;
        string dir_path = dir.toStdString();
        if (!checkDataset(dir_path)) {
            QMessageBox::warning(this, "Datensatz einfügen", "Die Struktur des Datensatzes ist inkorrekt." );
            return;
        }

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
        path = path.substr(path.rfind('/')+1, path.length()-path.rfind('/')+1);
        dirLabel->setText(QString::fromStdString(path));
        dirLabel->setAlignment(Qt::AlignCenter);
        //dirLabel->setPixmap(d.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(dirLabel);

        this->manager->setDatasetPath(dir.toStdString()); // adding directory to manager

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
        if (flag) {
            e->acceptProposedAction();
        } else {
            QMessageBox::warning(this, "Bild einfügen", "Das Bildformat ist inkorrekt." );
        }
    } else {
        flag = true;
        int i = 0;
        foreach (const QUrl &url, e->mimeData()->urls()) {
            QFileInfo fileInfo(url.toLocalFile());
            string path = url.toString().toLocal8Bit().constData();
            if ((path[path.length()-1] != '/') && (!(fileInfo.isDir()))) {
                flag = false;
            } else {
                i++;
            }
        }
        if (i != 1) {
            flag = false;
        }
        if (flag) {
            e->acceptProposedAction();
        } else if (i > 1) {
            QMessageBox::warning(this, "Datensatz einfügen", "Nur ein Datensatz kann eingefügt werden!" );
        } else {
            QMessageBox::warning(this, "Datensatz einfügen", "Die Struktur des Datensatzes ist inkorrekt." );
        }
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
        if(previewImages.size() >= 1) {
            QMessageBox::warning(this, "Datensatz einfügen", "Nur ein Datensatz kann eingefügt werden!" );
            return;
        }

        foreach (const QUrl &url, e->mimeData()->urls()) {
            QLabel* dirLabel = new QLabel(this);
            QString q_path = url.toString();
            if (q_path == "") return;
            string path = url.toString().toStdString();

            //QString subPath = q_path.mid(7,path.length()-8); //macOs
            //path = path.substr(0, path.length()-1);

            QString subPath = q_path.mid(7,path.length()-6);
            path = path.substr(0, path.length());
            path = path.substr(path.rfind('/')+1, path.length()-path.rfind('/')+1);
            string pathStr = subPath.toStdString();
            if (!checkDataset(pathStr)) {
                QMessageBox::warning(this, "Datensatz einfügen", "Die Struktur des Datensatzes ist inkorrekt." );
                return;
            }

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

            dirLabel->setText(QString::fromStdString(path));
            dirLabel->setAlignment(Qt::AlignCenter);
            m_verticalLayout->addWidget(dirLabel);
            this->manager->setDatasetPath(subPath.toStdString());
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

bool InputPanel::checkDataset(string &path) {
    std::string path_valid = path+"/valid/";
    std::string path_train = path+"/train/";
    std::string path_test = path+"/test/";
    list<string> files_valid = getAllFilesInDir(path_valid);
    list<string> files_train = getAllFilesInDir(path_train);
    list<string> files_test = getAllFilesInDir(path_test);

    if ((files_test.size() != 0) && (files_test == files_train) && (files_test == files_valid))
        return true;
    return false;
}

list<string> InputPanel::getAllFilesInDir(string &path) {
    list<string> files_valid;
    char * dir_path = new char [path.length()+1];
    strcpy (dir_path, path.c_str());
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dir_path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            files_valid.push_back(ent->d_name);
        }
        closedir(dir);
    }
    return files_valid;
}


