//
// Created by Viet Pham.
//

#ifndef ALEXLENS_FC_H
#define ALEXLENS_FC_H


#include "Layer.h"

class FC: public Layer {
private:
    const int NEURONS;
    const Matrix WEIGHTS;
    const Vector BIAS;
    const bool GPU_MODE;
    void flaten(ThreeDMatrix &inputMatrix, Vector &convertedVector);
public:
    FC(int neurons, Matrix &weights, Vector &bias, bool gpuMode):
            NEURONS(neurons),
            WEIGHTS(weights),
            BIAS(bias),
            GPU_MODE(gpuMode)
    {}
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_FC_H
