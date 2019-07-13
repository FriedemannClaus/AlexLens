//
// Created by dmitrii on 11.07.19.
//

#include "../../includes/ManagerModule/Manager.h"


Manager::Manager() {
    setDefaultModes();
    setDefaultNeuralNets();
}

void Manager::setDefaultModes() {
    list<string> mods;
    mods.push_front("Optimal");
    mods.push_front("Hohe Perfomance");
    mods.push_front("Geringer Leistungsverbrauch");
    mods.push_front("Hohe Energieeffizienz");
    this->defaultModes = mods;
}

void Manager::setDefaultNeuralNets() {
    list<string> nets;
    nets.push_front("AlexNet");
    this->defaultNeuralNets = nets;
}
