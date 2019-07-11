#ifndef PARAMETERPANEL_H
#define PARAMETERPANEL_H

#include <QWidget>

#include <QGridLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QImage>
#include <QPixmap>

class ParameterPanel : public QWidget
{
    Q_OBJECT

public:
    ParameterPanel(QWidget *parent = 0);
    ~ParameterPanel();

private slots:
            void run();
    void beenden();

private:
    QGridLayout* m_gridLayout;
    QPushButton* m_pushButton;
    QPushButton* m_pushButton2;
};

#endif // WIDGET_H
