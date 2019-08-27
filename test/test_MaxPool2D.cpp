//
// Created by viet on 27.08.19.
//

#include <NeuralNetModule/MaxPool2D.cpp>
#include "catch.hpp"
#include <iostream>

TEST_CASE("MaxPool2D: AlexNet max pooling works correctly", "[fast]") {
    MaxPool2D *maxPool =  new MaxPool2D(3, 3, 2);
    ThreeDMatrix testMatrix;
    testMatrix.resize(1);
    testMatrix(0).resize(5, 5);
    int k = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            testMatrix(0)(i, j) = k;
            k++;
        }
    }
    ThreeDMatrix outputMatrix;
    maxPool->forward(testMatrix, outputMatrix);

    SECTION("Output matrix gets resized correctly") {
        REQUIRE(outputMatrix.rows() == 1);
        REQUIRE(outputMatrix(0).rows() == 2);
        REQUIRE(outputMatrix(0).cols() == 2);
    }

    SECTION("Max pooled values are correct") {
        REQUIRE(outputMatrix(0)(0, 0) == (float) 13);
        REQUIRE(outputMatrix(0)(0, 1) == (float) 15);
        REQUIRE(outputMatrix(0)(1, 0) == (float) 23);
        REQUIRE(outputMatrix(0)(1, 1) == (float) 25);
    }
}

TEST_CASE( "MaxPool2D: Pooling with non standard pool size and stride works") {
    MaxPool2D *testPool = new MaxPool2D(2, 2, 3);
    ThreeDMatrix dtestMatrix;
    dtestMatrix.resize(1);
    dtestMatrix(0).resize(5, 5);
    int k = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            dtestMatrix(0)(i, j) = k;
            k++;
        }
    }
    ThreeDMatrix outputMatrix;
    testPool->forward(dtestMatrix, outputMatrix);

    SECTION("Output matrix gets resized correctly") {
        REQUIRE(outputMatrix.rows() == 1);
        REQUIRE(outputMatrix(0).rows() == 2);
        REQUIRE(outputMatrix(0).cols() == 2);
    }

    SECTION("Max pooled values are correct") {
        REQUIRE(outputMatrix(0)(0, 0) == (float) 7);
        REQUIRE(outputMatrix(0)(0, 1) == (float) 10);
        REQUIRE(outputMatrix(0)(1, 0) == (float) 22);
        REQUIRE(outputMatrix(0)(1, 1) == (float) 25);
    }
}
