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
    PlatformType type;
    PlatformStatistic statistic;
    vector<string> imagePaths;
    vector<string> results;

public:
    CPUPlatform();
    void runClassify() override;
    void setImagePaths(list<string> imagePaths) override;
    vector<string> getResults() override;

    inline PlatformType getType() override {return this->type;}
    inline PlatformStatistic getStatistic() override { return this->statistic;}
    inline void setNeuralNet(string neuralNet) override {}
};


#endif //ALEXLENS_CPUPLATFORM_H
