/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _STATISTICHELPPANEL_H
#define _STATISTICHELPPANEL_H

#include "IObserver.h"


class StatisticHelpPanel: public IObserver {
public: 
	
void StatisticHelpPanel();
	
/**
 * @param invoker
 */
void register(IEventInvoker invoker);
};

#endif //_STATISTICHELPPANEL_H