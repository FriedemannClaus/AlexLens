cmake_minimum_required(VERSION 3.14)
project(AlexLens)

set(CMAKE_INCLUDE_CURRENT_DIR )
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

list(APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core)

#fix line
add_executable(AlexLens src/main.cpp src/GUIModule/InputPanel.cpp includes/GUIModule/inputpanel.h src/GUIModule/mainwindow.cpp includes/GUIModule/mainwindow.h src/GUIModule/parameterpanel.cpp includes/GUIModule/parameterpanel.h src/GUIModule/outputclassifypanel.cpp includes/GUIModule/outputclassifypanel.h includes/GUIModule/ui_mainwindow.h src/ManagerModule/Manager.cpp src/ManagerModule/Manager.h src/PlatformModule/Mode.h src/PlatformModule/Mode.h src/PlatformModule/Mode.cpp)

include_directories(includes)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        )