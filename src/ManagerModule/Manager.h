//
// Created by dmitrii on 11.07.19.
//

#ifndef ALEXLENS_MANAGER_H
#define ALEXLENS_MANAGER_H

#include <list>
#include <iterator>
#include <string>
#include <GUIModule/Subject.h>
#include "../PlatformModule/Mode.h"
#include "../PlatformModule/ModeUtil.h"
#include "Executor.h"

using namespace std;


class Manager{
private:
    list<string> defaultModesClassify;
    list<string> defaultModesTraining;
    list<string> defaultNeuralNets;
    Mode operationMode;
    string neuralNet;
    list<string> imagePaths;
    Executor* executor;
    Subject* subject;
    vector<string> results;

public:
    Manager(Subject* subject);

    inline void addImage(string imagePath) {this->imagePaths.push_front(imagePath);}

    inline void setMode(Mode mode) {operationMode = mode;}

    inline void setNeuralNet(string neuralNet) {this->neuralNet = neuralNet;}

    inline string getNeuralNet() {return this->neuralNet;}

    inline list<string> getDefaultModesClassify() {return defaultModesClassify;}

    inline list<string> getDefaultModesTraining() {return defaultModesTraining;}

    inline list<string> getDeafaultNeuralNets() {return defaultNeuralNets;}

    inline Executor* getExecutor() { return this->executor;}

    inline Subject* getSubject() { return  this->subject;}

    inline vector<string> getResults() { return this->results;}

    inline void clearImagePaths() {this->imagePaths.clear();}

    inline void addNeuralNet(string newNN) {this->defaultNeuralNets.push_back(newNN);}

    void runClassify();

    void runTraining();

private:
    void setDefaultModesClassify();
    void setDefaultModesTraining();
    void setDefaultNeuralNets();

    list<string> findNeuralNets();
};


#endif //ALEXLENS_MANAGER_H