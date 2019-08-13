/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#include "PlatformStatistic.h"

/**
 * PlatformStatistic implementation
 */


/**
 * @return double
 */
double PlatformStatistic::getFLOPS() {
    return this->flops;
}

/**
 * @return double
 */
double PlatformStatistic::getEnergyConsum() {
    return this->energyConsum;
}

double PlatformStatistic::getTotalInferenceTime() {
    return this->totalInferenceTime;
}

void PlatformStatistic::setTotalInferenceTime(double time) {
    this->totalInferenceTime = time;
}

double PlatformStatistic::getThroughput() {
    return this->throughput;
}

void PlatformStatistic::setThroughput(double throughput) {
    this->throughput = throughput;
}

double PlatformStatistic::getAvgIterationTime() {
    return this->avgIterationTime;
}

void PlatformStatistic::setAvgIterationTime(double avgIterationTime) {
    this->avgIterationTime = avgIterationTime;
}