//
// Created by Viet Pham.
//

#include "CPUPlatform.h"
#include <Python.h>

CPUPlatform::CPUPlatform() {
    this->alexNet = new AlexNet(this->results, false);
    this->type = PlatformType::CPU;
    this->statistic.setEnergyConsum(20);
    this->statistic.setFLOPS(90);
}


void CPUPlatform::runClassify() {
    this->results.clear();
    const clock_t begin_time = clock();
    alexNet->runClassify(this->imageNames);
    const float final_time = float( clock () - begin_time )/CLOCKS_PER_SEC*1000;
    this->imageNames.clear();
    this->statistic.setTotalInferenceTime(final_time);
    this->statistic.setAvgIterationTime(final_time/results.size());
}

