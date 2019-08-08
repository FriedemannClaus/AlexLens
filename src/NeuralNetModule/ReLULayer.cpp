//
// Created by viet on 08.08.19.
//

#include "ReLULayer.h"
#include "Layer.h"

const Layer::Matrix_t& ReLULayer::forward(const Layer::Matrix_t &x){
    int columns = x.cols();
    x.array() = x.array()cwiseMax(Scalar(0));
    r.resize(this->outputSize, columns);
    r.array() = x.array();
    return x;
}