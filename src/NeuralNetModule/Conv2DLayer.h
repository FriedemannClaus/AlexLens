/**
 * Project Entwurf_PSE_KNN
 * @author Friedemann Claus
 */


#ifndef _CONV2DLAYER_H
#define _CONV2DLAYER_H

#include "Layer.h"

class Conv2DLayer: public Layer {
private:
    int STRIDE;
    bool ZERO_PADDING;
    /**
     * Weight Matrix
     */
    FourDMatrix weights;
    /**
     * Bias vector
     */
    Vector bias;

public:
    Conv2DLayer(int stride, bool ZeroPadding, FourDMatrix& weights, Vector& bias);

    void forward(const ThreeDMatrix &input, ThreeDMatrix &output) override;
    void setWeights(const FourDMatrix& weights, const Vector& bias);

private:
    void zeroPad(const Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output);
};

#endif //_CONV2DLAYER_H