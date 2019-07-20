#ifndef INPUTPANEL_H
#define INPUTPANEL_H

#include <QWidget>

#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include "../../src/ManagerModule/Manager.h"

class InputPanel : public QWidget
{
    Q_OBJECT

public:
    InputPanel(QWidget *parent = nullptr);
    ~InputPanel();

    inline void setManager(Manager* manager) {this->manager = manager;}
    inline bool isImageAdded() {return imageWasAdded;}
    inline QVector<QPair<QLabel*, QPixmap> > getPreviewImages() {return this->previewImages;}
    inline void clearPreviewImages() {this->previewImages.clear(); this->imageWasAdded = false;}

private slots:
            void addImage();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout* m_gridLayout;
    QGridLayout* m_gridLayout_2;
    QScrollArea* m_scrollArea;
    QPushButton* m_pushButton;
    QVBoxLayout* m_verticalLayout;
    QWidget*     m_scrollAreaWidgetContents;
    QVector<QPair<QLabel*, QPixmap> > previewImages;
    Manager* manager;
    bool imageWasAdded = false;
};

#endif // WIDGET_H
