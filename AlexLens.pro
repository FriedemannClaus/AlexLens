#-------------------------------------------------
#
# Project created by QtCreator 2019-06-22T17:37:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlexLens
TEMPLATE = app
INCLUDEPATH += includes/GUIModule

#fix commit
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    src/GUIModule/helpform.cpp \
    src/GUIModule/InputPanel.cpp \
    src/GUIModule/helppanel.cpp \
    src/GUIModule/mainwindow.cpp \
    src/GUIModule/outputclassifypanel.cpp \
    src/GUIModule/parameterpanel.cpp \
    src/ManagerModule/Manager.cpp \
    src/PlatformModule/ModeUtil.cpp \
    src/ManagerModule/main.cpp


HEADERS += \
    includes/GUIModule/helpform.h \
    includes/GUIModule/inputpanel.h \
    includes/GUIModule/helppanel.h \
    includes/GUIModule/mainwindow.h \
    includes/GUIModule/outputclassifypanel.h \
    includes/GUIModule/parameterpanel.h \
    includes/GUIModule/ui_mainwindow.h \
    includes/GUIModule/ui_helpform.h \
    src/ManagerModule/Manager.h \
    src/PlatformModule/ModeUtil.h \
    src/PlatformModule/Mode.h

FORMS += \
    helpform.ui \
    mainwindow.ui


Release:DESTDIR = qmake-build-release
Release:OBJECTS_DIR = qmake-build-release/.obj
Release:MOC_DIR = qmake-build-release/.moc
Release:RCC_DIR = qmake-build-release/.rcc
Release:UI_DIR = qmake-build-release/.ui

Debug:DESTDIR = qmake-build-debug
Debug:OBJECTS_DIR = qmake-build-debug/.obj
Debug:MOC_DIR = qmake-build-debug/.moc
Debug:RCC_DIR = qmake-build-debug/.rcc
Debug:UI_DIR = qmake-build-debug/.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icon/icon.qrc
