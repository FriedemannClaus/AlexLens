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
    std::string project_dir;
    std::string datasetPath;

public:
    CPUPlatform();
    void runClassify() override;
    void runTraining() override;
    void setImagePaths(list<string> imagePaths) override;
    vector<string> getResults() override;

    inline void setDatasetPath(std::string path) override {this->datasetPath = path;}
    inline PlatformType getType() override {return this->type;}
    inline PlatformStatistic getStatistic() override { return this->statistic;}
    inline void setNeuralNet(string neuralNet) override {}
    inline void setProjectDir(std::string dir) override {this->project_dir = dir;}

};


#endif //ALEXLENS_CPUPLATFORM_H
