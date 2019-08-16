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
    /**
    * Constructor
     * @param stride The stride of the Conv-Layer
    * @param ZeroPadding Whether Zero-Padding shall be used
    * @param weights The weights of the Conv-Layer
    * @param bias The bias of the Conv-Layer
    */
    Conv2DLayer(int stride, bool ZeroPadding, FourDMatrix& weights, Vector& bias);

    /**
    * The forward-propagation-function
    * @param input The 3D-Input-Matrix
     * @param output The 3D-Output-Matrix
    */
    void forward(ThreeDMatrix &input, ThreeDMatrix &output) override;

    /**
    * A setter-method for the weights
    * @param weights the new weights of the Conv-Layer
    * @param bias the new bias of the Conv-Layer
    */
    void setWeights(const FourDMatrix& weights, const Vector& bias);

private:

    /**
    * The zero-padding-function
    * @param input The 3D-Input-Matrix to be padded
    * @param output The 3D-Output-Matrix
    */
    void zeroPad(const Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output);
};

#endif //_CONV2DLAYER_H