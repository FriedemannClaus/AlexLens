/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _NEURALNET_H
#define _NEURALNET_H

#include "NeuralNetModule/INeuralNet.h"
#include "NeuralNetModule/INeuralNet.h"
#include "Layer.h"
#include "Conv2DLayer.h"
#include "FCLayer.h"
#include "MaxPool2D.h"
#include "NormLayer.h"
#include "ReLULayer.h"


class NeuralNet: public INeuralNet {
private: 
//    Eigen::Matrix<Conv2DLayer* , Eigen::Dynamic, 1> convLayers;
//    Eigen::Matrix<FCLayer* , Eigen::Dynamic, 1> fcLayers;
//    Eigen::Matrix<MaxPool2D* , Eigen::Dynamic, 1> maxPoolLayers;
//    Eigen::Matrix<NormLayer* , Eigen::Dynamic, 1> normLayers;

    Eigen::Matrix<Layer*, Eigen::Dynamic, 1> layers;


public:
    void init();
    Layer::Vector& classify(Layer::ThreeDMatrix &picture);
};

#endif //_NEURALNET_H