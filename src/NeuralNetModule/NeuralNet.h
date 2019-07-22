/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _NEURALNET_H
#define _NEURALNET_H

#include "INeuralNet.h"



class NeuralNet: public INeuralNet {
public:
    NeuralNet(std::string modelPath);
private: 
	QList<std::shared_ptr<Layer>> layers;
};

#endif //_NEURALNET_H