//
// Created by dmitrii on 11.07.19.
//

#ifndef ALEXLENS_MANAGER_H
#define ALEXLENS_MANAGER_H

#include <list>
#include <iterator>
#include <string>
#include "../../includes/PlatformModule/Mode.h"

using namespace std;


class Manager{
private:
    list<string> defaultModes;
    list<string> defaultNeuralNets;
    Mode operationMode;
    list<string>* imagePaths;
public:
    Manager();

    inline void addImage(string imagePath) {this->imagePaths->push_front(imagePath);};

    inline void setMode(Mode mode) {operationMode = mode;};

    inline list<string> getDefaultModes() {return defaultModes;};

    inline list<string> getDeafaultNeuralNets() {return defaultNeuralNets;};

private:
    void setDefaultModes();
    void setDefaultNeuralNets();
};


#endif //ALEXLENS_MANAGER_H
