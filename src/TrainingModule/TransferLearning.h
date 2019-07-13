/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TRANSFERLEARNING_H
#define _TRANSFERLEARNING_H

#include "LearningRule.h"


class TransferLearning: public LearningRule {
private: 
	vector<double> trainingScope;
};

#endif //_TRANSFERLEARNING_H