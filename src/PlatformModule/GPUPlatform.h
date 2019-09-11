//
// Created by viet on 01.09.19.
//

#ifndef SRC_GUIMODULE_ALEXLENS_GPUPLATFORM_H
#define SRC_GUIMODULE_ALEXLENS_GPUPLATFORM_H

#include "Platform.h"
#include "PlatformStatistic.h"
#include "../NeuralNetModule/AlexNet.h"

/**
 * Interface class to control the image classification on the GPU platform
 */
class GPUPlatform: public Platform {
private:
    AlexNet *alexNet; /// AlexNet architecture template
public:
    /**
     * GPUPlatform class constructor
     */
    GPUPlatform();

    /**
     * Runs image classification on the GPU platform
     */
    void runClassify() override;

    /**
     * Runs Transfer Learning on the CPU! platform with use of the Torch library
     */
    void runTraining() override;

    /**
     * Superclass method to obtain the ID of the platform
     * @return ID of the GPU platform. AlexLens works with a single GPU platform, so "" is returned
     */
    inline std::string getId() override{ return "";}
};


#endif //SRC_GUIMODULE_ALEXLENS_GPUPLATFORM_H
