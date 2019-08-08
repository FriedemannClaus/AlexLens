/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PLATFORMSTATISTIC_H
#define _PLATFORMSTATISTIC_H

#include "PlatformType.h"

class PlatformStatistic {
public:
    double getFLOPS();
    double getEnergyConsum();
    PlatformType getName();
    double getTotalInferenceTime();
    void setTotalInferenceTime(double time);

    double getThroughput();
    void setThroughput(double throughput);

    double getAvgIterationTime();
    void setAvgIterationTime(double avgIterationTime);

private:
    double totalInferenceTime;
    double throughput;
    double avgIterationTime;
};

#endif //_PLATFORMSTATISTIC_H