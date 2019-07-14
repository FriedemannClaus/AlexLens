/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _ITRAINING_H
#define _ITRAINING_H

#include "../../src/GUIModule/Subject.h"
#include "../../src/GUIModule/IObserver.h"


class ITraining: public Subject {
public: 
	
void train();
	
void stopTraining();
	
void saveTrainedWeights();
	
void getBatchLoss();
	
void getLog();
};

#endif //_ITRAINING_H