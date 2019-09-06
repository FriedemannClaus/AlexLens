//
// Created by Viet Pham.
//

#ifndef ALEXLENS_SOFTMAX_H
#define ALEXLENS_SOFTMAX_H

#include "Layer.h"

/**
 * Softmax layer class is the last layer in the Neural Net, which computes probabilities of defined object classes in the image inputted to the Neural Net
 * About: https://en.wikipedia.org/wiki/Softmax_function
 */
class Softmax : public Layer {
public:
    /**
     * Function applies softmax to input
     * @param input layer input
     * @param output layer input
     */
    void apply(ThreeDMatrix &input, Vector &output);

    /**
     * Empty virtual method override
     */
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;

};


#endif //ALEXLENS_SOFTMAX_H
