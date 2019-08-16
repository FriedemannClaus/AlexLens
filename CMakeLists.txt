cmake_minimum_required(VERSION 3.14)
project(AlexLens)

set(CMAKE_INCLUDE_CURRENT_DIR )
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
#find_package(OpenCV 4.1.1 EXACT REQUIRED PATHS /opt/intel/openvino)

list(APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core)

# OpenCV
#set(OpenCV_DIR /opt/intel/openvino/opencv/cmake)
set(OpenCV_DIR /home/viet/installation/OpenCV-3.4.7/share/OpenCV)
find_package(OpenCV)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# OpenVino
set(InferenceEngine_DIR /opt/intel/openvino/inference_engine/share)
find_package(InferenceEngine QUIET)
include_directories(/opt/intel/openvino/deployment_tools/inference_engine/samples/common/format_reader)
message(STATUS "InferenceEngine library status:")
message(STATUS "    version: ${InferenceEngine_VERSION}")
message(STATUS "    libraries: ${InferenceEngine_LIBRARIES}")
message(STATUS "    include path: ${InferenceEngine_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(AlexLens
        src/ManagerModule/main.cpp
        src/GUIModule/InputPanel.cpp includes/GUIModule/inputpanel.h
        src/GUIModule/mainwindow.cpp includes/GUIModule/mainwindow.h
        src/GUIModule/parameterpanel.cpp includes/GUIModule/parameterpanel.h
        src/GUIModule/outputclassifypanel.cpp includes/GUIModule/outputclassifypanel.h
        includes/GUIModule/ui_mainwindow.h
        src/ManagerModule/Manager.cpp src/ManagerModule/Manager.h
        src/PlatformModule/Mode.h src/PlatformModule/Mode.h
        includes/TrainingModule/ITraining.h
        src/GUIModule/Subject.h
        #src/MathModule/Matrix.cpp src/MathModule/Matrix.h
        #src/MathModule/Skalar.cpp src/MathModule/Skalar.h src/MathModule/MathException.h
        src/NeuralNetModule/Layer.h
        src/NeuralNetModule/TrainableLayer.h
        src/NeuralNetModule/FCLayer.cpp src/NeuralNetModule/FCLayer.h
        src/NeuralNetModule/Conv2DLayer.cpp src/NeuralNetModule/Conv2DLayer.h
        src/NeuralNetModule/NeuralNet.cpp src/NeuralNetModule/NeuralNet.h
        src/NeuralNetModule/NeuralNetException.h)

include_directories(includes)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Eigen3::Eigen
        ${OpenCV_LIBS}
        )