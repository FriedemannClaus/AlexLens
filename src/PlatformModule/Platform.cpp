//
// Created by dmitrii on 7/18/19.
//

#include "Platform.h"
void Platform::runClassify() {
    std::cout << "base virtual mathods" << std::endl;
}

PlatformStatistic Platform::getStatistic() {
    return PlatformStatistic();
}

PlatformType Platform::getType() {
    return PlatformType();
}

string Platform::getId() {
    return "";
}

void Platform::setImagePaths(std::list<std::string> imagePaths) {
}
vector<string> Platform::getResults() {}

void Platform::runTraining() {
    std::cout << "base virtual mathods" << std::endl;
}

void Platform::setNeuralNet(string neuralNet) {
    std::cout << "base virtual mathods" << std::endl;
}

void Platform::setDatasetPath(string path) {
    std::cout << "base virtual mathods" << std::endl;
}

void Platform::setProjectDir(string dir) {

}
