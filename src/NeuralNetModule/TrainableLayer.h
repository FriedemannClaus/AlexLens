/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TRAINABLELAYER_H
#define _TRAINABLELAYER_H

#include "Layer.h"


class TrainableLayer: public Layer {
public: 
	
/**
 * @param weights
 */
void setWeights(TensorObject weights);
	
TensorObject getWeights();
private: 
	boolean USE_BIAS;
	double LEARNING_RATE;
	TensorObject weights;
	TensorObject forwardPropagationCache;
	TensorObject backPropagationResult;
};

#endif //_TRAINABLELAYER_H