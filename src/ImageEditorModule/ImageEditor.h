/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _IMAGEEDITOR_H
#define _IMAGEEDITOR_H

#include "ImageEditorModule/IImageEditor.h"
#include "ImageEditorModule/IImageEditor.h"
#include "ImageEditorModule/IImageEditor.h"


class ImageEditor: public IImageEditor, public IImageEditor, public IImageEditor {
public: 
	
/**
 * @param input
 * @param params
 */
TensorObject executeOperation(TensorObject input, Params params);
	
/**
 * @param operation
 */
ImageOperation getOperation(String operation);
private: 
	ImageOperation imageOperation;
};

#endif //_IMAGEEDITOR_H