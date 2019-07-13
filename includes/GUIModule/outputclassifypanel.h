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

class OutputClassifyPanel : public QWidget
{
    Q_OBJECT

public:
    OutputClassifyPanel(QWidget *parent = 0);
    ~OutputClassifyPanel();

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
    QVector<QPair<QLabel*, QPixmap> > m_imagesVector;
};

#endif // WIDGET_H