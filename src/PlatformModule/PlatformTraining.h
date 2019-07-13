/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PLATFORMTRAINING_H
#define _PLATFORMTRAINING_H

#include "Platform.h"
#include "OpenCL.h"


class PlatformTraining: public Platform, protected OpenCL {
public: 
	
virtual void runTrainForward() = 0;
	
virtual void runTrainBackward() = 0;
};

#endif //_PLATFORMTRAINING_H