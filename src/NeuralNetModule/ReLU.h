//
// Created by Viet Pham.
//

#ifndef ALEXLENS_RELU_H
#define ALEXLENS_RELU_H


#include "Layer.h"

class ReLU: public Layer {
private:
    float max(float a);

public:
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_RELU_H
