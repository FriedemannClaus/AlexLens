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

    /**
     * Runs image classification on the CPU platform with the use of the Torch library
     */
    void runClassify() override;

    /**
     * Sets the Neural Net to run the classification on
     * @param neuralNet name of the Neural Net architecture
     */
    inline void setNeuralNet(string neuralNet) override;

    /**
    * Superclass method to obtain the ID of the platform
    * @return ID of the CPU platform. AlexLens works with a single CPU platform, so "" is returned
    */
    inline std::string getId() override {return "";}
};


#endif //ALEXLENS_CPUPLATFORMTORCH_H