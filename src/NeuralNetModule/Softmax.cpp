//
// Created by Viet Pham.
//

#include "Softmax.h"
#include <cmath>
#include <iostream>

void Softmax::forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) {

}

void Softmax::apply(ThreeDMatrix &input, Vector &output) {
    //resize output vector
    output.resize(1000);

    Vector exponents;
    exponents.resize(1000);

    float sumExponents = 0;
    for (int i = 0; i < 1000; i++) {
        exponents(i) = exp(input(0)(i, 0) * 2); // * 2 because of drop out in AlexNet
        sumExponents += exponents(i);
    }

    //fill in output vector
    float sumPropabilities = 0;
    for (int i = 0; i < 1000; i++) {
        output(i) = exponents(i) / sumExponents;
        sumPropabilities += output(i);
    }
    //std::cout << "SUM PROPABILITIES: " << sumPropabilities << std::endl;
}
