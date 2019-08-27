//
// Created by viet on 25.08.19.
//
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <NeuralNetModule/ReLU.cpp>
#include "catch.hpp"

TEST_CASE( "ReLU: inputMatrix size equals outputMatrix size", "[fast]") {
     ThreeDMatrix testInput;
     ThreeDMatrix testOutput;
     ReLU *reLU = new ReLU();
     testInput.resize(5);
     for (int i = 0; i < 5; i++) {
         testInput(i).resize(6, 7);
     }

     reLU->forward(testInput, testOutput);
     REQUIRE(testOutput.rows() == 5);
     REQUIRE(testOutput(0).rows() == 6);
     REQUIRE(testOutput(0).cols() == 7);
}

TEST_CASE( "ReLU: outputMatrix contains only float scalars >= 0", "[fast]") {
    ThreeDMatrix testInput;
    ThreeDMatrix testOutput;
    ReLU *reLU = new ReLU();
    testInput.resize(1);
    testInput(0).resize(2, 3);
    testInput(0)(0, 0) = (float) -50.2323;
    testInput(0)(0, 1) = (float) -0;
    testInput(0)(0, 2) = (float) +0;
    testInput(0)(1, 0) = (float) -0.00001;
    testInput(0)(1, 1) = (float) +0.00001;
    testInput(0)(1, 2) = (float) 50.2323;

    reLU->forward(testInput, testOutput);

    REQUIRE(testOutput(0)(0, 0) >= 0);
    REQUIRE(testOutput(0)(0, 1) >= 0);
    REQUIRE(testOutput(0)(0, 2) >= 0);
    REQUIRE(testOutput(0)(1, 0) >= 0);
    REQUIRE(testOutput(0)(1, 1) >= 0);
    REQUIRE(testOutput(0)(1, 2) >= 0);
}

TEST_CASE( "ReLU: Activation function works correctly", "[fast][math]") {
    ThreeDMatrix testInput;
    ThreeDMatrix testOutput;
    ReLU *reLU = new ReLU();
    testInput.resize(1);
    testInput(0).resize(2, 3);
    testInput(0)(0, 0) = -2323.4445;
    testInput(0)(0, 1) = -0;
    testInput(0)(0, 2) = +0;
    testInput(0)(1, 0) = -0.00001;
    testInput(0)(1, 1) = 0.00001;
    testInput(0)(1, 2) = 2323.4445;

    reLU->forward(testInput, testOutput);

    REQUIRE(testOutput(0)(0, 0) == (float) 0);
    REQUIRE(testOutput(0)(0, 1) == (float) 0);
    REQUIRE(testOutput(0)(0, 2) == (float) 0);
    REQUIRE(testOutput(0)(1, 0) == (float) 0);

    REQUIRE(testOutput(0)(1, 1) == (float) 0.00001);
    REQUIRE(testOutput(0)(1, 2) == (float) 2323.4445);
}