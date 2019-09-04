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
    const bool GPU_MODE;
    void zeroPadding(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix);
    void image2col(ThreeDMatrix &inputMatrix, Matrix &convertedMatrix);
    void weights2row(Matrix &convertedWeights);
    void reshape(Matrix &resultMatrix, ThreeDMatrix *outputMatrix);
    void addBias(ThreeDMatrix *outputMatrix);
    void convertToEigen(float *floatArray, Matrix &multResult);
public:
    Conv2D(int numKernels, int kernelSize, int kernelStride, int padding, FourDMatrix &weights, Vector &bias, bool gpuMode):
            NUM_KERNELS(numKernels),
            KERNEL_SIZE(kernelSize),
            STRIDE(kernelStride),
            PAD(padding),
            WEIGHTS(weights),
            BIAS(bias),
            GPU_MODE(gpuMode)
    {}
    Conv2D(int numKernels, int kernelSize, int kernelStride, int padding, FourDMatrix &weights, Vector &bias,float* X_):
            NUM_KERNELS(numKernels),
            KERNEL_SIZE(kernelSize),
            STRIDE(kernelStride),
            PAD(padding),
            WEIGHTS(weights),
            BIAS(bias),
            GPU_MODE(true)
    {}
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;


};


#endif //ALEXLENS_CONV2D_H
