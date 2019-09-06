//
// Created by Viet Pham.
//

#ifndef ALEXLENS_RELU_H
#define ALEXLENS_RELU_H

#include "Layer.h"

/**
 * Rectified Linear Unit layer class. Computes activations of the layer it succeeds
 */
class ReLU: public Layer {
private:
    float max(float a); ///Returns max(0,a)

public:
    /**
     * Function computes layer activations
     *
     * @param inputMatrix layer input
     * @param outputMatrix layer output
     */
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};

#endif //ALEXLENS_RELU_H
