/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _FCLAYER_H
#define _FCLAYER_H

#include "TrainableLayer.h"
#include "TrainableLayer.h"


class FCLayer: public TrainableLayer, public TrainableLayer {
private: 
	int LAYER_SIZE;
	double dropout;
};

#endif //_FCLAYER_H