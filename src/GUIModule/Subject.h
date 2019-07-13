/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _SUBJECT_H
#define _SUBJECT_H

#include <QList>

class IObserver;

class Subject {
public: 
	
/**
 * @param observer
 */
void attachObserver(IObserver *observer);
	
void informObservers();
	
/**
 * @param observer
 */
void detachObserver(IObserver *observer);
private: 
	QList<IObserver> observerList;
};

#endif //_SUBJECT_H