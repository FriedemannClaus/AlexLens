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
    /**
     * Returns FLOPS performance of the selected platform
     * @return FLOPS number
     */
    int getFLOPS();

    /**
     * Sets FLOPS number of the selected platform
     * @param flops
     */
    inline void setFLOPS(int flops) {this->flops = flops;}

    /**
     * Returns energy consumption of the selected platform
     * @return energy consumption in watts
     */
    double getEnergyConsum();

    /**
     * Sets energy consumption of the selected platform
     * @param energy consumption in watts
     */
    inline void setEnergyConsum(int energyConsum) {this->energyConsum = energyConsum;}

    /**
     * Returns the total inference time
     * @return inference time in ms
     */
    double getTotalInferenceTime();

    /**
     * Sets the total inference time
     * @param inference time in ms
     */
    void setTotalInferenceTime(double time);

    /**
     * Returns platform throughput
     * @return throughput
     */
    double getThroughput();

    /**
     * Sets platform throughput
     * @param throughput
     */
    void setThroughput(double throughput);

    /**
     * Returns average iteration time in ms (time it takes to classificate one image)
     * @return average iteration time in ms
     */
    double getAvgIterationTime();

    /**
     * Sets average iteration time in ms
     * @param avgIterationTime in ms
     */
    void setAvgIterationTime(double avgIterationTime);

private:
    double totalInferenceTime = 0.0;
    double throughput = 0.0;
    double avgIterationTime = 0.0;
    int flops = 0;
    double energyConsum = 0.0;
};

#endif //_PLATFORMSTATISTIC_H