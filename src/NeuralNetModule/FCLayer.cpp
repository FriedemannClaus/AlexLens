/**
 * Project Entwurf_PSE_KNN
 * @author Friedemann Claus, Dima Seletkov
 */

#include "FCLayer.h"

/**
 * Constructor
 * @param weights The weights of the Conv-Layer
 * @param bias The bias of the Conv-Layer
 */
FCLayer::FCLayer(Layer::FourDMatrix &weights, Layer::Vector &bias) :
        weights(weights),
        bias(bias)
{}

void FCLayer::forward(const Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output) {
//    Vector vectorizedInput = input(i) mit for-schleife input zu Vektor machen. Oder nicht vectorizen
//    und per for-schleife weight-Matrix mit ThreeD-Input-Matrix multiplizieren.
//    int columns = input.cols();
    // Linear term result = weights^T * input + bias
    // Or: Vector result = weights * vectorized Input + bias
    // Because other Layers need a ThreeDMatrix as input for the forward-pass
//    result.resize(bias.rows(), columns);
//    result.noalias() = weights.transpose() * input;
//    result.colwise() += this->bias;
}

void FCLayer::setWeights(const Layer::Matrix &weights, const Layer::Vector &bias) {
//    this->weights.resize(inputSize, outputSize);
//    this->bias.resize(outputSize);
    this->weights = weights;
    this->bias = bias;
}
