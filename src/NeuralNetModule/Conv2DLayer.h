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
    int ZERO_PAD_WIDTH;
    int FORCED_INPUT_SIZE;
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
    * @param forcedInputSize The Size the Input shall have. The depth of the input is implicitly forced
     *       through the 4D-weights-Matrix (the depth of the kernels).
    * @param stride The stride of the Conv-Layer
    * @param ZeroPadding Whether Zero-Padding shall be used
    * @param weights The weights of the Conv-Layer
    * @param bias The bias of the Conv-Layer
    */
    Conv2DLayer(int forcedInputSize, int stride, int zeroPadWidth, FourDMatrix& weights, Vector& bias);

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
    * The zero-padding-function.
    * @param input The 3D-Input-Matrix to be padded
    * @param output The 3D-Output-Matrix
    * @param zeroPadWidth The desired width of the zero-border. 0 is not valid.
    */
    void zeroPad(const Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output, int zeroPadWidth);
};

#endif //_CONV2DLAYER_H