//
// Created by dmitrii on 11.07.19.
//

#include "Manager.h"


Manager::Manager() {
    setDefaultModes();
    setDefaultNeuralNets();
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
