/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _MATRIX_H
#define _MATRIX_H

#include "TensorObject.h"


class Matrix: public TensorObject {
public: 
	
/**
 * @param values
 */
void Matrix(double values);
	
/**
 * @param x
 * @param y
 */
double getValue(int x, int y);
	
/**
 * @param x
 * @param y
 * @param value
 */
void setValue(int x, int y, double value);
	
int getNumRow();
	
int getNumCol();
};

#endif //_MATRIX_H