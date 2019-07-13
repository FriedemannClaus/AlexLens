/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _MATH_H
#define _MATH_H

class Math final  {
public: 
	
/**
 * @param input
 */
static TensorObject reLU(TensorObject input);
	
/**
 * @param params
 */
static TensorObject gradientDescent(List<TensorObject> params);
};

#endif //_MATH_H