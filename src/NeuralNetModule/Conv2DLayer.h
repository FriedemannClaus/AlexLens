/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _CONV2DLAYER_H
#define _CONV2DLAYER_H

#include "TrainableLayer.h"


class Conv2DLayer: public TrainableLayer {
private: 
	int STRIDE;
	int NUM_FILTERS;
	int ZERO_PADDING;
	int FILTER_SIZE;
	List<Matrix> kernels;
};

#endif //_CONV2DLAYER_H