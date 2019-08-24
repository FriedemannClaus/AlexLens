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

class CPUPlatformTorch : public Platform {
private:
    PlatformType type;
    PlatformStatistic statistic;
    vector<string> imageNames;
    vector<string> results;
    std::string model_path;
    std::string label_path;
    std::string datasetPath;
    std::string project_dir;

    void runClassifyOne(string imagePath);
    void convertListToVector(list<string> list, vector<string> *imageNames);

    inline void setNeuralNet(string neuralNet) override {
        this->model_path = this->project_dir + "resources/" + neuralNet + "/";
        this->model_path += neuralNet + "_model" + ".pt";
        this->label_path = this->project_dir + "resources/" + neuralNet + "/";
        this->label_path += neuralNet + "_labels" + ".txt";
    }

public:
    CPUPlatformTorch();
    void runClassify() override;
    void runTraining() override;

    inline PlatformType getType() override {return this->type;}
    inline PlatformStatistic getStatistic() override { return this->statistic;}
    inline void setDatasetPath(std::string path) override {this->datasetPath = path;}
    inline void setProjectDir(std::string dir) override {this->project_dir = dir;}

    void setImagePaths(list<string> imagePaths) override;
    vector<string> getResults() override;


};


#endif //ALEXLENS_CPUPLATFORMTORCH_H