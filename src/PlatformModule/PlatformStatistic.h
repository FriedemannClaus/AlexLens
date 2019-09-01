/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#ifndef _PLATFORMSTATISTIC_H
#define _PLATFORMSTATISTIC_H

#include "PlatformType.h"
/**

 * Class PlatformStatistic aggregates all Statistics for platform
 */
class PlatformStatistic {
public:
    double getFLOPS();
    inline void setFLOPS(int flops) {this->flops = flops;}

    double getEnergyConsum();
    inline void setEnergyConsum(int energyConsum) {this->energyConsum = energyConsum;}

    double getTotalInferenceTime();
    void setTotalInferenceTime(double time);

    double getThroughput();
    void setThroughput(double throughput);

    double getAvgIterationTime();
    void setAvgIterationTime(double avgIterationTime);

private:
    double totalInferenceTime = 0.0;
    double throughput = 0.0;
    double avgIterationTime = 0.0;
    double flops = 0.0;
    double energyConsum = 0.0;
};

#endif //_PLATFORMSTATISTIC_H