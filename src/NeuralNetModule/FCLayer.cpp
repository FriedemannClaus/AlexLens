/**
 * Project Entwurf_PSE_KNN
 * @author Friedemann Claus
 */

#include "FCLayer.h"


FCLayer::FCLayer(Matrix &weights, Vector &bias) :
        weights(weights),
        bias(bias)
{}

void FCLayer::forward(Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output) {
//    Vector vectorizedInput = input(i) mit for-schleife input zu Vektor machen. Oder nicht vectorizen
//    und per for-schleife weight-Matrix mit ThreeD-Input-Matrix multiplizieren.
//    int columns = input.cols();
    // Linear term result = weights^T * input + bias
    // Or: Vector result = weights * vectorized Input + bias
    // Because other Layers need a ThreeDMatrix as input for the forward-pass
//    result.resize(bias.rows(), columns);
//    result.noalias() = weights.transpose() * input;
//    result.colwise() += this->bias;

    int neurons = weights.rows();
    int inputDepth = input.rows();
    int inputSize = input(0).rows();
    int inputSizeSquare = inputSize * inputSize;

    int neuronResult;
    // FC-Layer returns a vector. Still has to be a ThreeDMatrix so that the other layers can process it.
    // But this doesn't cause a noticeable performance-decrease because of the way the loops are built.
    output.resize(neurons);
    for (int i = 0; i < neurons; ++i) {
        output(i).resize(1,1);
    }

    //options are: one transformationlayer after conv5. Would need another Relulayer afterwards and threeDLayers twoDLayers attributes in NN.cpp
    // TransformationLayer would need one RAM-Copy
    //2. like now: Index-Calculations in the calculation-> slower (bc CPU-Calculations, RAM shouldnt be the bottleneck here)

    //calculate the output
    for (int neuron = 0; neuron < neurons; ++neuron) {
        neuronResult = 0;;
        for (int depth = 0; depth < inputDepth; ++depth) {
            for (int j = 0; j < inputSize; ++j) {
                for (int i = 0; i < inputSize; ++i) {
                    neuronResult += weights(neuron, i + (j * inputSize) + (depth * inputSizeSquare)) * input(depth) (i, j);
                }
            }
        }
        output(neuron)(0, 0) = neuronResult + bias(neuron);
    }
}

void FCLayer::setWeights(const Layer::Matrix &weights, const Layer::Vector &bias) {
    this->weights = weights;
    this->bias = bias;
}
