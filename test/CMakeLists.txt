project(AlexLens_tests)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
    #Uncomment in case of linker errors
    #link_libraries(clang_rt.profile-x86_64)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    #Uncomment in case of linker errors
    link_libraries(gcov)
endif ()

add_executable(AlexLens_tests test_ReLU.cpp test_MaxPool2D.cpp test_Softmax.cpp test_Normalisation.cpp test_Conv2D.cpp test_Manager.cpp test_Executor.cpp ../src/Exceptions/ReadException.h ../src/Exceptions/StickException.h)
target_link_libraries(AlexLens_tests AlexLens_lib catch)

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
include_directories(${Torch_INCLUDE_DIRS})
#find_package(Torch REQUIRED)

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

target_link_libraries(AlexLens_tests
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        ${InferenceEngine_LIBRARIES}
        /home/pselabs19/inference_engine_samples_build/intel64/Release/lib/libformat_reader.so
        ${HDF5_CXX_LIBRARIES}
        Eigen3::Eigen
        ${OpenCV_LIBS}
        ${PYTHON_LIBRARIES}
        ${TORCH_LIBRARIES}
        )