/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PREPROCESSOR_H
#define _PREPROCESSOR_H

class PreProcessor {
public: 
	
/**
 * @param images
 */
List<Tensor> processImages(List<Tensor> images);
	
/**
 * @param image
 */
List<Tensor> processPreviewImages(List<Tensor> image);
};

#endif //_PREPROCESSOR_H