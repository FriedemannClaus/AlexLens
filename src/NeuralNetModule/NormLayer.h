/**
 * Local Response Normalization Layer (across channels)
 * @author Viet Pham
 */



#ifndef _NORMLAYER_H
#define _NORMLAYER_H

#include "Layer.h"


class NormLayer: public Layer {
private:
    const int inputNumRows;
    const int inputNumCols;
    const int inputNumChannels;
    const int k;
    const int alpha;
    const int beta;
    const int n;
    const int outputNumRows;
    const int outputNumCols;
    ThreeDMatrix outputMatrix;

public:
    NormLayer(const int inputWidth, const int inputHeight, const int inputChannels, const int normK, const int normAlpha, const int normBeta, const in normRegionSize):
        //Initialisierungsliste
        Layer(inputWidth * inputHeight * inputChannels, inputWidth * inputHeight * inputChannels),
        inputNumRows(inputHeight),
        inputNumCols(inputWidth),
        inputNumChannels(inputChannels),
        k(normK);
        alpha(normAlpha),
        beta(normBeta),
        n(normRegionSize),
        outputNumRows(inputNumRows),
        outputNumCols(inputNumCols)
    {}

    ThreeDMatrix forward(const ThreeDMatrix &inputMatrix) {
        outputMatrix.resize(outputNumRows, outputNumCols);
        for (int i = 0; i < inputNumRows; i++) { // Iterieren über Reihen
            for (int j = 0; j < inputNumCols; j++) { // Iterieren über Spalten
                for (int k = 0; k < inputNumChannels; k++) { // Iterieren über Channel
                    // Summe berechnen:
                    float sum = 0;
                    for (int l = max(0, k - (n / 2)); l <= min(inputNumChannels - 1, k + (n / 2)); l++) {
                        sum += pow((*inputMatrix)(l)(i, j), 2);
                    }

                    outputMatrix(k)(i, j) = (*inputMatrix)(k)(i, j) / pow((k + alpha * sum), beta);
                }
            }
        }

        return outputMatrix;
    }

    int max(int a, int b) {
        return ((a > b) ? a : b);
    }

    int min(int a, int b) {
        return ((a < b) ? a : b);
    }
};

#endif //_NORMLAYER_H