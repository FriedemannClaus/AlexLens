//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_PLATFORM_H
#define ALEXLENS_PLATFORM_H

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "PlatformType.h"
#include "PlatformStatistic.h"

using namespace std;

class Platform {
private:
    string model_path;
    string label_path;
public:
    virtual void runClassify();
    virtual void runTraining();
    virtual PlatformType getType();
    virtual PlatformStatistic getStatistic();
    virtual void setImagePaths(std::list<std::string> imagePaths);
    virtual vector<string> getResults();
    virtual void setNeuralNet(string neuralNet);
};


#endif //ALEXLENS_PLATFORM_H