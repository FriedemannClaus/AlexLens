/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PARAMETERPANEL_H
#define _PARAMETERPANEL_H

#include "IObserver.h"


class ParameterPanel: public IObserver {
public: 
	
void ParameterPanel();
	
/**
 * @param invoker
 */
void register(IEventInvoker invoker);
};

#endif //_PARAMETERPANEL_H