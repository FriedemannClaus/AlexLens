//
// Created by dmitrii on 7/21/19.
//

#ifndef ALEXLENS_CPUPLATFORMTORCH_H
#define ALEXLENS_CPUPLATFORMTORCH_H


#include "Platform.h"
#include "PlatformStatistic.h"
#include <string>
#include <list>
#include <ctime>
#include <time.h>
using namespace std;

/**
 * This class implements CPU platform, that is using the library Torch
 */
class CPUPlatformTorch : public Platform {
public:
    /**
     * The standard constructor
     */
    CPUPlatformTorch();
    void runClassify() override;
    inline void setNeuralNet(string neuralNet) override;
    inline std::string getId() override {return "";}
};


#endif //ALEXLENS_CPUPLATFORMTORCH_H