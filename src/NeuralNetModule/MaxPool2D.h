/**
 * Maxpooling 2d layer
 * @author Viet Pham
 */


#ifndef _MAXPOOL2D_H
#define _MAXPOOL2D_H

#include "Layer.h"
#include <assert.h>


class MaxPool2D: public Layer {

private:
    const int inputNumRows;
    const int inputNumCols;
    const int inputNumChannels;
    const int poolNumRows;
    const int poolNumCols;
    const int outputNumRows;
    const int outputNumCols;
    const int stride;

    float getMaxFloat(Vector *floats) {
        float result = (*floats)(0);
        int numPoolElements = poolNumCols * poolNumRows;
        for (int i = 0; i < (numPoolElements - 1); i++) {
            if ((*floats)(i + 1) > result) result = (*floats)(i + 1);
        }
        return result;
    }


public:
    MaxPool2D(const int inputWidth, const int inputHeight, const int inputChannels, const int poolWidth, const int poolHeight, const int poolStride):
    //Initialisierungsliste

            //Layer(inputWidth * inputHeight * inputChannels, (((inputWidth - poolWidth) / poolStride) + 1) * (((inputHeight - poolHeight) / poolStride) + 1) * inputChannels),
            inputNumRows(inputHeight),
            inputNumCols(inputWidth),
            inputNumChannels(inputChannels),
            poolNumRows(poolHeight),
            poolNumCols(poolWidth),
            outputNumRows(((inputNumRows - poolNumRows) / poolStride) + 1),
            outputNumCols(((inputNumCols - poolNumCols) / poolStride) + 1),
            stride(poolStride)
    {}

    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override {
        assert(inputMatrix.rows() == inputNumChannels);
        assert(inputMatrix(0).cols() == inputNumCols);
        assert(inputMatrix(0).rows() == inputNumRows);
        int outputNumChannels = inputNumChannels;

        outputMatrix.resize(inputNumChannels);
        for (int i = 0; i < inputNumChannels; i++) {
            outputMatrix(i).resize(outputNumRows, outputNumCols);
        }

        int outputSize = ((inputNumCols - poolNumCols) / stride) + 1; //size of one side!
        int numPoolElements = poolNumCols * poolNumRows;
        for (int c = 0; c < inputNumChannels; c++) { // Iterieren ueber Channel
            for (int i = 0; i < outputSize; i++) { // Iterieren ueber Zeilen des Outputs
                for (int j = 0; j < outputSize; j++) { // Iterieren ueber Spalten des Outputs
                    Vector floats;
                    floats.resize(numPoolElements);
                    for (int k = 0; k < numPoolElements; k++) {
                        floats(k) = (inputMatrix)(c)((i * stride) + (k / 3), (j * stride) + (k % 3)); //Fehler
                    }
                    float max = getMaxFloat(&floats);
//                    cout << "max: " << max << endl;
                    outputMatrix(c)(i, j) = max;
                }
            }
        }
    }
};

#endif //_MAXPOOL2D_H