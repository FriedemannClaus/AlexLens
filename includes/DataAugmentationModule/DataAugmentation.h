/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _DATAAUGMENTATION_H
#define _DATAAUGMENTATION_H

class DataAugmentation {
public: 
	
/**
 * @param input
 */
static List<Tensor> fiveCrop(Tensor input);
	
/**
 * @param input
 */
static List<Tensor> randomCrop(Tensor input);
	
/**
 * @param input
 * @param axis
 */
static Tensor mirror(Tensor input, boolean axis);
	
/**
 * @param input
 */
static List<Tensor> fiveCropAndMirror(Tensor input);
};

#endif //_DATAAUGMENTATION_H