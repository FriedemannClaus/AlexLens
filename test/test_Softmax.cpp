//
// Created by jakubt on 27.08.19.
//
#define DELTA 1e-5

#include <NeuralNetModule/Softmax.cpp>
#include "catch.hpp"
#include <cstdlib>

TEST_CASE("Softmax: correct functioning of the Softmax function", "[fast]") {

    ThreeDMatrix testInput2;
    Vector testOutput2;
    int testSize = 1000;
    int testSize2 = 73;
    Softmax *softmax = new Softmax();

    testInput2.resize(1);
    testInput2(0).resize(testSize2, 1);
    for (int i = 0; i < testSize2; i++) {
        testInput2(0)(i, 0) = (float) (rand() % 100) / 100;
    }
    SECTION("Handling big activation values") {
        ThreeDMatrix testInput;
        Vector testOutput;
        testInput.resize(1);
        testInput(0).resize(testSize, 1);
        for (int i = 0; i < testSize; i++) {
            testInput(0)(i, 0) = (float) i;
        }
        REQUIRE_THROWS(softmax->apply(testInput, testOutput));
    }
    SECTION("Input vector size equals output vector size") {

        softmax->apply(testInput2, testOutput2);
        REQUIRE(testOutput2.size() == testInput2(0).rows());
    }
    SECTION("Output vector values sum up to 1") {
        softmax->apply(testInput2, testOutput2);
        float outputSum = 0;
        for (int i = 0; i < testOutput2.size(); i++) {
            outputSum += testOutput2(i);
        }
        REQUIRE(1.0 == Approx(outputSum).epsilon(DELTA));
    }
}
