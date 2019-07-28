//
// Created by dmitrii on 7/28/19.
//

#include "FCLayer.h"
#include "Layer.h"

const Layer::Matrix_t& FCLayer::forward(const Layer::Matrix_t &x) {
    int columns = x.cols();
    // Linear term r = W^T * x + b
    r.resize(this->outputSize, columns);
    r.noalias() = W.transpose() * x;
    r.colwise() += this->b;
    return x;
}

void FCLayer::setWeights(Layer::Matrix_t &W, Layer::Vector_t &b) {
    this->W.resize(inputSize, outputSize);
    this->b.resize(outputSize);
    this->W = W;
    this->b = b;
}
