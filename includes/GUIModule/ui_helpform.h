/********************************************************************************
** Form generated from reading UI file 'helpform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPFORM_H
#define UI_HELPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "helppanel.h"

QT_BEGIN_NAMESPACE

class Ui_HelpForm
{
public:
    HelpPanel *widget;

    void setupUi(QWidget *HelpForm)
    {
        if (HelpForm->objectName().isEmpty())
            HelpForm->setObjectName(QString::fromUtf8("HelpForm"));
        HelpForm->resize(400, 300);
        widget = new HelpPanel(HelpForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(15, 0, 600, 500));

        retranslateUi(HelpForm);

        QMetaObject::connectSlotsByName(HelpForm);
    } // setupUi

    void retranslateUi(QWidget *HelpForm)
    {
        HelpForm->setWindowTitle(QCoreApplication::translate("HelpForm", "Hilfe", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpForm: public Ui_HelpForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPFORM_H
