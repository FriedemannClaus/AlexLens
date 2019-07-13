/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IIMAGEEDITOR_H
#define _IIMAGEEDITOR_H

class IImageEditor {
public: 
	
/**
 * @param operationType
 * @param input
 * @param params
 */
TensorObject editImage(String operationType, TensorObject input, Params params);
};

#endif //_IIMAGEEDITOR_H