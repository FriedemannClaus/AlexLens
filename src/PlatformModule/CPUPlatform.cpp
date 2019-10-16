//
// Created by Viet Pham.
//

#include "CPUPlatform.h"
#include <Python.h>
#include <sys/time.h>

CPUPlatform::CPUPlatform() {
    this->alexNet = new AlexNet(this->results, false);
    this->type = PlatformType::CPU;
    this->statistic.setEnergyConsum(20);
    this->statistic.setFLOPS(90);
}


void CPUPlatform::runClassify() {
    this->results.clear();

    struct timespec begin, finish;
    clock_gettime(CLOCK_MONOTONIC, &begin);
    alexNet->runClassify(this->imageNames);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    const float final_time = (finish.tv_sec - begin.tv_sec) + (finish.tv_nsec - begin.tv_nsec) / 1000000.0;
    this->imageNames.clear();
    this->statistic.setTotalInferenceTime(final_time);
    this->statistic.setAvgIterationTime(final_time/results.size());
}

