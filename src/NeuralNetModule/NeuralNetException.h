/**
* Project Entwurf_PSE_KNN
* @author Friedemann Claus
*/

#include <QException>

/**
 * This Exception can get thrown when a mathematically incorret Operation has been tried.
 */

#ifndef ALEXLENS_NEURALNETEXCEPTION_H
#define ALEXLENS_NEURALNETEXCEPTION_H
class NeuralNetException : public QException {
public:
    void raise() const override { throw *this; }
    NeuralNetException *clone() const override { return new NeuralNetException(*this); }
};
#endif //ALEXLENS_NEURALNETEXCEPTION_H
