//
// Created by Viet Pham.
//

#ifndef ALEXLENS_MAXPOOL2D_H
#define ALEXLENS_MAXPOOL2D_H


#include "Layer.h"

/**
 * Layer used to reduce spatial dimensions of the input between convolutional layers with use of pooling technique
 */
class MaxPool2D: public Layer {
private:
    const int poolNumRows; ///Height of the pooling "window"
    const int poolNumCols; ///Width of the pooling "window"
    const int stride; ///Stride of the pooling "window"
    float getMaxFloat(Vector *floats); ///Get the max value from the pooling "window"
public:
    /**
     * MaxPool2D class constructor
     *
     * @param poolWidth Width of the pooling "window"
     * @param poolHeight Height of the pooling "window"
     * @param poolStride Stride of the pooling "window"
     */
    MaxPool2D(const int poolWidth, const int poolHeight, const int poolStride):
            poolNumRows(poolHeight),
            poolNumCols(poolWidth),
            stride(poolStride)
    {}
    /**
     * Function performs pooling on the layer input
     *
     * @param inputMatrix layer input
     * @param outputMatrix layer output
     */
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_MAXPOOL2D_H
