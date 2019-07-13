/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _POOLLAYER_H
#define _POOLLAYER_H

#include "Layer.h"


class PoolLayer: public Layer {
private: 
	int STRIDE;
	int POOL_SIZE;
	int ZERO_PADDING;
};

#endif //_POOLLAYER_H