/********************************************************************************
** Form generated from reading UI file 'statisticform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTICFORM_H
#define UI_STATISTICFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticForm
{
public:

    void setupUi(QWidget *StatisticForm)
    {
        if (StatisticForm->objectName().isEmpty())
            StatisticForm->setObjectName(QString::fromUtf8("StatisticForm"));
        StatisticForm->resize(400, 306);

        retranslateUi(StatisticForm);

        QMetaObject::connectSlotsByName(StatisticForm);
    } // setupUi

    void retranslateUi(QWidget *StatisticForm)
    {
        StatisticForm->setWindowTitle(QCoreApplication::translate("StatisticForm", "Statistiken", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatisticForm: public Ui_StatisticForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTICFORM_H
