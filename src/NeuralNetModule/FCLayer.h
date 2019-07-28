//
// Created by dmitrii on 7/28/19.
//

#ifndef UNTITLED_FCLAYER_H
#define UNTITLED_FCLAYER_H

#include "Layer.h"

class FCLayer : public Layer {
private:
    /*
     * Weight Matrix
     */
    Matrix_t W;
    /*
     * Bias vector
     */
    Vector_t b;
    /*
     * Result of forward propagation
     */
    Matrix_t r;

public:
    FCLayer(const size_t inputSize, const size_t outputSize) : Layer(inputSize, outputSize) {}

    const Matrix_t& forward(const Matrix_t& x) override;
    void setWeights(Matrix_t& W, Vector_t& b) override;

};


#endif //UNTITLED_FCLAYER_H
