//
// Created by Viet Pham.
//

#include "ReLU.h"

float ReLU::max(float a) {
    return ((a > 0) ? a : 0);
}

void ReLU::forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) {
    int inputNumRows = inputMatrix(0).rows();
    int inputNumCols = inputMatrix(0).cols();
    int inputNumChannels = inputMatrix.rows();

    outputMatrix.resize(inputNumChannels);
    for (int i = 0; i < inputNumChannels; i++) {
        outputMatrix(i).resize(inputNumRows, inputNumCols);
    }

    for (int i = 0; i < inputNumChannels; i++) { // Iterieren über Channel
        for (int j = 0; j < inputNumCols; j++) { // Iterieren über Spalten
            for (int k = 0; k < inputNumRows; k++) { // Iterieren über Zeilen
                outputMatrix(i)(k, j) = max(inputMatrix(i)(k, j));
            }
        }
    }
}
