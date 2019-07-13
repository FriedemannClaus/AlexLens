/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _LAYER_H
#define _LAYER_H

class Layer {
public: 
	
/**
 * @param input
 */
virtual TensorObject forwardPropagate(TensorObject input) = 0;
	
/**
 * @param backPropInterimResult
 */
virtual TensorObject backPropagate(TensorObject backPropInterimResult) = 0;
private: 
	Shape inputShape;
	Shape outputShape;
	Layer nextLayer;
	Layer previousLayer;
};

#endif //_LAYER_H