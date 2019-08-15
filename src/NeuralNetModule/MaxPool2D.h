/**
 * Maxpooling 2d layer
 * @author Viet Pham
 */


#ifndef _MAXPOOL2D_H
#define _MAXPOOL2D_H

#include "Layer.h"


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
    ThreeDMatrix outputMatrix;

    float getMaxFloat(Vector *floats) {
        float result = (*floats)(0);
        int numPoolElements = poolWidht * poolWidth;
        for (int i = 0; i < (numPoolElements - 1); i++) {
            if ((*floats)(i + 1) > result) result = (*floats)(i + 1));
        }
        return result;
    }


public:
    MaxPool2D(const int inputWidth, const int inputHeight, const int inputChannels, const int poolWidth, const int poolHeight, const int poolStride):
    //Initialisierungsliste

            Layer(inputWidth * inputHeight * inputChannels, (((inputWidth - poolWidth) / poolStride) + 1) * (((inputHeight - poolHeight) / poolStride) + 1) * inputChannels),
            inputNumRows(inputHeight),
            inputNumCols(inputWidth),
            inputNumChannels(inputChannels),
            poolNumRows(poolHeight),
            poolNumCols(poolWidth),
            outputNumRows(inputNumRows / poolNumRows),
            outputNumCols(inputNumCols / poolNumCols),
            stride(poolStride)
    {}

     ThreeDMatrix forward(const ThreeDMatrix &inputMatrix) {
        outputMatrix.resize(outputNumRows, outputNumCols);
        int outputSize = ((inputChannelNumCols - poolWidth) / poolStride) + 1; //size of one side!
        int numPoolElements = poolWidht * poolWidth;
        for (int c = 0; c < inputNumChannels; c++) { // Iterieren ueber Channel
            for (int i = 0; i < outputSize; i++) { // Iterieren ueber Zeilen
                for (int j = 0; j < outputSize; j++) { // Iterieren ueber Spalten
                    float floats<numPoolElements>;
                    Vector floats;
                    for (int k = 0; k < numPoolElements; k++) {
                        floats(k) = (*inputMatrix)(c)((i * stride) + (k / 3), (j * stride) + (k % 3));
                    }
                    float max = getMaxFloat(&floats);
                    outputMatrix(i)(j, k) = max; // i,j,k?! -> Überprüfen
                }
            }
        }
        return outputMatrix;
    }




};

#endif //_MAXPOOL2D_H