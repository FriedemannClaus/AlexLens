/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PLATFORM_H
#define _PLATFORM_H

class Platform {
public: 
	
virtual void runClassify() = 0;
private: 
	PlatformStatistic platformStatistic;
	PlatformType platformType;
};

#endif //_PLATFORM_H