/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _HANDLER_H
#define _HANDLER_H

class Handler {
public: 
	
virtual void run() = 0;
private: 
	IView frame;
	IEventInvoker invoker;
	IManager manager;
};

#endif //_HANDLER_H