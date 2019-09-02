//
// Created by viet on 01.09.19.
//

#ifndef SRC_GUIMODULE_ALEXLENS_GPUPLATFORM_H
#define SRC_GUIMODULE_ALEXLENS_GPUPLATFORM_H

#include "Platform.h"
#include "PlatformStatistic.h"
#include "../NeuralNetModule/AlexNet.h"

class GPUPlatform: public Platform {
private:
    AlexNet *alexNet;
public:
    GPUPlatform();
    void runClassify() override;
    inline std::string getId() override{ return "";}
};


#endif //SRC_GUIMODULE_ALEXLENS_GPUPLATFORM_H
