/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IVIEW_H
#define _IVIEW_H

class IView: public IView {
public: 
	
/**
 * @param manager
 */
static IView by(IManager manager);
	
void start();
	
List<IObservers> getObservers();
};

#endif //_IVIEW_H