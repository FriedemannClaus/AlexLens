//
// Created by jakubt on 27.08.19.
//
#define DELTA 1e-5

#include <NeuralNetModule/Softmax.cpp>
#include "catch.hpp"
#include <iostream>

TEST_CASE("Softmax: input vector size equals output vector size", "[fast]") {
    ThreeDMatrix testInput;
    Vector testOutput;
    int testSize = 1000;
    Softmax *softmax = new Softmax();

    testInput.resize(1);
    testInput(0).resize(testSize, 1);
    for (int i = 0; i < testSize; i++) {
        testInput(0)(i, 0) = (float)i/100;
        std::cout << testInput(0)(i,0);

    }
    std::cout << "\n";
    SECTION("Input vector size equals output vector size") {
        softmax->apply(testInput, testOutput);
        REQUIRE(testOutput.size() == testInput(0).rows());
    }

    SECTION("Output vector values sum up to 1") {
        softmax->apply(testInput, testOutput);
        float outputSum = 0;
        for (int i = 0; i < testOutput.size(); i++) {
            outputSum += testOutput(i);
            std::cout << testOutput(i);
        }
        std::cout << "\n";
        REQUIRE(outputSum == Approx(1.0).epsilon(DELTA));
    }


}
