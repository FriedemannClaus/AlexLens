//
// Created by dmitrii on 7/18/19.
//

#include "Platform.h"
void Platform::runClassify() {
    std::cout << "base virtual mathod runClassify" << std::endl;
}

void Platform::runTraining() {
    std::cout << "base virtual mathod runTraining" << std::endl;
}



void Platform::convertListToVector(list<string> list, vector<string> *imageNames) {
    for(string i : list) {
        imageNames->push_back(i);
    }
}
