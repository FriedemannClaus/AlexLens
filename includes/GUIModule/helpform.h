#ifndef HELPFORM_H
#define HELPFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class HelpForm;
}

class HelpForm : public QWidget
{
    Q_OBJECT

public:
    explicit HelpForm(QWidget *parent = nullptr);
    ~HelpForm();

private:
    Ui::HelpForm *ui;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QFont font_2;
    QFont font_4;
    QGridLayout* h_panel;
};

#endif // HELPFORM_H
