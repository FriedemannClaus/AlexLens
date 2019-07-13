/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _INPUTPANEL_H
#define _INPUTPANEL_H

#include "IObserver.h"
#include "IObserver.h"


class InputPanel: public IObserver, public IObserver {
public: 
	
void InputPanel();
	
/**
 * @param invoker
 */
void register(IEventInvoker invoker);
private: 
	List<QImage> previewImages;
};

#endif //_INPUTPANEL_H