/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _OUTPUTCLASSIFYPANEL_H
#define _OUTPUTCLASSIFYPANEL_H

#include "IObserver.h"


class OutputClassifyPanel: public IObserver {
public: 
	
void OutputClassifyPanel();
	
/**
 * @param invoker
 */
void register(IEventInvoker invoker);
};

#endif //_OUTPUTCLASSIFYPANEL_H