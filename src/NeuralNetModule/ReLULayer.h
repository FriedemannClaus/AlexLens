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
    float max(float a) {
        return ((a > 0) ? a : 0);
    }

public:
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override {
        int inputNumRows = inputMatrix(0).rows();
        int inputNumCols = inputMatrix(0).cols();
        int inputNumChannels = inputMatrix.rows();

        //outputMatrix.resize

        for (int i = 0; i < inputNumChannels; i++) {
            for (int j = 0; j < inputNumRows; j++) {
                for (int k = 0; k < inputNumCols; k++) {
                    inputMatrix(i)(j, k) = max(inputMatrix(i)(j, k));
                }
            }
        }
        outputMatrix = inputMatrix;
    }
};
