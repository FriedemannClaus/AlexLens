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
public:
    ///Definition of Types for convenient usage.
    ///To use Layer::Matrix or Layer::Vector
    typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, 1> ThreeDMatrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, Eigen::Dynamic> FourDMatrix;

/**
 * The forward-propagation-function. Pure virtual because layers have to implement this.
 * @param input The 3D-Input-Matrix
 * @param output The 3D-Output-Matrix
 */
    virtual void forward(const ThreeDMatrix &input, ThreeDMatrix &output) = 0;


};

#endif //UNTITLED_LAYER_H
