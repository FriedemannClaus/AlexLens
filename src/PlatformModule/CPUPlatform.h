//
// Created by Viet Pham.
//

#ifndef ALEXLENS_CPUPLATFORM_H
#define ALEXLENS_CPUPLATFORM_H

#include "Platform.h"
#include "PlatformStatistic.h"
#include "../NeuralNetModule/AlexNet.h"

class CPUPlatform: public Platform {
private:
    AlexNet *alexNet;
public:
    CPUPlatform();
    void runClassify() override;
    void runTraining() override;
};


#endif //ALEXLENS_CPUPLATFORM_H
