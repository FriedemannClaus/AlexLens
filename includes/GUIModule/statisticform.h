#ifndef STATISTICFORM_H
#define STATISTICFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "../../src/PlatformModule/PlatformManager.h"

namespace Ui {
class StatisticForm;
}

class StatisticForm : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticForm(QWidget *parent = nullptr);
    ~StatisticForm();
    inline void setPlatformManager(PlatformManager* platformManager) {this->platformManager = platformManager;}
    void printStatistic();
    inline string toString(const PlatformType &type)
    {
        switch (type)
        {
            case PlatformType::CPU:
                return "CPU";
            case PlatformType::ASIC:
                return "ASIC";
        }
    }

private:
    Ui::StatisticForm *ui;
    QGridLayout* main_panel;
    PlatformManager* platformManager;
};

#endif // STATISTICFORM_H
