/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _OUTPUTTRAININGPANEL_H
#define _OUTPUTTRAININGPANEL_H

#include "IObserver.h"


class OutputTrainingPanel: public IObserver {
public: 
	
void OutputTrainingPanel();
	
/**
 * @param invoker
 */
void register(IEventInvoker invoker);
};

#endif //_OUTPUTTRAININGPANEL_H