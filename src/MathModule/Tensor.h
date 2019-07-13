/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TENSOR_H
#define _TENSOR_H

#include "TensorObject.h"


class Tensor: public TensorObject {
public: 
	
/**
 * @param values
 */
void Tensor(double values);
	
/**
 * @param x
 * @param y
 * @param z
 */
double getValue(int x, int y, int z);
	
/**
 * @param x
 * @param y
 * @param z
 * @param value
 */
void setValue(int x, int y, int z, double value);
	
int getNumRow();
	
int getNumCol();
	
int getDepth();
};

#endif //_TENSOR_H