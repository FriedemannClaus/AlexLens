/**
 * Project Entwurf_PSE_KNN
 * @author Friedemann Claus, Dima Seletkov
 * @version 1.2
 */

#ifndef UNTITLED_LAYER_H
#define UNTITLED_LAYER_H

#include <cstdlib>
#include <Eigen/Core>
#include <vector>
/// Abstract class Layer. For all Layers extend this class
class Layer {
protected:
    ///Definition of Types for convenient usage.
    ///To use Layer::Matrix or Layer::Vector
    typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, 1> ThreeDMatrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, Eigen::Dynamic> FourDMatrix;

public:

    // separate non-virtual setweights-Function, because weights can be different (FourDMatrix or just a (2D-) Matrix)
    // and some Layers don't even have weights.
//    Layer() : {}

    /// Forward Propagation of layer. Pure virtual because layers have to implement this.
    /// \param input output of PREVIOUS Layer
    /// \return result of forward propagation
    virtual const ThreeDMatrix& forward(const ThreeDMatrix& input) = 0;


};

#endif //UNTITLED_LAYER_H
