/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _MATRIX_H
#define _MATRIX_H

#include "TensorObject.h"
#include <string>


class Matrix: public TensorObject {
private:
    double[][] values;
public:

/**
 * A constructor of a Matrix without the need to give values.
 * Constructs a Null (not zero) matrix.
 * @return void
 */
    Matrix();

/**
 * A constructor of a Matrix for given values.
 * @param values The values, the matrix shall contain. Null values are legit.
 * @return void
 */
    Matrix(double[][] values);
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

TensorObject Matrix::multiplyWith(Matrix other) throws MathException

TensorObject multiplyWith(TensorObject other) throws MathException

TensorObject multiplyWith(Skalar other) throws MathException
};

#endif //_MATRIX_H