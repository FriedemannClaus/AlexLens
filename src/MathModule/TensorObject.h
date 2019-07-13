/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TENSOROBJECT_H
#define _TENSOROBJECT_H

class TensorObject {
public: 
	
virtual int getDimensions() = 0;
	
virtual void transpose() = 0;
	
virtual boolean isTransposed() = 0;
	
/**
 * @param tensorObject
 */
virtual TensorObject multiplyWith(TensorObject tensorObject) = 0;
	
/**
 * @param tensorObject
 */
virtual TensorObject addTo(TensorObject tensorObject) = 0;
};

#endif //_TENSOROBJECT_H