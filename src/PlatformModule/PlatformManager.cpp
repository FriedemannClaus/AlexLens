//
// Created by dmitrii on 7/21/19.
//

#include "PlatformManager.h"

PlatformManager::PlatformManager() {
    for (int i = 0; i < NUM_PLATFORMS; i++) {
        Platform* asicplatform = new ASICPlatform(i);
        platforms.push_back(asicplatform);
    }
    Platform* cpuplatform = new CPUPlatformTorch();
    platforms.push_back(cpuplatform);
}

list<Platform *> PlatformManager::getAvailablePlatforms() {
    list<Platform*> returnPlatforms;
    switch(mode) {
        case Mode::HIGH_PERFOMANCE:
            return this->platforms;
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
                if (platform->getType() == PlatformType::CPU) {
                    returnPlatforms.push_back(platform);
                    return returnPlatforms;
                }
            }
        default:
            return this->platforms;

    }
}