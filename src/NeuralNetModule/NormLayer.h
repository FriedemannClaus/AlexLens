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
    const int alpha;
    const int beta;
    const int normRegion;
    const int outputNumRows;
    const int outputNumCols;
    ThreeDMatrix outputMatrix;

public:
    NormLayer(const int inputWidth, const int inputHeight, const int inputChannels, const int normAlpha, const int normBeta, const in normRegionSize):
        //Initiatlisierungsliste
        Layer(inputWidth * inputHeight * inputChannels, inputWidth * inputHeight * inputChannels),
        inputNumRows(inputHeight),
        inputNumCols(inputWidth),
        inputNumChannels(inputChannels),
        alpha(normAlpha),
        beta(normBeta),
        normRegion(normRegionSize),
        outputNumRows(inputNumRows),
        outputNumCols(inputNumCols)
    {}

    ThreeDMatrix forward(const ThreeDMatrix &inputMatrix) {
        outputMatrix.resize(outputNumRows, outputNumCols);

        return outputMatrix;
    }
};

#endif //_NORMLAYER_H