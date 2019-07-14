/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TENSOR_H
#define _TENSOR_H

#include "TensorObject.h"

template <class T>
class Tensor: public TensorObject {
public: 
	
/**
 * @param values
 */
void Tensor(T[][][] values);
	
/**
 * @param x
 * @param y
 * @param z
 */
T getValue(int x, int y, int z);
	
/**
 * @param x
 * @param y
 * @param z
 * @param value
 */
void setValue(int x, int y, int z, T value);
	
int getNumRow();
	
int getNumCol();
	
int getDepth();

private:
    T[][][] values;
};

#endif //_TENSOR_H