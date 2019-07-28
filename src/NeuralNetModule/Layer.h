//
// Created by dmitrii on 7/28/19.
//

#ifndef UNTITLED_LAYER_H
#define UNTITLED_LAYER_H

#include <cstdlib>
#include <Eigen/Core>
#include <vector>
using namespace Eigen;
/// Abstract class Layer. For all Layers extend this class
class Layer {
protected:
    ///Definition of Types for convenient using.
    ///To use Layer::Matrix or Layer::Vector
    typedef double Scalar;
    typedef Matrix<Scalar, Dynamic, Dynamic> Matrix_t;
    typedef Matrix<Scalar, Dynamic, 1> Vector_t;

    ///Input and Outut sizes of Layer
    ///they will be set in constructor
    /// Weight Matrix has sizes: (inputSize, outputSize)
    ///Bias (1,outputSizeSize)
    const size_t inputSize;
    const size_t outputSize;
public:
    inline size_t getInputSize() { return inputSize;}
    inline size_t getOuputSize() { return outputSize;}

    Layer(const size_t inputSize, const size_t outputSize) : inputSize(inputSize), outputSize(outputSize) {}

    /// Forward Propagation of layer
    /// \param x output of PREVIOUS Layet
    /// \return result of forward propagation r = W*x+b
    virtual const Matrix_t& forward(const Matrix_t& x);

    /// setting Weights of corresponding layer
    /// \param W Weight Matrix
    /// \param b Bias
    virtual void setWeights(Matrix_t& W, Vector_t& b);


};

#endif //UNTITLED_LAYER_H
