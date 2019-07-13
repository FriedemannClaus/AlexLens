/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PLATFORMSTATISTIC_H
#define _PLATFORMSTATISTIC_H

class PlatformStatistic {
public: 
	
double getFLOPS();
	
double getEnergyConsum();
	
PlatformType getName();
	
int getTime();
};

#endif //_PLATFORMSTATISTIC_H