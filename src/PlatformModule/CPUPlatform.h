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

    void runClassifyOne(string imagePath);
    void convertListToVector(list<string> list, vector<string> *imageNames);

public:
    CPUPlatform();
    void runClassify() override;

    inline PlatformType getType() {return this->type;}
    inline PlatformStatistic getStatistic() { return this->statistic;}
    void setImagePaths(list<string> imagePaths);
    vector<string> getResults();

};


#endif //ALEXLENS_CPUPLATFORM_H