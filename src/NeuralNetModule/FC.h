//
// Created by Viet Pham.
//

#ifndef ALEXLENS_FC_H
#define ALEXLENS_FC_H

#include "Layer.h"
#include "GPUSGeMM.h"

class FC: public Layer {
private:
    const int NEURONS; ///Number of neurons of the layer
    const Matrix WEIGHTS; ///Layer weights
    const Vector BIAS; ///Layer biases
    const bool GPU_MODE; ///Operation mode
    void flaten(ThreeDMatrix &inputMatrix, Vector &convertedVector); ///Flatten 3D input into 1D vector
public:
    /**
     * FC class constructor
     *
     * @param neurons number of neurons
     * @param weights weight matrix
     * @param bias bias vector
     * @param gpuMode operation mode true if GPU computation, false if CPU computation
     */
    FC(int neurons, Matrix &weights, Vector &bias, bool gpuMode):
            NEURONS(neurons),
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

#endif //ALEXLENS_FC_H
