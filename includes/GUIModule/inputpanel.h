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
#include <QMimeData>
#include "../../src/ManagerModule/Manager.h"

class InputPanel : public QWidget
{
    Q_OBJECT

public:
    InputPanel(QWidget *parent = nullptr);
    ~InputPanel();

    inline void setManager(Manager* manager) {this->manager = manager;}
    inline void setImageWasAdded(bool imageWasAdded) {this->imageWasAdded = imageWasAdded;}
    inline void setClassifyTab(bool classifyTab) {this->classifyTab = classifyTab;}
    inline bool isImageAdded() {return imageWasAdded;}
    inline bool isClassifyTab() {return classifyTab;}
    inline QVector<QPair<QLabel*, QPixmap> > getPreviewImages() {return this->previewImages;}
    inline void clearPreviewImages() {this->previewImages.clear(); this->imageWasAdded = false;}
    void clearPanel();

private slots:
            void addImage();
            void dragEnterEvent(QDragEnterEvent *e) override;
            void dropEvent(QDropEvent *e) override;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QGridLayout* m_gridLayout;
    QLabel *label;
    QGridLayout* m_gridLayout_2;
    QScrollArea* m_scrollArea;
    QPushButton* m_pushButton;
    QVBoxLayout* m_verticalLayout;
    QWidget*     m_scrollAreaWidgetContents;
    QVector<QPair<QLabel*, QPixmap> > previewImages;
    Manager* manager;
    bool imageWasAdded = false;
    bool classifyTab = true;
};

#endif // WIDGET_H
