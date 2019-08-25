//
// Created by Viet Pham.
//

#include "FC.h"
#include <iostream>

void FC::forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) {
    // We don't "work" with inputMatrix and outputMatrix.
    // inputMatrix will be converted from ThreeDMatrix to a Vector
    // After multiplication we fill our Vector into ThreeDMatrix outputMatrix
    int inputNumChannels = inputMatrix.rows();
    int inputNumRows = inputMatrix(0).rows();
    int inputNumCols = inputMatrix(0).cols();

    //resize outputMatrix
    int outputNumChannels = 1;
    int outputNumRows = NEURONS;
    int outputNumCols = 1;

    outputMatrix.resize(outputNumChannels);
    outputMatrix(0).resize(outputNumRows, outputNumCols);

    //resize X_row
    Vector X_row;
    X_row.resize(inputNumChannels * inputNumRows * inputNumCols);
    flaten(inputMatrix, X_row);

    // multiplication
    Vector multResult = X_row.transpose() * WEIGHTS;

    // add bias
    multResult += BIAS;

    // copy result into outputMatrix
    for (int i = 0; i < multResult.rows(); i++) {
        outputMatrix(0)(i, 0) = multResult(i);
    }





}

void FC::flaten(ThreeDMatrix &inputMatrix, Vector &convertedVector) {
    int inputNumChannels = inputMatrix.rows();
    int inputNumRows = inputMatrix(0).rows();
    int inputNumCols = inputMatrix(0).cols();
    int inputPatchSize = inputNumRows * inputNumCols;

    if (inputNumChannels > 1) {
        for (int i = 0; i < convertedVector.rows(); i++) {
            convertedVector(i) = inputMatrix(i / inputPatchSize)((i % inputPatchSize) / inputNumRows //
                    , (i % inputPatchSize) % inputNumCols); //
        }
    }
    else if (inputNumChannels == 1) { //input flat already, just put in vector
        for (int i = 0; i < convertedVector.rows(); i++) {
            convertedVector(i) = inputMatrix(0)(i, 0);
        }
    }


}
