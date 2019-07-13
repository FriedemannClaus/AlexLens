/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IEVENTINVOKER_H
#define _IEVENTINVOKER_H

class IEventInvoker {
public: 
	
/**
 * @param manager
 * @param view
 */
static IEventInvoker by(IManager manager, IView view);
	
/**
 * @param event
 */
void handleEvent(Events event);
};

#endif //_IEVENTINVOKER_H