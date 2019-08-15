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
    ThreeDMatrix result;

public:
//    Conv2DLayer() : Layer() {}
    const ThreeDMatrix& forward(const ThreeDMatrix& input) override;
    void setWeights(const FourDMatrix& weights, const Vector& bias);

private:
    const ThreeDMatrix& zeroPad(const ThreeDMatrix& input);
};

#endif //_CONV2DLAYER_H