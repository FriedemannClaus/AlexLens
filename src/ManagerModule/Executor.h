//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_EXECUTOR_H
#define ALEXLENS_EXECUTOR_H

#include <string>
#include <list>
#include <iostream>
#include <vector>

#include "../PlatformModule/Mode.h"
#include <GUIModule/Subject.h>
#include <PlatformModule/PlatformManager.h>
#include "../PlatformModule/Platform.h"
#include "../PlatformModule/ASICPlatform.h"

using namespace std;


class Executor {
private:
    PlatformManager* platformManager;

public:
    list<string> imagePaths;

    //inline Subject* getSubject() { return this->subject;}

    Executor();

    vector<string> classify(list<string> imagePaths, Mode mode, string neuralNet, string project_dir);
    void train (string dirPath, Mode mode, string neuralNet, string project_dir);
    inline PlatformManager* getPlatformManager() {return this->platformManager;}

};


#endif //ALEXLENS_EXECUTOR_H