/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IMAGEOPERATION_H
#define _IMAGEOPERATION_H

class ImageOperation {
public: 
	
/**
 * @param input
 * @param params
 */
virtual TensorObject execute(TensorObject input, Params params) = 0;
};

#endif //_IMAGEOPERATION_H