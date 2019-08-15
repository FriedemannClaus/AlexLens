/**
* Project Entwurf_PSE_KNN
* @author Friedemann Claus
* @version 1.2
*/


#include "Conv2DLayer.h"

/**
* Conv2DLayer implementation
*/
const Layer::ThreeDMatrix& Conv2DLayer::forward(const Layer::ThreeDMatrix &input)  {
//    if (ZERO_PADDING == true) { zeroPad(input); }
//    int strides = weights.cols() / STRIDE;
//
//    foreach(Matrix<double; FILTER_SIZE; FILTER_SIZE> filter: filters) { //so foreach?
//        for(int row = 0; i <= INPUT_SIZE; row += stride) {
//            for(int col = 0; i <= INPUT_SIZE; col += stride) {
//
//            }
//        }
//    }

    return input;
}

const Layer::ThreeDMatrix& Conv2DLayer::zeroPad(const Layer::ThreeDMatrix &input) {
    int zeroPadWidth = FILTER_SIZE / 2; //div
    int sideLength = input(0).cols() + 2 * zeroPadWidth;
    static Layer::ThreeDMatrix output; // TODO, static because of returning the local variable. There should be a better way.
    output.resize(input.rows());


    int oldSideLength = input(0).cols();
    for (int depth = 0; depth < input.rows(); ++depth) {
        output(depth).resize(sideLength, sideLength);
        output(depth).setZero(); //TODO should work

        //In Eigen, iterating firstly over the columns and secondly over the rows is more efficient.
        for (int j = 0; j < oldSideLength; j++) {
            for (int i = 0; i < oldSideLength; i++) {
                output(depth)(i + zeroPadWidth, j + zeroPadWidth) = input(depth)(i, j);
            }
        }
    }
    return output;
}

void Conv2DLayer::setWeights(const Layer::FourDMatrix &weights, const Layer::Vector &bias) {
    this->weights = weights;
    this->bias = bias;
}