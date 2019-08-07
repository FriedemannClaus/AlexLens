//
// Created by dmitrii on 7/18/19.
//

#include "../../includes/GUIModule/Subject.h"
#include "../NeuralNetModule/NeuralNet.h"
#include "Executor.h"
#include "../PlatformModule/Platform.h"
//#include "../PlatformModule/ASICPlatform.h"

vector<string> Executor::classify(list<string> imagePaths, Mode mode, string neuralNetPath) {

    NeuralNet *neuralNet1 = new NeuralNet(neuralNetPath);
    //Platform* asicplatform = new ASICPlatform;

    //vector<string> results = asicplatform->runClassify(imagePaths);

    vector<string> results = {"cat 0.9999 \n dog 0.01111 \n shark 0.0001 \n penguin 0.001 \n monkey 0.000 "};

    return results;

}
void Executor::train(list<string> trainPaths, Mode mode, string neuralNet) {

}
Executor::Executor() {}
