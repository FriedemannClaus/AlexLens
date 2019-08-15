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
    /**
     * Result of forward propagation
     */
    ThreeDMatrix result;

public:
//    FCLayer() : Layer() {}

    const ThreeDMatrix& forward(const ThreeDMatrix& input) override;
    void setWeights(const Matrix& weights, const Vector& bias);
};


#endif //UNTITLED_FCLAYER_H
