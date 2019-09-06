//
// Created by Viet Pham.
//

#ifndef ALEXLENS_CONV2D_H
#define ALEXLENS_CONV2D_H

#include "Layer.h"

/**
 * Class handles convolution computation
 */
class Conv2D: public Layer {
private:
    const int NUM_KERNELS; ///Number of kernels in the layer
    const int KERNEL_SIZE; ///Spatial size of the kernel "window"
    const int STRIDE; ///Stride of the kernel
    const int PAD; ///Width of the zero-padding of the input
    const FourDMatrix WEIGHTS; ///Layer weights
    const Vector BIAS; ///Layer biases
    const bool GPU_MODE; ///Operation mode
    void zeroPadding(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix); ///Zero-padding of the input
    void image2col(ThreeDMatrix &inputMatrix, Matrix &convertedMatrix); ///Conversion of 3D matrices to 2D matrices
    void weights2row(Matrix &convertedWeights); ///Conversion of 4D tensors to 2D matrices
    void reshape(Matrix &resultMatrix, ThreeDMatrix *outputMatrix); ///Conversion of the 2D matrix multiplication result to 3D matrix layer output
    void addBias(ThreeDMatrix *outputMatrix); ///Adding bias to the calculated result
public:
    /**
     * Conv2D class constructor
     *
     * @param numKernels number of kernels
     * @param kernelSize spatial size of the kernel "window"
     * @param kernelStride stride of the kernel
     * @param padding width of the zero-padding
     * @param weights layer weights
     * @param bias layer biases
     * @param gpuMode operation mode true if GPU computation, false if CPU computation
     */
    Conv2D(int numKernels, int kernelSize, int kernelStride, int padding, FourDMatrix &weights, Vector &bias, bool gpuMode):
            NUM_KERNELS(numKernels),
            KERNEL_SIZE(kernelSize),
            STRIDE(kernelStride),
            PAD(padding),
            WEIGHTS(weights),
            BIAS(bias),
            GPU_MODE(gpuMode)
    {}
    /**
     * Function calculating layer output
     *
     * @param inputMatrix layer input
     * @param outputMatrix layer output
     */
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_CONV2D_H
