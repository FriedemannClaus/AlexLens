//
// Created by Viet Pham.
//

#ifndef ALEXLENS_ALEXNETWEIGHTPARSER_H
#define ALEXLENS_ALEXNETWEIGHTPARSER_H


#include <Eigen/Core>
#include "H5Cpp.h"
using namespace H5;

typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
typedef Eigen::Matrix<Matrix, Eigen::Dynamic, 1> ThreeDMatrix;
typedef Eigen::Matrix<Matrix, Eigen::Dynamic, Eigen::Dynamic> FourDMatrix;

const H5std_string	FILE_NAME("../resources/alexnet-CPU/alexnet_weights.h5");
const H5std_string	CONV1_W("/conv_1/conv_1_W");
const H5std_string	CONV1_b("/conv_1/conv_1_b");
const H5std_string	CONV2_1_W("/conv_2_1/conv_2_1_W");
const H5std_string	CONV2_1_b("/conv_2_1/conv_2_1_b");
const H5std_string	CONV2_2_W("/conv_2_2/conv_2_2_W");
const H5std_string	CONV2_2_b("/conv_2_2/conv_2_2_b");
const H5std_string	CONV3_W("/conv_3/conv_3_W");
const H5std_string	CONV3_b("/conv_3/conv_3_b");
const H5std_string	CONV4_1_W("/conv_4_1/conv_4_1_W");
const H5std_string	CONV4_1_b("/conv_4_1/conv_4_1_b");
const H5std_string	CONV4_2_W("/conv_4_2/conv_4_2_W");
const H5std_string	CONV4_2_b("/conv_4_2/conv_4_2_b");
const H5std_string	CONV5_1_W("/conv_5_1/conv_5_1_W");
const H5std_string	CONV5_1_b("/conv_5_1/conv_5_1_b");
const H5std_string	CONV5_2_W("/conv_5_2/conv_5_2_W");
const H5std_string	CONV5_2_b("/conv_5_2/conv_5_2_b");
const H5std_string	DENSE1_W("/dense_1/dense_1_W");
const H5std_string	DENSE1_b("/dense_1/dense_1_b");
const H5std_string	DENSE2_W("/dense_2/dense_2_W");
const H5std_string	DENSE2_b("/dense_2/dense_2_b");
const H5std_string	DENSE3_W("/dense_3/dense_3_W");
const H5std_string	DENSE3_b("/dense_3/dense_3_b");

const int CONV1_W_NK = 96;
const int CONV1_W_NZ = 3;
const int CONV1_W_NY = 11;
const int CONV1_W_NX = 11;
const int CONV1_W_RANK_OUT = 4;
const int CONV1_b_N = 96;
const int CONV1_b_RANK_OUT = 1;

const int CONV2_1_W_NK = 128;
const int CONV2_1_W_NZ = 48;
const int CONV2_1_W_NY = 5;
const int CONV2_1_W_NX = 5;
const int CONV2_1_W_RANK_OUT = 4;
const int CONV2_1_b_N = 128;
const int CONV2_1_b_RANK_OUT = 1;

const int CONV2_2_W_NK = 128;
const int CONV2_2_W_NZ = 48;
const int CONV2_2_W_NY = 5;
const int CONV2_2_W_NX = 5;
const int CONV2_2_W_RANK_OUT = 4;
const int CONV2_2_b_N = 128;
const int CONV2_2_b_RANK_OUT = 1;

const int CONV3_W_NK = 384;
const int CONV3_W_NZ = 256;
const int CONV3_W_NY = 3;
const int CONV3_W_NX = 3;
const int CONV3_W_RANK_OUT = 4;
const int CONV3_b_N = 384;
const int CONV3_b_RANK_OUT = 1;

const int CONV4_1_W_NK = 192;
const int CONV4_1_W_NZ = 192;
const int CONV4_1_W_NY = 3;
const int CONV4_1_W_NX = 3;
const int CONV4_1_W_RANK_OUT = 4;
const int CONV4_1_b_N = 192;
const int CONV4_1_b_RANK_OUT = 1;

const int CONV4_2_W_NK = 192;
const int CONV4_2_W_NZ = 192;
const int CONV4_2_W_NY = 3;
const int CONV4_2_W_NX = 3;
const int CONV4_2_W_RANK_OUT = 4;
const int CONV4_2_b_N = 192;
const int CONV4_2_b_RANK_OUT = 1;

const int CONV5_1_W_NK = 128;
const int CONV5_1_W_NZ = 192;
const int CONV5_1_W_NY = 3;
const int CONV5_1_W_NX = 3;
const int CONV5_1_W_RANK_OUT = 4;
const int CONV5_1_b_N = 128;
const int CONV5_1_b_RANK_OUT = 1;

const int CONV5_2_W_NK = 128;
const int CONV5_2_W_NZ = 192;
const int CONV5_2_W_NY = 3;
const int CONV5_2_W_NX = 3;
const int CONV5_2_W_RANK_OUT = 4;
const int CONV5_2_b_N = 128;
const int CONV5_2_b_RANK_OUT = 1;

const int DENSE1_W_NY = 9216;
const int DENSE1_W_NX = 4096;
const int DENSE1_W_RANK_OUT = 2;
const int DENSE1_b_N = 4096;
const int DENSE1_b_RANK_OUT = 1;

const int DENSE2_W_NY = 4096;
const int DENSE2_W_NX = 4096;
const int DENSE2_W_RANK_OUT = 2;
const int DENSE2_b_N = 4096;
const int DENSE2_b_RANK_OUT = 1;

const int DENSE3_W_NY = 4096;
const int DENSE3_W_NX = 1000;
const int DENSE3_W_RANK_OUT = 2;
const int DENSE3_b_N = 1000;
const int DENSE3_b_RANK_OUT = 1;

class AlexNetWeightParser {
public:
    AlexNetWeightParser(    FourDMatrix &eigen_conv1_w, Vector &eigen_conv1_b, FourDMatrix &eigen_conv2_1_w, Vector &eigen_conv2_1_b,
                            FourDMatrix &eigen_conv2_2_w, Vector &eigen_conv2_2_b, FourDMatrix &eigen_conv3_w, Vector &eigen_conv3_b,
                            FourDMatrix &eigen_conv4_1_w, Vector &eigen_conv4_1_b, FourDMatrix &eigen_conv4_2_w, Vector &eigen_conv4_2_b,
                            FourDMatrix &eigen_conv5_1_w, Vector &eigen_conv5_1_b, FourDMatrix &eigen_conv5_2_w, Vector &eigen_conv5_2_b,
                            Matrix &eigen_dense1_w, Vector &eigen_dense1_b, Matrix &eigen_dense2_w, Vector &eigen_dense2_b, Matrix &eigen_dense3_w, Vector &eigen_dense3_b
    );
    void parse();
    void setWeights();
private:
    void initArrays();
    void initMatrices();

    float conv1_w[CONV1_W_NK][CONV1_W_NZ][CONV1_W_NY][CONV1_W_NX];
    float conv1_b[CONV1_b_N];

    float conv2_1_w[CONV2_1_W_NK][CONV2_1_W_NZ][CONV2_1_W_NY][CONV2_1_W_NX];
    float conv2_1_b[CONV2_1_b_N];

    float conv2_2_w[CONV2_2_W_NK][CONV2_2_W_NZ][CONV2_2_W_NY][CONV2_2_W_NX];
    float conv2_2_b[CONV2_2_b_N];

    float conv3_w[CONV3_W_NK][CONV3_W_NZ][CONV3_W_NY][CONV3_W_NX];
    float conv3_b[CONV3_b_N];

    float conv4_1_w[CONV4_1_W_NK][CONV4_1_W_NZ][CONV4_1_W_NY][CONV4_1_W_NX];
    float conv4_1_b[CONV4_1_b_N];

    float conv4_2_w[CONV4_2_W_NK][CONV4_2_W_NZ][CONV4_2_W_NY][CONV4_2_W_NX];
    float conv4_2_b[CONV4_2_b_N];

    float conv5_1_w[CONV5_1_W_NK][CONV5_1_W_NZ][CONV5_1_W_NY][CONV5_1_W_NX];
    float conv5_1_b[CONV5_1_b_N];

    float conv5_2_w[CONV5_2_W_NK][CONV5_2_W_NZ][CONV5_2_W_NY][CONV5_2_W_NX];
    float conv5_2_b[CONV5_2_b_N];

    float dense1_w[DENSE1_W_NY][DENSE1_W_NX];
    float dense1_b[DENSE1_b_N];

    float dense2_w[DENSE2_W_NY][DENSE2_W_NX];
    float dense2_b[DENSE2_b_N];

    float dense3_w[DENSE3_W_NY][DENSE3_W_NX];
    float dense3_b[DENSE3_b_N];

    FourDMatrix *eigen_conv1_w;
    Vector *eigen_conv1_b;

    FourDMatrix *eigen_conv2_1_w;
    Vector *eigen_conv2_1_b;

    FourDMatrix *eigen_conv2_2_w;
    Vector *eigen_conv2_2_b;

    FourDMatrix *eigen_conv3_w;
    Vector *eigen_conv3_b;

    FourDMatrix *eigen_conv4_1_w;
    Vector *eigen_conv4_1_b;

    FourDMatrix *eigen_conv4_2_w;
    Vector *eigen_conv4_2_b;

    FourDMatrix *eigen_conv5_1_w;
    Vector *eigen_conv5_1_b;

    FourDMatrix *eigen_conv5_2_w;
    Vector *eigen_conv5_2_b;

    Matrix *eigen_dense1_w;
    Vector *eigen_dense1_b;

    Matrix *eigen_dense2_w;
    Vector *eigen_dense2_b;

    Matrix *eigen_dense3_w;
    Vector *eigen_dense3_b;

};


#endif //ALEXLENS_ALEXNETWEIGHTPARSER_H
