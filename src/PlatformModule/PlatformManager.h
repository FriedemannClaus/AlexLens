/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PLATFORMMANAGER_H
#define _PLATFORMMANAGER_H

#include "IPlatformManager.h"
#include "../GUIModule/Subject.h"
#include "../GUIModule/Subject.h"
#include "../GUIModule/Subject.h"


class PlatformManager: public IPlatformManager, public Subject, public Subject, public Subject {
private: 
	Vector<Platform> platforms;
	Mode mode;
	INeuralNet neuralNet;
};

#endif //_PLATFORMMANAGER_H