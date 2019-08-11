//
// Created by dmitrii on 7/21/19.
//

#ifndef ALEXLENS_CPUPLATFORM_H
#define ALEXLENS_CPUPLATFORM_H


#include "Platform.h"
#include "PlatformStatistic.h"
#include <string>
#include <list>
using namespace std;

class CPUPlatform : public Platform {
private:
    PlatformType type;
    PlatformStatistic statistic;
    vector<string> imageNames;
    vector<string> results;
    std::string model_path;
    std::string label_path;
    std::string datasetPath;

    void runClassifyOne(string imagePath);
    void convertListToVector(list<string> list, vector<string> *imageNames);

    inline void setNeuralNet(string neuralNet) override{
        this->model_path = "/home/dmitrii/AlexLens/resources/" + neuralNet + "/";
        this->model_path +=neuralNet + "_model" + ".pt";
        this->label_path = "/home/dmitrii/AlexLens/resources/" + neuralNet + "/";
        this->label_path +=neuralNet + "_labels" + ".txt";
    }

public:
    CPUPlatform();
    void runClassify() override;
    void runTraining() override;

    inline PlatformType getType() {return this->type;}
    inline PlatformStatistic getStatistic() { return this->statistic;}
    inline void setDatasetPath(std::string path) override {this->datasetPath = path;}

    void setImagePaths(list<string> imagePaths);
    vector<string> getResults();


};


#endif //ALEXLENS_CPUPLATFORM_H