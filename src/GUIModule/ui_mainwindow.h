/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "inputpanel.h"
#include "outputclassifypanel.h"
#include "parameterpanel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStatistiken;
    QAction *actionHilfe;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *classifyTab;
    QHBoxLayout *horizontalLayout;
    InputPanel *inputClassifyPanel;
    ParameterPanel *parameterClassifyPanel;
    OutputClassifyPanel *outputClassifyPanel;
    QWidget *trainingTab;
    QHBoxLayout *horizontalLayout_2;
    InputPanel *inputTrainingPanel;
    ParameterPanel *parameterTrainingPanel;
    OutputClassifyPanel *outputTrainingPanel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(822, 481);
        actionStatistiken = new QAction(MainWindow);
        actionStatistiken->setObjectName(QString::fromUtf8("actionStatistiken"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/iconStat.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStatistiken->setIcon(icon);
        actionHilfe = new QAction(MainWindow);
        actionHilfe->setObjectName(QString::fromUtf8("actionHilfe"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/iconQuestion.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHilfe->setIcon(icon1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        classifyTab = new QWidget();
        classifyTab->setObjectName(QString::fromUtf8("classifyTab"));
        horizontalLayout = new QHBoxLayout(classifyTab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        inputClassifyPanel = new InputPanel(classifyTab);
        inputClassifyPanel->setObjectName(QString::fromUtf8("inputClassifyPanel"));

        horizontalLayout->addWidget(inputClassifyPanel);

        parameterClassifyPanel = new ParameterPanel(classifyTab);
        parameterClassifyPanel->setObjectName(QString::fromUtf8("parameterClassifyPanel"));

        horizontalLayout->addWidget(parameterClassifyPanel);

        outputClassifyPanel = new OutputClassifyPanel(classifyTab);
        outputClassifyPanel->setObjectName(QString::fromUtf8("outputClassifyPanel"));

        horizontalLayout->addWidget(outputClassifyPanel);

        tabWidget->addTab(classifyTab, QString());
        trainingTab = new QWidget();
        trainingTab->setObjectName(QString::fromUtf8("trainingTab"));
        horizontalLayout_2 = new QHBoxLayout(trainingTab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        inputTrainingPanel = new InputPanel(trainingTab);
        inputTrainingPanel->setObjectName(QString::fromUtf8("inputTrainingPanel"));

        horizontalLayout_2->addWidget(inputTrainingPanel);

        parameterTrainingPanel = new ParameterPanel(trainingTab);
        parameterTrainingPanel->setObjectName(QString::fromUtf8("parameterTrainingPanel"));

        horizontalLayout_2->addWidget(parameterTrainingPanel);

        outputTrainingPanel = new OutputClassifyPanel(trainingTab);
        outputTrainingPanel->setObjectName(QString::fromUtf8("outputTrainingPanel"));

        horizontalLayout_2->addWidget(outputTrainingPanel);

        tabWidget->addTab(trainingTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 822, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setLayoutDirection(Qt::RightToLeft);
        mainToolBar->setIconSize(QSize(20, 20));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionHilfe);
        mainToolBar->addAction(actionStatistiken);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AlexLens", nullptr));
        actionStatistiken->setText(QCoreApplication::translate("MainWindow", "Statistiken", nullptr));
#if QT_CONFIG(tooltip)
        actionStatistiken->setToolTip(QCoreApplication::translate("MainWindow", "Statistiken", nullptr));
#endif // QT_CONFIG(tooltip)
        actionHilfe->setText(QCoreApplication::translate("MainWindow", "Hilfe", nullptr));
#if QT_CONFIG(tooltip)
        actionHilfe->setToolTip(QCoreApplication::translate("MainWindow", "Hilfe", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget->setTabText(tabWidget->indexOf(classifyTab), QCoreApplication::translate("MainWindow", "Klassifizierung", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(trainingTab), QCoreApplication::translate("MainWindow", "Transfer Learning", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
