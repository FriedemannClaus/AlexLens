/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IMANAGER_H
#define _IMANAGER_H

class IManager {
public: 
	
void runClassify();
	
void runTrain();
	
void stop();
	
/**
 * @param image
 */
void addImage(Tensor image);
	
/**
 * @param trainingSet
 */
void addTrainingSet(Map<String, Tensor> trainingSet);
	
/**
 * @param mode
 */
void setMode(Mode mode);
	
/**
 * @param NNConfPath
 */
void setClassificationNN(String NNConfPath);
	
/**
 * @param NNConfPath
 */
void setTrainingNN(String NNConfPath);
	
List <INeuralNetwork> getAvailableNNs();
};

#endif //_IMANAGER_H