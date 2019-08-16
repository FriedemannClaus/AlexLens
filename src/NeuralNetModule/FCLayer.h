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
    FCLayer(Layer::FourDMatrix &weights, Layer::Vector &bias);

    void forward(const Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output) override;
    void setWeights(const Matrix& weights, const Vector& bias);
};


#endif //UNTITLED_FCLAYER_H
