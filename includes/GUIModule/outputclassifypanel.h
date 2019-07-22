#ifndef OUTPUTCLASSIFYPANEL_H
#define OUTPUTCLASSIFYPANEL_H

#include <QWidget>

#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include "../GUIModule/IObserver.h"
#include "../../src/ManagerModule/Manager.h"
#include "Subject.h"

using namespace std;

class OutputClassifyPanel : public QWidget, public IObserver
{
    Q_OBJECT

public:
    OutputClassifyPanel(QWidget *parent = nullptr);
    ~OutputClassifyPanel();

    void addPreviewImages(QVector<QPair<QLabel*, QPixmap> > previewImages);
    void clearPanel();

    inline void setManager(Manager* manager) {this->manager = manager;}

    //inline void setSubject(Subject* subject) {this->subject = subject;subject->attachObserver(this);}
    void setResults(vector<string>& results);
    void invokeUpdate() override;
    void hello() {std::cout << "hello!" << std::endl;}


protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    vector<string> results;
    QGridLayout* m_gridLayout;
    QGridLayout* m_gridLayout_2;
    QScrollArea* m_scrollArea;
    QPushButton* m_pushButton;
    QVBoxLayout* m_verticalLayout;
    QWidget*     m_scrollAreaWidgetContents;
    QVector<QPair<QLabel*, QPixmap> > previewImages;
    QVector<QLabel*> classifyResults;
    //Subject* subject = new Subject();
    Manager* manager;

};

#endif // WIDGET_H
