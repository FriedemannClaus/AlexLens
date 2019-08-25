//
// Created by Viet Pham.
//

#include "Conv2D.h"
#include <iostream>

void Conv2D::forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) {
    ThreeDMatrix paddedMatrix;
    if (PAD > 0) {
        zeroPadding(inputMatrix, paddedMatrix);
    }
    else {
        paddedMatrix = inputMatrix;
    }

    //resize outputMatrix
    int paddedNumChannels = paddedMatrix.rows();
    int paddedNumRows = paddedMatrix(0).rows();
    int paddedNumCols = paddedMatrix(0).cols();

    int outputNumChannels = NUM_KERNELS;
    int outputNumRows = ((paddedNumRows - KERNEL_SIZE) / STRIDE) + 1;
    int outputNumCols = ((paddedNumCols - KERNEL_SIZE) / STRIDE) + 1;

    outputMatrix.resize(outputNumChannels);
    for (int i = 0; i < outputNumChannels; i++) {
        outputMatrix(i).resize(outputNumRows, outputNumCols);
    }

    //Preparation for matrix multiplication (flaten our matrices)
    int weightsNZ = WEIGHTS.cols();
    //resize X_col
    Matrix X_col;
    X_col.resize(KERNEL_SIZE * KERNEL_SIZE * weightsNZ, outputNumRows * outputNumCols);
    image2col(paddedMatrix, X_col);

    //resize W_row
    Matrix W_row;
    W_row.resize(NUM_KERNELS, KERNEL_SIZE * KERNEL_SIZE * weightsNZ);
    weights2row(W_row);

    //resize multResult
    Matrix multResult;
    multResult.resize(NUM_KERNELS, outputNumRows * outputNumCols); // WTF?

    // Let the multiplication begin
    multResult = W_row * X_col; //(dot product -> where the magic happens

    reshape(multResult, &outputMatrix);

    addBias(&outputMatrix);
}

void Conv2D::zeroPadding(ThreeDMatrix &inputMatrix, ThreeDMatrix &paddedMatrix) {
    int inputNumChannels = inputMatrix.rows();
    int inputNumRows = inputMatrix(0).rows();
    int inputNumCols = inputMatrix(0).cols();

    int paddedNumChannels = inputNumChannels;
    int paddedNumRows = inputNumRows + 2 * PAD;
    int paddedNumCols = inputNumCols + 2 * PAD;

    // resize padded Matrix and init with zero
    paddedMatrix.resize(paddedNumChannels);
    for (int i = 0; i < paddedNumChannels; i++) {
        paddedMatrix(i).resize(paddedNumRows, paddedNumCols);
        paddedMatrix(i).setZero(paddedNumRows, paddedNumCols);
    }

    // copy inputMatrix into new paddedMatrix
    for (int i = 0; i < inputNumChannels; i++) {
        for (int j = 0; j < inputNumCols; j++) {
            for (int k = 0; k < inputNumRows; k++) {
                paddedMatrix(i)(k + PAD, j + PAD) = inputMatrix(i)(k, j);
            }
        }
    }
}

void Conv2D::image2col(ThreeDMatrix &inputMatrix, Matrix &convertedMatrix) {
    int numKernelElements = KERNEL_SIZE * KERNEL_SIZE;
    int inputNumChannels = inputMatrix.rows();
    int numStridesPerRowCol = ((inputMatrix(0).rows() - KERNEL_SIZE) / STRIDE) + 1;


    for (int j = 0; j < convertedMatrix.cols(); j++) {
        for (int i = 0; i < convertedMatrix.rows(); i++) {
            convertedMatrix(i, j) = inputMatrix(i / numKernelElements)(((i % numKernelElements) / KERNEL_SIZE ) + (j / numStridesPerRowCol) * STRIDE,
                                                                       ((i % numKernelElements) % KERNEL_SIZE) + (j % numStridesPerRowCol) * STRIDE);

        }
    }
}

void Conv2D::weights2row(Matrix &convertedWeights) {
    int weightsNK = WEIGHTS.rows();
    int weightsNZ = WEIGHTS.cols();
    int numKernelElements = KERNEL_SIZE * KERNEL_SIZE;

    for (int i = 0; i < NUM_KERNELS; i++) {
        for (int j = 0; j < KERNEL_SIZE * KERNEL_SIZE * weightsNZ; j++) {
            convertedWeights(i, j) = WEIGHTS(i, (j / numKernelElements)) ( (j % numKernelElements) / KERNEL_SIZE,  (j % numKernelElements) % KERNEL_SIZE);
        }
    }
}

void Conv2D::reshape(Matrix &resultMatrix, ThreeDMatrix *outputMatrix) { //needs check
    int outputNumRows = (*outputMatrix)(0).rows();
    int outputNumCols = (*outputMatrix)(0).cols();
    for (int i = 0; i < NUM_KERNELS; i++) {
        for (int j = 0; j < outputNumRows; j++) {
            for (int k = 0; k < outputNumCols; k++) {
                (*outputMatrix)(i)(j, k) = resultMatrix(i, k + j * outputNumCols);
            }
        }
    }
}

void Conv2D::addBias(ThreeDMatrix *outputMatrix) {
    int outputNumKernels = (*outputMatrix).rows();
    int outputNumRows = (*outputMatrix)(0).rows();
    int outputNumCols = (*outputMatrix)(0).cols();
    for (int i = 0; i < outputNumKernels; i++) {
        for (int j = 0; j < outputNumCols; j++) {
            for (int k = 0; k < outputNumRows; k++) {
                (*outputMatrix)(i)(k, j) += BIAS(i);
            }
        }
    }
}
