/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _NEURALNET_H
#define _NEURALNET_H

#include "INeuralNet.h"
#include "INeuralNet.h"


class NeuralNet: public INeuralNet, public INeuralNet {
private: 
	List<Layer> layers;
};

#endif //_NEURALNET_H