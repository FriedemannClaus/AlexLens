#include "../../includes/GUIModule/statisticform.h"
#include "../../includes/GUIModule/ui_statisticform.h"

StatisticForm::StatisticForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticForm)
{
    ui->setupUi(this);

    setWindowFlags( Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

StatisticForm::~StatisticForm()
{
    delete ui;
}
