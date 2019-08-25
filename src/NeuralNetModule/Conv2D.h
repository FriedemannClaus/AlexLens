//
// Created by Viet Pham.
//

#ifndef ALEXLENS_CONV2D_H
#define ALEXLENS_CONV2D_H


#include "Layer.h"

class Conv2D: public Layer {
private:
    const int NUM_KERNELS;
    const int KERNEL_SIZE;
    const int STRIDE;
    const int PAD;
    const FourDMatrix WEIGHTS;
    const Vector BIAS;
    void zeroPadding(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix);
    void image2col(ThreeDMatrix &inputMatrix, Matrix &convertedMatrix);
    void weights2row(Matrix &convertedWeights);
    void reshape(Matrix &resultMatrix, ThreeDMatrix *outputMatrix);
    void addBias(ThreeDMatrix *outputMatrix);
public:
    Conv2D(int numKernels, int kernelSize, int kernelStride, int padding, FourDMatrix &weights, Vector &bias):
            NUM_KERNELS(numKernels),
            KERNEL_SIZE(kernelSize),
            STRIDE(kernelStride),
            PAD(padding),
            WEIGHTS(weights),
            BIAS(bias)
    {}
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_CONV2D_H
