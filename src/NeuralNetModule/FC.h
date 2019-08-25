//
// Created by viet on 25.08.19.
//

#ifndef ALEXLENS_FC_H
#define ALEXLENS_FC_H


#include "Layer.h"

class FC: public Layer {
private:
    const int NEURONS;
    const Matrix WEIGHTS;
    const Vector BIAS;
    void flaten(ThreeDMatrix &inputMatrix, Vector &convertedVector);
public:
    FC(int neurons, Matrix &weights, Vector &bias):
            NEURONS(neurons),
            WEIGHTS(weights),
            BIAS(bias)
    {}
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_FC_H
