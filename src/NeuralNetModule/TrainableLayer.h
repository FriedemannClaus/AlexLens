// Class is not useful

///**
// * Project Entwurf_PSE_KNN
// * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
// * @version 1.2
// */
//
//
//#ifndef _TRAINABLELAYER_H
//#define _TRAINABLELAYER_H
//
//#include "Layer.h"
//
//
//class TrainableLayer: public Layer {
//public:
//
///**
// * @param weights
// */
//void setWeights(TensorObject weights);
//
//TensorObject getWeights();
//private:
//	boolean USE_BIAS;
//	double LEARNING_RATE;
//	TensorObject weights;
//	TensorObject forwardPropagationCache;
//	TensorObject backPropagationResult;
//};
//
//#endif //_TRAINABLELAYER_H


//Alternativ:
///**
// * Project Entwurf_PSE_KNN
// * @author Friedemann Claus
// * @version 1.2
// */
//
//
//#ifndef _TRAINABLELAYER_H
//#define _TRAINABLELAYER_H
//
//#include "Layer.h"
//
//
//class TrainableLayer: public Layer {
//
//protected:
//    /*
//     * Weight Matrix
//     */
//    Matrix W;
//    /*
//     * Bias vector
//     */
//    Vector b;
//    /*
//     * Result of forward propagation
//     */
//    Matrix r;
//
//  // boolean USE_BIAS; for future training
//  // double LEARNING_RATE; for future training
//
//public:
//    /// setting Weights of corresponding layer
//    /// \param W Weight Matrix
//    /// \param b Bias
//    TrainableLayer(const size_t inputSize, const size_t outputSize) : Layer(inputSize, outputSize) {}
//    virtual void setWeights(Matrix& W, Vector& b) = 0;
//};
//
//#endif //_TRAINABLELAYER_H