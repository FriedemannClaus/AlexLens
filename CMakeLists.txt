cmake_minimum_required(VERSION 3.14)
project(AlexLens)

set(CMAKE_INCLUDE_CURRENT_DIR )
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

list(APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core)

add_executable(AlexLens src/main.cpp src/InputPanel.cpp includes/inputpanel.h src/mainwindow.cpp includes/mainwindow.h src/parameterpanel.cpp includes/parameterpanel.h src/outputclassifypanel.cpp includes/outputclassifypanel.h includes/ui_mainwindow.h src/Manager.cpp src/Manager.h)

include_directories(includes)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        )