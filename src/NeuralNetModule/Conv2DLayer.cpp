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
//    int zeroPadWidth = FILTER_SIZE / 2; //div
//    int sideLength = input.cols() + 2 * zeroPadWidth;
//    Matrix output = Layer::Matrix::Zero();
//    output.resize(sideLength);
//
//
//    //In Eigen, iterating firstly over the columns and then over the rows is more efficient.
//    for (int j = 0; j < input.cols(); j++) {
//        for (int i = 0; i < input.row(); i++) {
//            output(i + zeroPadWidth, j + zeroPadWidth) = input(i, j);
//        }
//    }
//    input = output;
      return input;
}

void Conv2DLayer::setWeights(const Layer::FourDMatrix &weights, const Layer::Vector &bias) {
    this->weights = weights;
    this->bias = bias;
}