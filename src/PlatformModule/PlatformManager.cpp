//
// Created by dmitrii on 7/21/19.
//

#include "PlatformManager.h"

PlatformManager::PlatformManager() {
    for (int i = 0; i < NUM_PLATFORMS; i++) {
        Platform *asicplatform = new ASICPlatform(i);
        platforms.push_back(asicplatform);
    }
    //Platform* cpuplatform = new CPUPlatformTorch();
    Platform *cpuplatform = new CPUPlatform();
    Platform *gpuplatform = new GPUPlatform();
    Platform *cpuplatformTorch = new CPUPlatformTorch();
    platforms.push_back(gpuplatform);
    platforms.push_back(cpuplatform);
    platforms.push_back(cpuplatformTorch);
}

list<Platform *> PlatformManager::getAvailablePlatforms() {
    list<Platform *> returnPlatforms;
    switch (mode) {
        case Mode::HIGH_PERFOMANCE:
            for (auto platform:this->platforms) {
                if (((platform->getType() == PlatformType::CPU) && (this->neuralNet == "alexnet"))
                    || ((platform->getType() == PlatformType::GPU) && (this->neuralNet == "alexnet"))
                    || ((platform->getType() == PlatformType::CPU_TORCH) && (this->neuralNet != "alexnet"))
                    || (platform->getType() == PlatformType::ASIC)) {
                    returnPlatforms.push_back(platform);
                }
            }
            return returnPlatforms;
        case Mode::LOW_POWER:
            for (auto platform:this->platforms) {
                if (platform->getType() == PlatformType::ASIC) {
                    returnPlatforms.push_back(platform);
                    return returnPlatforms;
                }
            }
        case Mode::ENERGY_EFFICIENT:
            for (auto platform:this->platforms) {
                if (platform->getType() == PlatformType::ASIC) {
                    returnPlatforms.push_back(platform);
                }
            }
            return returnPlatforms;
        case Mode::OPTIMAL:
            for (auto platform:this->platforms) {
                if (((platform->getType() == PlatformType::GPU) && (this->neuralNet == "alexnet"))
                    || ((platform->getType() == PlatformType::CPU_TORCH) && (this->neuralNet != "alexnet"))) {
                    returnPlatforms.push_back(platform);
                    return returnPlatforms;
                }
            }
        default:
            return this->platforms;

    }
}