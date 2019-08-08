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
void Platform::setImagePaths(std::list<std::string> imagePaths) {
}
vector<string> Platform::getResults() {}