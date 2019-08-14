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
    Matrix result;

public:
    FCLayer() : Layer() {}

    const Matrix& forward(const Matrix& input) override;
    void setWeights(Matrix& weights, Vector& bias);
};


#endif //UNTITLED_FCLAYER_H
