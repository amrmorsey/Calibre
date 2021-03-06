cmake_minimum_required(VERSION 3.6)
project(InferenceEngine)

set(CMAKE_CXX_STANDARD 11)


if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    # OPENCV_DIR needs to be properly set for windows linking to properly occur
    # Visual Studio 2015 (vc14) and Visual Studio 2017 (vc15) opencv binaries are compatible.
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)    # 64 bit
        set(OpenCV_DIR "D:/opencv/build/x64/vc14/lib")
    else (CMAKE_SIZEOF_VOID_P EQUAL 8)  # 32 bit
        set(OpenCV_DIR "D:/opencv/build/x86/vc14/lib")
    endif (CMAKE_SIZEOF_VOID_P EQUAL 8)

ELSE ()
    # Debugging conf
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -std=c++11")

    # Release conf
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -std=c++11 -O3 -DNDEBUG -Wall -Wno-sign-compare -Wno-uninitialized -Wno-c++11-narrowing")
ENDIF ()

find_package(OpenCV REQUIRED)

set(INFERENCE_ENGINE src/layers/ConvLayer.h src/Net.cpp src/Net.h src/layers/abstract_layers/AbstractLayer.h src/layers/MaxPool.h src/layers/FullyConnected.h src/layers/InputLayer.h src/MatrixAVX.h src/main.cpp src/layers/abstract_layers/AbstractPoolingLayer.h src/layers/abstract_layers/AbstractWeightedLayer.h src/layers/ReLU.h src/layers/Softmax.h src/layers/Sigmoid.h src/AlignedVector.h src/utils.h src/utils.cpp src/layers/Tanh.h)
add_executable(InferenceEngine ${INFERENCE_ENGINE})

target_link_libraries(InferenceEngine ${OpenCV_LIBS})