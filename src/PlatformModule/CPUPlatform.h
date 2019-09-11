//
// Created by Viet Pham.
//

#ifndef ALEXLENS_CPUPLATFORM_H
#define ALEXLENS_CPUPLATFORM_H

#include "Platform.h"
#include "PlatformStatistic.h"
#include "../NeuralNetModule/AlexNet.h"

/**
 * Interface class to control the image classification on the CPU platform
 */
class CPUPlatform: public Platform {
private:
    AlexNet *alexNet; /// AlexNet architecture template
public:
    /**
     * CPUPlatform class constructor
     */
    CPUPlatform();

    /**
     * Runs image classification on the CPU platform
     */
    void runClassify() override;

    /**
     * Superclass method to obtain the ID of the platform
     * @return ID of the CPU platform. AlexLens works with a single CPU platform, so "" is returned
     */
    inline std::string getId() override{ return "";}
};


#endif //ALEXLENS_CPUPLATFORM_H
