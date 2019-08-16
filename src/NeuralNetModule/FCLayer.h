/**
 * Project Entwurf_PSE_KNN
 * @author Dima Seletkov, Friedemann Claus
 * @version 1.2
 */

#ifndef UNTITLED_FCLAYER_H
#define UNTITLED_FCLAYER_H

#include "Layer.h"

class FCLayer : public Layer {
private:
    /**
     * Weight Matrix
     */
    Matrix weights;
    /**
     * Bias vector
     */
    Vector bias;

public:
    /**
    * Constructor
    * @param weights The weights of the FC-Layer
    * @param bias The bias of the FC-Layer
    */
    FCLayer(Matrix &weights, Vector &bias);

    /**
    * The forward-propagation-function
    * @param input The 3D-Input-Matrix
    * @param output The 3D-Output-Matrix
    */
    void forward(Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output) override;

    /**
    * A setter-method for the weights
    * @param weights the new weights of the FC-Layer
    * @param bias the new bias of the FC-Layer
    */
    void setWeights(const Matrix& weights, const Vector& bias);
};


#endif //UNTITLED_FCLAYER_H
