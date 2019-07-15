#include "../../includes/GUIModule/helpform.h"
#include "../../includes/GUIModule/ui_helpform.h"

HelpForm::HelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpForm)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    //setWindowFlags( Qt::Window | Qt::MSWindowsFixedSizeDialogHint| Qt::WindowTitleHint | Qt::CustomizeWindowHint );
}

HelpForm::~HelpForm()
{
    delete ui;
}

