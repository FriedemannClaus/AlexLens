/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#include "Skalar.h"

/**
 * Skalar implementation
 */
double Skalar::getValue() {
    return this->value;
}

void Skalar::setValue(double value) {
    this->value = value;
}
int Skalar::getDimensions(){
    return this->dimension;
}
void Skalar::transpose(){
    //do nothing
}
bool Skalar::isTransposed() {
    return false;
}

std::shared_ptr<TensorObject> Skalar::multiplyWith(std::shared_ptr<TensorObject> tensorObject) {

    return nullptr;
}

std::shared_ptr<TensorObject> Skalar::addTo(std::shared_ptr<TensorObject> tensorObject) {

    return nullptr;
}

