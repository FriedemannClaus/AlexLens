//
// Created by viet on 01.09.19.
//

#include "GPUPlatform.h"

GPUPlatform::GPUPlatform() {
    this->alexNet = new AlexNet(this->results, true);
    this->type = PlatformType::GPU;
    this->statistic.setEnergyConsum(20);
    this->statistic.setFLOPS(19);
}

void GPUPlatform::runClassify() {
    this->results.clear();
    const clock_t begin_time = clock();
    alexNet->runClassify(this->imageNames);
    const float final_time = float( clock () - begin_time )/CLOCKS_PER_SEC*100; // not * 1000?!
    this->imageNames.clear();
    this->statistic.setTotalInferenceTime(final_time);
    this->statistic.setAvgIterationTime(final_time/results.size());
}
