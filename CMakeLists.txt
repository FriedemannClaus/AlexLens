cmake_minimum_required(VERSION 3.14)
project(AlexLens)

set(CMAKE_INCLUDE_CURRENT_DIR )
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTORCC ON)
SET(CMAKE_CXX_FLAGS -pthread)
find_package(Threads)

include_directories(includes)
include_directories(src)

# Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
list(APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core)

# Torch
find_package(Torch REQUIRED)
include_directories( ${Torch_INCLUDE_DIRS} )

# OpenCV
set(OpenCV_DIR /opt/intel/openvino/opencv/cmake)
find_package(OpenCV)

# OpenVino
set(InferenceEngine_DIR /opt/intel/openvino/inference_engine/share)
find_package(InferenceEngine)
include_directories(/opt/intel/openvino/deployment_tools/inference_engine/samples/common/format_reader)

add_executable(AlexLens src/ManagerModule/main.cpp
        src/ManagerModule/Manager.cpp src/ManagerModule/Manager.h
        src/GUIModule/InputPanel.cpp includes/GUIModule/inputpanel.h
        src/GUIModule/helpform.cpp includes/GUIModule/helpform.h
        src/GUIModule/statisticform.cpp includes/GUIModule/statisticform.h
        src/GUIModule/mainwindow.cpp includes/GUIModule/mainwindow.h
        src/GUIModule/parameterpanel.cpp includes/GUIModule/parameterpanel.h
        src/GUIModule/outputclassifypanel.cpp includes/GUIModule/outputclassifypanel.h
        src/PlatformModule/Mode.h
        Icon/icon.qrc
        src/PlatformModule/ModeUtil.cpp src/PlatformModule/ModeUtil.h
        src/NeuralNetModule/NeuralNet.cpp src/NeuralNetModule/NeuralNet.h
        src/NeuralNetModule/INeuralNet.h
        src/PlatformModule/ModeUtil.cpp src/PlatformModule/ModeUtil.h
        src/ManagerModule/Manager.cpp src/ManagerModule/Manager.h
        src/ManagerModule/Executor.cpp src/ManagerModule/Executor.h
        src/PlatformModule/Platform.cpp src/PlatformModule/Platform.h
        src/PlatformModule/ASICPlatform.cpp src/PlatformModule/ASICPlatform.h
        includes/GUIModule/IObserver.h
        includes/GUIModule/Subject.h
        src/PlatformModule/PlatformManager.cpp src/PlatformModule/PlatformManager.h
        src/PlatformModule/CPUPlatform.cpp src/PlatformModule/CPUPlatform.h
        src/PlatformModule/PlatformType.h
        src/PlatformModule/PlatformStatistic.cpp src/PlatformModule/PlatformStatistic.h
        )



target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        ${InferenceEngine_LIBRARIES}
        /home/viet/inference_engine_samples_build/intel64/Release/lib/libformat_reader.so
        ${TORCH_LIBRARIES}
        ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        )
