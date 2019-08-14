/**
 * Project Entwurf_PSE_KNN
 * @author Friedemann Claus
 * @version 1.2
 */


#ifndef _CONV2DLAYER_H
#define _CONV2DLAYER_H

#include "Layer.h"

class Conv2DLayer: public Layer {
private:
    int STRIDE;
    int NUM_FILTERS;
    bool ZERO_PADDING;
    int FILTER_SIZE;
    /**
     * Weight Matrix
     */
    FourDMatrix weights;
    /**
     * Bias vector
     */
    Vector bias;
    /**
     * Result of forward propagation
     */
    Matrix result;

public:
    Conv2DLayer() : Layer() {}
    const Matrix& forward(const Matrix& input) override;
    void setWeights(FourDMatrix& weights, Vector& bias);

private:
    const Matrix& zeroPad(const Matrix& input);
};

#endif //_CONV2DLAYER_H