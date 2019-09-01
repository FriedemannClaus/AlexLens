#include "outputclassifypanel.h"

#include <vector>
#include <QApplication>
#include <unistd.h>


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

void OutputClassifyPanel::addPreviewImages(QVector<QPair<QLabel *, QPixmap> > previewImages) {
    int imageWidth = m_scrollArea->width() - 30;
    this->classifyResults.clear();
    this->previewImages.clear();
    this->previewImages = previewImages;

    for (auto pairLabelMap : this->previewImages)
    {
        QLabel* imageLabel = pairLabelMap.first;
        QPixmap pix = pairLabelMap.second;
        previewImages.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);
        QLabel* resultLabel = new QLabel(this);
        resultLabel->setText("Das Ergebnis wird gerade berechnet \n");
        classifyResults.push_front(resultLabel);
        m_verticalLayout->addWidget(resultLabel);
    }
}

void OutputClassifyPanel::clearPanel() {
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

void OutputClassifyPanel::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event)
    int imageWidth = m_scrollArea->width() - 30;

    for (QPair<QLabel*, QPixmap> pair : previewImages)
    {
        pair.first->setPixmap(pair.second.scaledToWidth(imageWidth));
    }
}

void OutputClassifyPanel::invokeUpdate() {
    if (classifyTab) {
        int i = 0;
        for (string result:this->manager->getResults()) {
            classifyResults.at(i)->setText(QString::fromStdString(result));
            i++;
        }
    } else {
        this->clearPanel();
        this->addTrainingLog();
        this->addTrainingAccuracyCurve();
        this->addTrainingLossCurve();
    }
}

void OutputClassifyPanel::setResults(vector<string>& results) {
        //vector<string> reults = ;
        this->results.reserve(10);
        for (auto a :results) this->results.push_back(a);
        //this->results = results;

}

void OutputClassifyPanel::addTrainingLog() {
    string line;
    ifstream file_log;
    string file_log_name = "";
    file_log_name += this->manager->getProjectDir() + "resources/";
    file_log_name += this->manager->getNeuralNet();
    file_log_name+= "/";
    file_log_name += this->manager->getNeuralNet();
    file_log_name+= "_log.txt";
    file_log.open(file_log_name);
    if (file_log.fail()) {
        cerr << "Error opening a file" << endl;
        file_log.close();
        exit(1);
    }
    while ( getline (file_log,line) )
    {
        this->addLine(line);
    }
    file_log.close();
}

void OutputClassifyPanel::addLine(string line) {
    QFont font;
    font.setPointSize(12);
    QLabel *label = new QLabel(this);
    label->setText(QString::fromStdString(line));
    label->setFont(font);
    m_verticalLayout->addWidget(label);
    qApp->processEvents();
    usleep(rand()%300000);
}
void OutputClassifyPanel::addLoadingIcon(){
    QMovie *movie = new QMovie(QString::fromStdString(this->manager->getProjectDir() + "Icon/iconLoading.gif"));
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
    processLabel->setAlignment(Qt::AlignCenter);
    m_verticalLayout->addWidget(processLabel);;
}
void OutputClassifyPanel::addTrainingAccuracyCurve() {
    string fileNameListPath = this->manager->getProjectDir() + "resources/" + this->manager->getNeuralNet() + "/" + this->manager->getNeuralNet()+ "_accuracy_curve.png";
    QString QfileNameListPath = QString::fromStdString(fileNameListPath);
    QStringList fileNameList = {QfileNameListPath};

    int imageWidth = m_scrollArea->width() - 30;

    for (QString fileName : fileNameList) {
        QLabel* imageLabel = new QLabel(this);
        QPixmap pix(fileName);
        previewImages.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);
        QFont font;
        font.setPointSize(12);
        QLabel *label = new QLabel(this);
        label->setText(QString::fromStdString("Accuracy curve"));
        label->setFont(font);
        m_verticalLayout->addWidget(label);
    }
}

void OutputClassifyPanel::addTrainingLossCurve() {
    string fileNameListPath = this->manager->getProjectDir() + "resources/" + this->manager->getNeuralNet() + "/" + this->manager->getNeuralNet()+ "_loss_curve.png";
    QString QfileNameListPath = QString::fromStdString(fileNameListPath);
    QStringList fileNameList = {QfileNameListPath};

    int imageWidth = m_scrollArea->width() - 30;

    for (QString fileName : fileNameList) {
        QLabel* imageLabel = new QLabel(this);
        QPixmap pix(fileName);
        previewImages.append(qMakePair(imageLabel, pix));
        imageLabel->setPixmap(pix.scaledToWidth(imageWidth));
        m_verticalLayout->addWidget(imageLabel);
        QFont font;
        font.setPointSize(12);
        QLabel *label = new QLabel(this);
        label->setText(QString::fromStdString("Loss curve"));
        label->setFont(font);
        m_verticalLayout->addWidget(label);
    }
}