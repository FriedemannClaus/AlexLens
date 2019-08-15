//
// Created by viet on 08.08.19.
//

#include "Layer.h"

/*const Layer::Matrix& ReLULayer::forward(const Layer::Matrix &input){
//    int columns = x.cols();
//    x.array() = x.array()cwiseMax(Scalar(0));
//    r.resize(this->outputSize, columns);
//    r.array() = x.array();
    return input;*/

class ReLULayer: public Layer {

private:
    const int inputNumRows;
    const int inputNumCols;
    const int inputNumChannels;

    float max(float a) {
        return ((a > 0) ? a : 0);
    }

public:
    ReLULayer(const int inputWidth, const int inputHeight, const int inputChannels):
    //Initialisierungsliste
            Layer(inputWidth * inputHeight * inputChannels, inputWidth * inputHeight * inputChannels),
            inputNumRows(inputHeight),
            inputNumCols(inputWidth),
            inputNumChannels(inputChannels),
    {}

    void forward(const ThreeDMatrix &inputMatrix) {
        for (int i = 0; i < inputNumChannels; i++) {
            for (int j = 0; j < inputNumRows; j++) {
                for (int k = 0; k < inputNumCols; k++) {
                    (*inputMatrix)(i)(j)(k) = max((*inputMatrix)(i)(j)(k));
                }
            }
        }
    }
};
