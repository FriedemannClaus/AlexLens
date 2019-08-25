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

# HDF5
find_package(HDF5 REQUIRED COMPONENTS CXX)
message(STATUS "HDF5 library status:")
message(STATUS "    version: ${HDF5_VERSION}")
message(STATUS "    libraries: ${HDF5_LIBRARIES}")
message(STATUS "    include path: ${HDF5_INCLUDE_DIRS}")
include_directories(${HDF5_INCLUDE_DIRS})

# Eigen3
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
message(STATUS "Eigen3 library status:")
message(STATUS "    version: ${Eigen3_VERSION}")

# Python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
list(APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core)

# Torch
include_directories(/home/viet/pytorch/build/lib.linux-x86_64-3.7/torch/include)
include_directories(/home/viet/pytorch/build/lib.linux-x86_64-3.7/torch/include/torch/csrc/api/include)

# OpenCV
set(OpenCV_DIR /opt/intel/openvino/opencv/cmake)
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

#[[
add_library(AlexLens_static_lib STATIC
        src/ManagerModule/main.cpp
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
        src/PlatformModule/CPUPlatformTorch.cpp src/PlatformModule/CPUPlatformTorch.h
        src/PlatformModule/PlatformType.h
        src/PlatformModule/PlatformStatistic.cpp src/PlatformModule/PlatformStatistic.h
        )

target_include_directories(AlexLens_static_lib
        PUBLIC
        ${PROJECT_SOURCE_DIR}/includes
        )
        ]]#
add_executable(AlexLens
#        AlexLens_static_lib
        src/ManagerModule/main.cpp
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
        src/PlatformModule/ModeUtil.cpp src/PlatformModule/ModeUtil.h
        src/ManagerModule/Manager.cpp src/ManagerModule/Manager.h
        src/ManagerModule/Executor.cpp src/ManagerModule/Executor.h
        src/PlatformModule/Platform.cpp src/PlatformModule/Platform.h
        src/PlatformModule/ASICPlatform.cpp src/PlatformModule/ASICPlatform.h
        includes/GUIModule/IObserver.h
        includes/GUIModule/Subject.h
        src/PlatformModule/PlatformManager.cpp src/PlatformModule/PlatformManager.h
        src/PlatformModule/CPUPlatformTorch.cpp src/PlatformModule/CPUPlatformTorch.h
        src/PlatformModule/PlatformType.h
        src/PlatformModule/PlatformStatistic.cpp src/PlatformModule/PlatformStatistic.h
        src/NeuralNetModule/Layer.cpp src/NeuralNetModule/Layer.h src/NeuralNetModule/Conv2D.cpp src/NeuralNetModule/Conv2D.h src/NeuralNetModule/ReLU.cpp src/NeuralNetModule/ReLU.h src/NeuralNetModule/MaxPool2D.cpp src/NeuralNetModule/MaxPool2D.h src/NeuralNetModule/Normalization.cpp src/NeuralNetModule/Normalization.h src/NeuralNetModule/FC.cpp src/NeuralNetModule/FC.h src/NeuralNetModule/Softmax.cpp src/NeuralNetModule/Softmax.h src/NeuralNetModule/AlexNetWeightParser.cpp src/NeuralNetModule/AlexNetWeightParser.h src/NeuralNetModule/AlexNet.cpp src/NeuralNetModule/AlexNet.h)

target_link_libraries(${PROJECT_NAME}
        #PRIVATE
        #AlexLens_static_lib
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        ${InferenceEngine_LIBRARIES}
        /home/viet/inference_engine_samples_build/intel64/Release/lib/libformat_reader.so
        /home/viet/pytorch/build/lib.linux-x86_64-3.7/torch/lib/libtorch.so
        /home/viet/pytorch/build/lib.linux-x86_64-3.7/torch/lib/libshm.so
        /home/viet/pytorch/build/lib.linux-x86_64-3.7/torch/lib/libc10.so
        ${HDF5_CXX_LIBRARIES}
        Eigen3::Eigen
        ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        )
