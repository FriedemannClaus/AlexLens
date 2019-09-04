project(AlexLens_prog)
# Main program
set(CMAKE_INCLUDE_CURRENT_DIR )
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_CXX_FLAGS -pthread)
#find_package(libusb-1.0 REQUIRED)
#include_directories (${LIBUSB_1_INCLUDE_DIRS})
find_package(PkgConfig REQUIRED)
pkg_search_module(LIBUSB1 REQUIRED libusb-1.0)
include_directories(SYSTEM ${LIBUSB1_INCLUDE_DIRS})
find_package(Threads)

include_directories(../includes)

# OpenCL
find_package(OpenCL REQUIRED)

# Qt5
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
list(APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core)


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

# Torch
set(Torch_DIR ../thirdparty/libtorch/share/cmake/Torch)
find_package(Torch REQUIRED)
message(STATUS "Torch library status:")
message(STATUS "    version: ${Torch_VERSION}")
message(STATUS "    libraries: ${Torch_LIBRARIES}")
message(STATUS "    include path: ${Torch_INCLUDE_DIRS}")

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

#Static library with all sources that need to be tested in unit tests
add_library(AlexLens_lib STATIC
        ManagerModule/Manager.cpp
        GUIModule/InputPanel.cpp
        GUIModule/helpform.cpp
        GUIModule/statisticform.cpp
        GUIModule/mainwindow.cpp
        GUIModule/parameterpanel.cpp
        GUIModule/outputclassifypanel.cpp
        PlatformModule/ModeUtil.cpp
        ManagerModule/Manager.cpp
        ManagerModule/Executor.cpp
        PlatformModule/Platform.cpp
        PlatformModule/ASICPlatform.cpp
        PlatformModule/PlatformManager.cpp
        PlatformModule/CPUPlatformTorch.cpp
        PlatformModule/PlatformStatistic.cpp
        PlatformModule/GPUPlatform.cpp
        NeuralNetModule/Layer.cpp
        NeuralNetModule/Conv2D.cpp
        NeuralNetModule/ReLU.cpp
        NeuralNetModule/MaxPool2D.cpp
        NeuralNetModule/Normalization.cpp
        NeuralNetModule/FC.cpp
        NeuralNetModule/Softmax.cpp
        NeuralNetModule/AlexNetWeightParser.cpp
        NeuralNetModule/AlexNet.cpp
        NeuralNetModule/GPUSGeMM.cpp
        PlatformModule/CPUPlatform.cpp
        Exceptions/ReadException.h Exceptions/StickException.h)

target_include_directories(AlexLens_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        /usr/include/eigen3
        ${InferenceEngine_INCLUDE_DIRS}
        ${HDF5_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${Torch_INCLUDE_DIRS}
        /home/dmitrii/AlexLens/thirdparty/libtorch/include
        /home/dmitrii/AlexLens/thirdparty/libtorch/include/torch/csrc/api/include/
        ${Thread_INCLUDE_DIRS}
        ${PYTHON_INCLUDE_DIRS}
        #APPEND THIRD-PARTY-LIBS Qt::Widgets Qt::Core
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        )

target_link_libraries(AlexLens_lib PRIVATE
        #PRIVATE
        #AlexLens_static_lib
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        ${InferenceEngine_LIBRARIES}
        /home/jakubt/inference_engine_samples_build/intel64/Release/lib/libformat_reader.so
        ${HDF5_CXX_LIBRARIES}
        Eigen3::Eigen
        ${OpenCV_LIBS}
        ${OpenCL_LIBRARIES}
        ${PYTHON_LIBRARIES}
        ${TORCH_LIBRARIES}
        )


add_executable(AlexLens_prog
        ManagerModule/main.cpp
        ManagerModule/Manager.cpp ManagerModule/Manager.h
        GUIModule/InputPanel.cpp GUIModule/inputpanel.h
        GUIModule/helpform.cpp GUIModule/helpform.h
        GUIModule/statisticform.cpp GUIModule/statisticform.h
        GUIModule/mainwindow.cpp GUIModule/mainwindow.h
        GUIModule/parameterpanel.cpp GUIModule/parameterpanel.h
        GUIModule/outputclassifypanel.cpp GUIModule/outputclassifypanel.h
        PlatformModule/Mode.h
        ../Icon/icon.qrc
        PlatformModule/ModeUtil.cpp PlatformModule/ModeUtil.h
        PlatformModule/ModeUtil.cpp PlatformModule/ModeUtil.h
        ManagerModule/Manager.cpp ManagerModule/Manager.h
        ManagerModule/Executor.cpp ManagerModule/Executor.h
        PlatformModule/Platform.cpp PlatformModule/Platform.h
        PlatformModule/ASICPlatform.cpp PlatformModule/ASICPlatform.h
        PlatformModule/GPUPlatform.cpp PlatformModule/GPUPlatform.h
        NeuralNetModule/GPUSGeMM.cpp NeuralNetModule/GPUSGeMM.h
        GUIModule/IObserver.h
        GUIModule/Subject.h
        PlatformModule/PlatformManager.cpp PlatformModule/PlatformManager.h
        PlatformModule/CPUPlatformTorch.cpp PlatformModule/CPUPlatformTorch.h
        PlatformModule/PlatformType.h
        PlatformModule/PlatformStatistic.cpp PlatformModule/PlatformStatistic.h
        NeuralNetModule/Layer.cpp NeuralNetModule/Layer.h NeuralNetModule/Conv2D.cpp NeuralNetModule/Conv2D.h NeuralNetModule/ReLU.cpp NeuralNetModule/ReLU.h NeuralNetModule/MaxPool2D.cpp NeuralNetModule/MaxPool2D.h NeuralNetModule/Normalization.cpp NeuralNetModule/Normalization.h NeuralNetModule/FC.cpp NeuralNetModule/FC.h NeuralNetModule/Softmax.cpp NeuralNetModule/Softmax.h NeuralNetModule/AlexNetWeightParser.cpp NeuralNetModule/AlexNetWeightParser.h NeuralNetModule/AlexNet.cpp NeuralNetModule/AlexNet.h PlatformModule/CPUPlatform.cpp PlatformModule/CPUPlatform.h Exceptions/ReadException.h Exceptions/StickException.h)

target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        ${InferenceEngine_LIBRARIES}
        /home/jakubt/inference_engine_samples_build/intel64/Release/lib/libformat_reader.so
        ${HDF5_CXX_LIBRARIES}
        Eigen3::Eigen
        ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        ${TORCH_LIBRARIES}
        ${OpenCL_LIBRARIES}
        /usr/lib/x86_64-linux-gnu/libusb-1.0.so
        AlexLens_lib
        )