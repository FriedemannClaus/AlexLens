//
// Created by Viet Pham.
//

#ifndef ALEXLENS_FC_H
#define ALEXLENS_FC_H


#include "Layer.h"
#include "GPUSGeMM.h"

class FC: public Layer {
private:
    const int NEURONS;
    const Matrix WEIGHTS;
    const Vector BIAS;
    const bool GPU_MODE;
    void flaten(ThreeDMatrix &inputMatrix, Vector &convertedVector);
    void convertToEigen(float *floatArray, Vector &memResult);
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
