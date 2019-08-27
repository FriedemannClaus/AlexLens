//
// Created by Viet Pham.
//

#include "MaxPool2D.h"

void MaxPool2D::forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) {
    int inputNumChannels = inputMatrix.rows();
    int inputNumRows = inputMatrix(0).rows();
    int inputNumCols = inputMatrix(0).cols();
    int outputNumRows = ((inputNumRows - poolNumRows) / stride) + 1;
    int outputNumCols = ((inputNumCols - poolNumCols) / stride) + 1;

    outputMatrix.resize(inputNumChannels);
    for (int i = 0; i < inputNumChannels; i++) {
        outputMatrix(i).resize(outputNumRows, outputNumCols);
    }

    int outputSize = ((inputNumCols - poolNumCols) / stride) + 1; //size of one side!
    int numPoolElements = poolNumCols * poolNumRows;
    for (int c = 0; c < inputNumChannels; c++) { // Iterieren ueber Channel
        for (int i = 0; i < outputSize; i++) { // Iterieren ueber Spalten des Outputs
            for (int j = 0; j < outputSize; j++) { // Iterieren ueber Zeilen des Outputs
                Vector floats;
                floats.resize(numPoolElements);
                for (int k = 0; k < numPoolElements; k++) {
                    floats(k) = (inputMatrix)(c)((j * stride) + (k % poolNumRows), (i * stride) + (k / poolNumRows));
                }
                float max = getMaxFloat(&floats);
                outputMatrix(c)(j, i) = max;
            }
        }
    }


}

float MaxPool2D::getMaxFloat(Vector *floats) {
    float result = (*floats)(0);
    int numPoolElements = poolNumCols * poolNumRows;
    for (int i = 0; i < (numPoolElements - 1); i++) {
        if ((*floats)(i + 1) > result) result = (*floats)(i + 1);
    }
    return result;
}
