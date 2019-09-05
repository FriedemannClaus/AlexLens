//
// Created by jakubt on 28.08.19.
//
#define DELTA 0.05
#include <NeuralNetModule/Normalization.cpp>
#include <iostream>
#include "catch.hpp"
TEST_CASE("Normalization: Normalization function works correctly", "[fast]") {
    int hyperKNorm = 0;
    int hyperAlpha = 1;
    int hyperBeta = 1;
    int hyperN = 2;
    ThreeDMatrix inputMatrix;
    ThreeDMatrix expectedOutputMatrix;
    ThreeDMatrix outputMatrix;
    int inputChannels = 4;
    inputMatrix.resize(inputChannels);
    for (int i = 0; i < inputChannels; i++) {
        inputMatrix(i).resize(3, 3);
    }
    inputMatrix(0) << 1, 2, 3, 4, 3, 6, 7, 8, 9;
    inputMatrix(1) << 1, 2, 1, 2, 3, 2, 3, 4, 3;
    inputMatrix(2) << 2, 1, 2, 3, 2, 3, 4, 3, 4;
    inputMatrix(3) << 4, 2, 1, 5, 2, 1, 2, 2, 4;
    expectedOutputMatrix.resize(inputChannels);
    for (int i = 0; i < inputChannels; i++) {
        expectedOutputMatrix(i).resize(3, 3);
    }
    //approximiertes Ergebnis auf 2 nachkommastellen
    expectedOutputMatrix(0)<<0.5, 0.25, 0.3, 0.2, 0.17, 0.15, 0.12, 0.1, 0.1;
    expectedOutputMatrix(1)<<0.17, 0.22, 0.07, 0.07, 0.14, 0.04, 0.04, 0.04, 0.03;
    expectedOutputMatrix(2)<<0.1, 0.11, 0.33, 0.08, 0.12, 0.21, 0.14, 0.1, 0.1;
    expectedOutputMatrix(3)<<0.2, 0.4, 0.2, 0.15, 0.25, 0.1, 0.1, 0.15, 0.13;
    Normalization *normalization = new Normalization(hyperKNorm, hyperAlpha, hyperBeta, hyperN);
    SECTION("Output matrix size equals input matrix size") {
        normalization->forward(inputMatrix, outputMatrix);
        int inputDepth = inputMatrix.size();
        REQUIRE(inputDepth == outputMatrix.size());
        for (int i = 0; i < inputDepth; i++) {
            REQUIRE(inputMatrix(i).rows() == outputMatrix(i).rows());
            REQUIRE(inputMatrix(i).cols() == outputMatrix(i).cols());
        }
    }
    SECTION("Output matrix is calculated correctly") {
        normalization->forward(inputMatrix, outputMatrix);
        int inputDepth = inputMatrix.size();
        int inputRows = inputMatrix(0).rows();
        int inputCols = inputMatrix(0).cols();
        for(int i=0; i<inputDepth;i++){
            for(int j=0;j<inputRows;j++){
                for(int k=0;k<inputCols;k++){
                    REQUIRE(fabsf(expectedOutputMatrix(i)(j,k)-outputMatrix(i)(j,k)) == Approx(0.0).margin(0.005));
                }
            }
        }
    }
}