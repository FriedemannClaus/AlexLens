#ifndef STATISTICFORM_H
#define STATISTICFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <iostream>
#include <memory>
#include <iomanip>
#include <c++/v1/sstream>
#include "PlatformModule/PlatformManager.h"

namespace Ui {
class StatisticForm;
}

/**
 * Class StatisticFrom. All information of platforms is available.
 */
class StatisticForm : public QWidget
{
    Q_OBJECT

public:
    /**
     * Constructor for class StatisticForm.
     * @param parent
     */
    explicit StatisticForm(QWidget *parent = nullptr);

    /**
     * Destructor for class StatisticForm.
     */
    ~StatisticForm();

    /**
     * @param platformManager platformManager to set
     */
    inline void setPlatformManager(PlatformManager* platformManager) {this->platformManager = platformManager;}

    /**
     * All statistics of platforms after classify are printed.
     */
    void printStatistic();

    /**
     * Convert PlatformType object to string.
     * @param type PlatformType object
     * @return string representation of object
     */
    inline string toString(const PlatformType &type)
    {
        switch (type)
        {
            case PlatformType::CPU:
                return "CPU";
            case PlatformType::ASIC:
                return "ASIC";
            case PlatformType ::CPU_TORCH:
                return "CPU_TORCH";
        }
    }
    /**
     * Convert double object to string.
     * @param n double object
     * @return string representation of object in form *.??
     */
    inline string convertDoubleToStr(double n) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << n;
        return stream.str();
    }

private:
    Ui::StatisticForm *ui; /// Skeleton of Statisticform
    QGridLayout* main_panel; /// The main panel of Statisticform
    PlatformManager* platformManager; /// Manager of platforms

    QGridLayout* m_gridLayout_2; /// The panel with all statistics
    QScrollArea* m_scrollArea; /// Scroll area
    QWidget*     m_scrollAreaWidgetContents; /// Scroll widget
};

#endif // STATISTICFORM_H
