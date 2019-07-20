//
// Created by dmitrii on 11.07.19.
//

#include "Manager.h"
#include "Executor.h"


Manager::Manager(Subject* subject) {
    setDefaultModes();
    setDefaultNeuralNets();
    this->subject = subject;
    Executor* executor = new Executor();
    this->executor = executor;
}

void Manager::setDefaultModes() {
    list<string> mods = ModeUtil::getAllModes();
    this->defaultModes = mods;
}

void Manager::setDefaultNeuralNets() {
    list<string> nets;
    nets.push_front("AlexNet");
    this->defaultNeuralNets = nets;
}

void Manager::runClassify() {
    this->results = executor->classify(imagePaths, operationMode, neuralNet);
    for (auto a: results) cout << a << endl;
    this->subject->informObservers();

}
