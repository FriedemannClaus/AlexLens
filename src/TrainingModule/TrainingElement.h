/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _TRAININGELEMENT_H
#define _TRAININGELEMENT_H

class TrainingElement {
private: 
	Tensor image;
	String imageLabel;
	int labelID;
};

#endif //_TRAININGELEMENT_H