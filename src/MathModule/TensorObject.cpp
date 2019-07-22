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
virtual bool TensorObject::isTransposed() {
    return false;
}

/**
 * Virtual/abstract method to multiply a TensorObject to the TensorObject form the right side.
 * @param tensorObject the TensorObject to multiply with the TensorObject.
 * @return TensorObject the result.
 */
virtual std::shared_ptr<TensorObject> TensorObject::multiplyWith(TensorObject other) {
}

/**
 * @param tensorObject
 * @return TensorObject
 */
virtual std::shared_ptr<TensorObject> TensorObject::addTo(TensorObject tensorObject) {
    return null;
}