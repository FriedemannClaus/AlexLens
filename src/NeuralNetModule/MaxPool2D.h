//
// Created by Viet Pham.
//

#ifndef ALEXLENS_MAXPOOL2D_H
#define ALEXLENS_MAXPOOL2D_H


#include "Layer.h"


class MaxPool2D: public Layer {
private:
    const int poolNumRows;
    const int poolNumCols;
    const int stride;
    float getMaxFloat(Vector *floats);
public:
    MaxPool2D(const int poolWidth, const int poolHeight, const int poolStride):
            poolNumRows(poolHeight),
            poolNumCols(poolWidth),
            stride(poolStride)
    {}
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_MAXPOOL2D_H
