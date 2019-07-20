//
// Created by dmitrii on 7/18/19.
//

#include <GUIModule/Subject.h>
#include "Executor.h"
#include "../PlatformModule/Platform.h"
#include "../PlatformModule/ASICPlatform.h"

vector<string> Executor::classify(list<string> imagePaths, Mode mode, string neuralNet) {

    Platform* asicplatform = new ASICPlatform;

    vector<string> results = asicplatform->runClassify(imagePaths);

    return results;

}
Executor::Executor() {}