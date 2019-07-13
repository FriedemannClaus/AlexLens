/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "../GUIModule/Subject.h"
#include "../GUIModule/Subject.h"


class Interpreter: public Subject, public Subject {
public: 
	
/**
 * @param result
 * @param picture
 */
void interpretResult(Vektor result, Tensor picture);
	
Map<Map<String;double>; Tensor> getResults();
private: 
	List<String> objectClasses;
	Map<Map<String;double>; Tensor> results;
};

#endif //_INTERPRETER_H