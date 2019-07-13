/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _LEARNINGRULE_H
#define _LEARNINGRULE_H

#include "ITraining.h"
#include "ITraining.h"


class LearningRule: public ITraining, public ITraining {
private: 
	INeuralNet neuralNet;
	IPlatformManager platformManager;
	IDataAugmentation dataAugmentation;
	Map<String;Tensor> rawTrainingSet;
	int batchSize;
	vector<double> dropout;
	Training trainingSubSet;
	Validation validationSubSet;
	Test testSubSet;
};

#endif //_LEARNINGRULE_H