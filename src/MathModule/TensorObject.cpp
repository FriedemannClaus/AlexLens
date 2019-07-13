/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#include "TensorObject.h"

/**
 * TensorObject implementation
 */


/**
 * @return int
 */
virtual int TensorObject::getDimensions() {
    return 0;
}

/**
 * @return void
 */
virtual void TensorObject::transpose() {
    return;
}

/**
 * @return boolean
 */
virtual boolean TensorObject::isTransposed() {
    return false;
}

/**
 * @param tensorObject
 * @return TensorObject
 */
virtual TensorObject TensorObject::multiplyWith(TensorObject tensorObject) {
    return null;
}

/**
 * @param tensorObject
 * @return TensorObject
 */
virtual TensorObject TensorObject::addTo(TensorObject tensorObject) {
    return null;
}