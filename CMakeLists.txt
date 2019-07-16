cmake_minimum_required(VERSION 3.14)
project(AlexLens)

set(CMAKE_INCLUDE_CURRENT_DIR )
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

list(APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core)

add_executable(AlexLens src/ManagerModule/main.cpp
        src/GUIModule/InputPanel.cpp includes/GUIModule/inputpanel.h
        src/GUIModule/helppanel.cpp includes/GUIModule/helppanel.h
        src/GUIModule/helpform.cpp includes/GUIModule/helpform.h
        src/GUIModule/statisticform.cpp includes/GUIModule/statisticform.h
        src/GUIModule/mainwindow.cpp includes/GUIModule/mainwindow.h
        src/GUIModule/parameterpanel.cpp includes/GUIModule/parameterpanel.h
        src/GUIModule/outputclassifypanel.cpp includes/GUIModule/outputclassifypanel.h
        src/ManagerModule/Manager.cpp src/ManagerModule/Manager.h
        src/PlatformModule/Mode.h
        src/TrainingModule/ITraining.h
        src/GUIModule/Subject.h
        Icon/icon.qrc
        src/PlatformModule/ModeUtil.cpp src/PlatformModule/ModeUtil.h)

include_directories(includes)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        )