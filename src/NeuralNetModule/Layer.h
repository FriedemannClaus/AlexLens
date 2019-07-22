/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _LAYER_H
#define _LAYER_H

#include "Shape.h"

class Layer {
public: 
	
/**
 * @param input
 */
virtual std::shared_ptr<TensorObject> forwardPropagate(std::shared_ptr<TensorObject> input) = 0;
	
/**
 * @param backPropInterimResult
 */
virtual std::shared_ptr<TensorObject> backPropagate(std::shared_ptr<TensorObject> backPropInterimResult) = 0;
private: 
	Shape inputShape;
	Shape outputShape;
	std::shared_ptr<Layer> nextLayer;
    std::shared_ptr<Layer> previousLayer;
};

#endif //_LAYER_H