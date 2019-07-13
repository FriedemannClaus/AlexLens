/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#include "../GUIModule/Subject.h"


class Executor: public Subject {
public: 
	
/**
 * @param images
 * @param mode
 */
void classify(List<Tensor> images, Mode mode);
	
/**
 * @param trainingSet
 * @param mode
 */
void train(Map trainingSet, Mode mode);
	
void stop();
private: 
	Interpreter interpreter;
	INeuralNet neuralNet;
	ITraining learningRule;
	IPlatformManager platformManager;
};

#endif //_EXECUTOR_H