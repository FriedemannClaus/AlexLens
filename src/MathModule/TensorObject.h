/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TENSOROBJECT_H
#define _TENSOROBJECT_H
#include <qsharedpointer.h>
#include <memory>
#include <iostream>

class TensorObject {
public: 
	
virtual int getDimensions() = 0;
	
virtual void transpose() = 0;
	
virtual bool isTransposed() = 0;
	
/**
 * @param tensorObject
 */
virtual std::shared_ptr<TensorObject> multiplyWith(std::shared_ptr<TensorObject> tensorObject) = 0;
	
/**
 * @param tensorObject
 */
virtual std::shared_ptr<TensorObject> addTo(std::shared_ptr<TensorObject> tensorObject) = 0;
};

#endif //_TENSOROBJECT_H