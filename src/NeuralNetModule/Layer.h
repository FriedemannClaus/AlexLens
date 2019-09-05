//
// Created by Viet Pham.
//

#ifndef ALEXLENS_LAYER_H
#define ALEXLENS_LAYER_H


#include <Eigen/Core>

typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
typedef Eigen::Matrix<Matrix, Eigen::Dynamic, 1> ThreeDMatrix;
typedef Eigen::Matrix<Matrix, Eigen::Dynamic, Eigen::Dynamic> FourDMatrix;

class Layer {
    /**
     * Abstract forward function
     *
     * @param input layer input
     * @param output layer output
     */
    virtual void forward(ThreeDMatrix &input, ThreeDMatrix &output) = 0;
};


#endif //ALEXLENS_LAYER_H
