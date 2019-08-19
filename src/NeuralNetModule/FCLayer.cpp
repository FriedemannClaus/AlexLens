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
    int neurons = weights.rows();
    int inputDepth = input.rows();
    int inputSize = input(0).rows();
    int inputSizeSquare = inputSize * inputSize;


    //Okay for now TODO
    assert(input.rows() * input(0).rows() * input(0).cols() == weights.cols());
    assert(inputSizeSquare * inputDepth == weights.cols()); // basically the same

    // FC-Layer returns a vector. Still has to be a ThreeDMatrix so that the other layers can process it.
    // But this doesn't cause a noticeable performance-decrease because of the way the loops are built.
    output.resize(neurons);
    for (int i = 0; i < neurons; ++i) {
        output(i).resize(1,1);
    }

    float neuronResult;
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
