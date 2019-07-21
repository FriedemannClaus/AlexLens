//
// Created by Friedemann on 18.07.2019.
//

#ifndef ALEXLENS_MATHEXCEPTION_H
#define ALEXLENS_MATHEXCEPTION_H


#include "QException.h"

/**
 * This Exception can get thrown when a mathematically incorret Operation has been tried.
 */
class MathException: public QException {
public:
    void raise() const override { throw *this; }
    MathException *clone() const override { return new MathException(*this); }
};

#endif //MATHEXCEPTION_H
