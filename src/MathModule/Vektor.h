/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _VEKTOR_H
#define _VEKTOR_H

#include "TensorObject.h"


class Vektor: public TensorObject {
public: 
	
/**
 * @param values
 */
void Vektor(vector<double> values);
	
/**
 * @param index
 */
double getValue(int index);
	
/**
 * @param index
 * @param value
 */
void setValue(int index, double value);
	
int getLength();
};

#endif //_VEKTOR_H