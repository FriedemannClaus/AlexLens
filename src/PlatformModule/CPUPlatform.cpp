//
// Created by Viet Pham.
//

#include "CPUPlatform.h"

CPUPlatform::CPUPlatform() {
    this->alexNet = new AlexNet(this->results);
    this->type = PlatformType::CPU;
    this->statistic.setEnergyConsum(20);
    this->statistic.setFLOPS(19);
}

void CPUPlatform::setImagePaths(list<string> images) {
    this->imagePaths.clear();
    for (string i : images) {
        this->imagePaths.push_back(i);
    }
}

vector<string> CPUPlatform::getResults() {
    return this->results;
}

void CPUPlatform::runClassify() {
    this->results.clear();
    alexNet->runClassify(this->imagePaths);
}
