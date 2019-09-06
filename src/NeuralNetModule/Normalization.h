//
// Created by Viet Pham.
//

#ifndef ALEXLENS_NORMALIZATION_H
#define ALEXLENS_NORMALIZATION_H

#include "Layer.h"

/**
 * Layer performing inter-channel local response normalization(LRN) after convolutional layers
 * About LRN and its hyperparameters:
 * https://towardsdatascience.com/difference-between-local-response-normalization-and-batch-normalization-272308c034ac
 */
class Normalization: public Layer {
private:
    const int kNorm;
    const float alpha;
    const float beta;
    const int n;

    int max(int a, int b); ///Returns max(a,b)
    int min(int a, int b); ///Returns min(a,b)
public:
    /**
     * Normalization class constructor
     *
     * @param normK k hyperparameter
     * @param normAlpha alpha hyperparameter
     * @param normBeta beta hyperparameter
     * @param normRegionSize region size hyperparameter
     */
    Normalization(const int normK, const float normAlpha, const float normBeta, const int normRegionSize):
            kNorm(normK),
            alpha(normAlpha),
            beta(normBeta),
            n(normRegionSize)
    {}

    /**
     * Functions normalizes layer input
     *
     * @param inputMatrix layer input
     * @param outputMatrix layer output
     */
    void forward(ThreeDMatrix &inputMatrix, ThreeDMatrix &outputMatrix) override;
};


#endif //ALEXLENS_NORMALIZATION_H
