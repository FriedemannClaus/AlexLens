#ifndef HELPFORM_H
#define HELPFORM_H

#include <QVBoxLayout>
#include <QLabel>

namespace Ui {
class HelpForm;
}

/**
 * Class HelpFrom. All necessary information of software is printed.
 */
class HelpForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructor for class HelpForm.
     * @param parent
     */
    explicit HelpForm(QWidget *parent = nullptr);

    /**
     * Destructor for class HelpForm.
     */
    ~HelpForm();

private:
    Ui::HelpForm *ui; // Skeleton of Helpform
    QLabel *label; // Information of software
    QGridLayout* h_panel; // The main panel of Helpform
};

#endif // HELPFORM_H
