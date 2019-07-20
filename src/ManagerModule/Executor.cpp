//
// Created by dmitrii on 7/18/19.
//

#include <GUIModule/Subject.h>
#include "Executor.h"
#include "../PlatformModule/Platform.h"
//#include "../PlatformModule/ASICPlatform.h"

vector<string> Executor::classify(list<string> imagePaths, Mode mode, string neuralNet) {

    //Platform* asicplatform = new ASICPlatform;

    //vector<string> results = asicplatform->runClassify(imagePaths);

    vector<string> results = {"cat 0.9999 \n dog 0.01111 \n shark 0.0001 \n penguin 0.001 \n monkey 0.000 "};

    return results;

}
Executor::Executor() {}