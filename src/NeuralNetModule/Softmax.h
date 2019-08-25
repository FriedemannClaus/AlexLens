//
// Created by Viet Pham.
//

#ifndef ALEXLENS_SOFTMAX_H
#define ALEXLENS_SOFTMAX_H


#include "Layer.h"

class Softmax: public Layer {
public:
    void apply(ThreeDMatrix &input, Vector &output);
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;

};


#endif //ALEXLENS_SOFTMAX_H
