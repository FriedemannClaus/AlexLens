/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IOBSERVER_H
#define _IOBSERVER_H

class Subject;

class IObserver {
public: 
	
/**
 * @param subject
 */
void invokeUpdate(Subject *subject);
};

#endif //_IOBSERVER_H