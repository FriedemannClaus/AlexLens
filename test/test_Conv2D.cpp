//
// Created by jakubt on 30.08.19.
//

#define DELTA 0.05

#include <NeuralNetModule/Conv2D.cpp>
#include "catch.hpp"
#include <stdio.h>

float calculateExpectedOutputSize(int inputSize, int kernelSize, int stride, int pad) {
    return (float) (inputSize - kernelSize + 2 * pad) / stride + 1;
}

TEST_CASE("Convolution forward pass functions correctly", "[slow]") {
    ThreeDMatrix inputMatrix;
    ThreeDMatrix outputMatrix;
    ThreeDMatrix expectedOutputMatrix;
    FourDMatrix weights;
    Vector bias;
    int hyperNumKernels = 2;
    int hyperKernelSize = 3;
    int hyperStride = 2;
    int hyperPad = 1;

    int inputSize = 5;
    int inputDepth = 3;
    inputMatrix.resize(inputDepth);
    for (int i = 0; i < 3; i++) {
        inputMatrix(i).resize(inputSize, inputSize);
    }
    inputMatrix(0) << 1, 1, 1, 0, 0,
            2, 1, 0, 0, 1,
            2, 1, 1, 2, 2,
            1, 2, 2, 0, 1,
            1, 1, 1, 1, 0;
    inputMatrix(1) << 1, 1, 2, 1, 1,
            1, 1, 1, 2, 2,
            2, 2, 1, 2, 1,
            2, 0, 2, 1, 2,
            2, 2, 1, 2, 2;
    inputMatrix(2) << 1, 0, 0, 1, 0,
            0, 0, 1, 2, 1,
            2, 0, 2, 0, 1,
            2, 2, 0, 2, 0,
            0, 2, 1, 1, 0;


    weights.resize(hyperNumKernels, inputDepth);
    for (int i = 0; i < hyperNumKernels; i++) {
        for (int j = 0; j < inputDepth; j++) {
            weights(i, j).resize(hyperKernelSize, hyperKernelSize);
        }
    }
    weights(0, 0) << 0, 1, 1,
            1, -1, 1,
            1, 0, 1;
    weights(0, 1) << 1, 1, 1,
            -1, 1, -1,
            0, 1, -1;
    weights(0, 2) << 0, 1, 0,
            0, -1, 1,
            1, -1, 0;
    weights(1, 0) << 0, 1, 0,
            1, 1, 1,
            1, 1, 1;
    weights(1, 1) << 0, 1, 0,
            1, 1, 1,
            1, 1, 1;
    weights(1, 2) << 1, 1, -1,
            -1, -1, -1,
            1, -1, 1;

    bias.resize(hyperNumKernels);
    bias(0) = 1;
    bias(1) = 0;

    int expectedOutputSize = calculateExpectedOutputSize(inputSize, hyperKernelSize, hyperStride, hyperPad);

    expectedOutputMatrix.resize(hyperNumKernels);
    for (int i = 0; i < hyperNumKernels; i++) {
        expectedOutputMatrix(i).resize(expectedOutputSize, expectedOutputSize);
    }
    expectedOutputMatrix(0) << 0, 1, 4,
            4, 6, 9,
            9, 3, 6;
    expectedOutputMatrix(1) << 3, 1, 1,
            7, 9, 12,
            3, 3, 5;

    SECTION("Output matrix has correct size") {
        for (hyperStride = 0; hyperStride < 5; hyperStride++) {
            expectedOutputSize = ceilf(calculateExpectedOutputSize(inputSize, hyperKernelSize, hyperStride, hyperPad));
            int expectedOutputSize_Floor = floorf(calculateExpectedOutputSize(inputSize, hyperKernelSize, hyperStride,
                                                                              hyperPad));
          Conv2D *conv2D = new Conv2D(hyperNumKernels, hyperKernelSize, hyperStride, hyperPad, weights, bias, false);
            if (hyperStride == 0) {
                //TODO
                //REQUIRE_THROWS(conv2D->forward(inputMatrix, outputMatrix));

            } else {
                conv2D->forward(inputMatrix, outputMatrix);


                if (expectedOutputSize != expectedOutputSize_Floor) {
                    REQUIRE_THROWS(conv2D->forward(inputMatrix, outputMatrix));
                } else {
                    int outputSize = outputMatrix.size();
                    REQUIRE(outputSize == hyperNumKernels);
                    for (int i = 0; i < outputSize; i++) {
                        REQUIRE(outputMatrix(i).rows() == expectedOutputSize);
                        REQUIRE(outputMatrix(i).cols() == expectedOutputSize);
                    }
                }
            }

        }

    }

    SECTION("Input matrix is correctly zero-padded") {


    }
}
