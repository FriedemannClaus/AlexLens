//
// Created by Viet Pham.
//

#ifndef ALEXLENS_NORMALIZATION_H
#define ALEXLENS_NORMALIZATION_H


#include "Layer.h"

class Normalization: public Layer {
private:
    const int kNorm;
    const float alpha;
    const float beta;
    const int n;

    int max(int a, int b);
    int min(int a, int b);
public:
    Normalization(const int normK, const float normAlpha, const float normBeta, const int normRegionSize):
    // Initialisierungsliste
            kNorm(normK),
            alpha(normAlpha),
            beta(normBeta),
            n(normRegionSize)
    {}

    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_NORMALIZATION_H
