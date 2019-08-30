//
// Created by Viet Pham.
//
#include "Normalization.h"
int Normalization::max(int a, int b) {
    return ((a > b) ? a : b);
}
int Normalization::min(int a, int b) {
    return ((a < b) ? a : b);
}
void Normalization::forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) {
    int inputNumChannels = inputMatrix.rows();
    int inputNumRows = inputMatrix(0).rows();
    int inputNumCols = inputMatrix(0).cols();
    int outputNumRows = inputNumRows;
    int outputNumCols = inputNumCols;
    outputMatrix.resize(inputNumChannels);
    for (int i = 0; i < inputNumChannels; i++) {
        outputMatrix(i).resize(outputNumRows, outputNumCols);
    }
    // Inter-Channel LRN
    for (int i = 0; i < inputNumCols; i++) { // Iterieren über Spalten
        for (int j = 0; j < inputNumRows; j++) { // Iterieren über Zeilen
            for (int k = 0; k < inputNumChannels; k++) { // Iterieren über Channel
                // Summe berechnen:
                float sum = 0;
                for (int l = max(0, k - (n / 2)); l <= min(inputNumChannels - 1, k + (n / 2)); l++) {
                    sum += pow((inputMatrix)(l)(j, i), 2);
                }
                outputMatrix(k)(j, i) = (inputMatrix)(k)(j, i) / pow((kNorm + alpha * sum), beta);
            }
        }
    }
}