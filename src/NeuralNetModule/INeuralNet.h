/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _INEURALNET_H
#define _INEURALNET_H

#include <QList>
#include "../MathModule/TensorObject.h"
#include "Layer.h"

class INeuralNet {
public:

/**
 * @param weights
 */
    void setWeights(QList<TensorObject> weights);

    QList<std::shared_ptr<TensorObject>> getWeights();

    QList<Layer> getLayers();
};


#endif //_INEURALNET_H