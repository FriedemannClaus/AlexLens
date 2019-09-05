//
// Created by dmitrii on 7/21/19.
//

#include "PlatformManager.h"
#include <libusb-1.0/libusb.h>

PlatformManager::PlatformManager() {
    // discover devices
    int num_sticks = 0;
    string idProduct = to_string(8528);
    string idProduct2 = to_string(9349);
    string idVendor = to_string(999);
    libusb_context *context = NULL;
    libusb_device **list = NULL;
    int rc = 0;
    ssize_t count = 0;

    rc = libusb_init(&context);
    assert(rc == 0);

    count = libusb_get_device_list(context, &list);
    assert(count > 0);

    for (size_t idx = 0; idx < count; ++idx) {
        libusb_device *device = list[idx];
        libusb_device_descriptor desc = {0};

        rc = libusb_get_device_descriptor(device, &desc);
        assert(rc == 0);
        if ((to_string(desc.idVendor) == idVendor && to_string(desc.idProduct) == idProduct) ||
            (to_string(desc.idVendor) == idVendor && to_string(desc.idProduct) == idProduct2))
            num_sticks++;
    }
    NUM_PLATFORMS = num_sticks;
    libusb_free_device_list(list, count);
    libusb_exit(context);

    for (int i = 0; i < NUM_PLATFORMS; i++) {
        Platform *asicplatform = new ASICPlatform(i);
        platforms.push_back(asicplatform);
    }

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