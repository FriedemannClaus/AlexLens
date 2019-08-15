//
// Created by dmitrii on 7/21/19.
//

#ifndef ALEXLENS_PLATFORMMANAGER_H
#define ALEXLENS_PLATFORMMANAGER_H

#include <iostream>
#include <list>
#include "Platform.h"
#include "Mode.h"
#include "ASICPlatform.h"
#include "CPUPlatform.h"

using namespace std;

class PlatformManager {
private:
    const static int NUM_PLATFORMS = 1;
    list<Platform*> platforms;
    Mode mode;
    string neuralNet;
public:
    PlatformManager();
    list<Platform *> getAvailablePlatforms();
    inline void setMode(Mode mode) {this->mode = mode;}
    inline void setNeuralNet(string neuralNet) {this->neuralNet = neuralNet;}
};


#endif //ALEXLENS_PLATFORMMANAGER_H