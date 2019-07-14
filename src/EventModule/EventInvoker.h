/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _EVENTINVOKER_H
#define _EVENTINVOKER_H

#include "EventModule/IEventInvoker.h"
#include "EventModule/IEventInvoker.h"


class EventInvoker: public IEventInvoker, public IEventInvoker {
private: 
	Map eventsAndHandlerMap;
	IManager manager;
	IView frame;
};

#endif //_EVENTINVOKER_H