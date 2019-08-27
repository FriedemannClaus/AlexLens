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
    int inputSize = input(0).rows();

    output.resize(inputSize);

    Vector exponents;
    exponents.resize(inputSize);

    float sumExponents = 0;
    for (int i = 0; i < inputSize; i++) {
        exponents(i) = exp(input(0)(i, 0) * 2); // * 2 because of drop out in AlexNet
        sumExponents += exponents(i);
    }

    //fill in output vector
    float sumPropabilities = 0;
    for (int i = 0; i < inputSize; i++) {
        output(i) = exponents(i) / sumExponents;
        sumPropabilities += output(i);
    }
    //std::cout << "SUM PROPABILITIES: " << sumPropabilities << std::endl;
}
