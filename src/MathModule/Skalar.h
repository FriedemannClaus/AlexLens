/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _SKALAR_H
#define _SKALAR_H

#include "TensorObject.h"


class Skalar: public TensorObject {
public:
    double getValue();
    void setValue(double value);
    std::shared_ptr<TensorObject> multiplyWith(std::shared_ptr<TensorObject> tensorObject);
    std::shared_ptr<TensorObject> addTo(std::shared_ptr<TensorObject> tensorObject);
    int getDimensions();
    void transpose();
    bool isTransposed();
private:
    double value;
    const int dimension;
};

#endif //_SKALAR_H