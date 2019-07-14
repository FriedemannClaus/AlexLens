/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IPLATFORMMANAGER_H
#define _IPLATFORMMANAGER_H

class IPlatformManager {
public: 
	
/**
 * @param mode
 */
void setMode(String mode);
	
Mode getMode();
	
void stop();
	
/**
 * @param inputImage
 */
double runClassify(Tensor inputImage);
	
/**
 * @param trainingBatch
 */
List<TensorObject> runTrain(List<Tensor> trainingBatch);
	
/**
 * @param validateBatch
 */
vector<double> runValidate(List<Tensor> validateBatch);
	
/**
 * @param neuralNet
 */
void updatePlatforms(INeuralNet neuralNet);
	
List <Platform> getAvailablePlatforms();
};

#endif //_IPLATFORMMANAGER_H