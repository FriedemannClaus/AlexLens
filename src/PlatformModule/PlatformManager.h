//
// Created by dmitrii on 7/21/19.
//

#ifndef ALEXLENS_PLATFORMMANAGER_H
#define ALEXLENS_PLATFORMMANAGER_H

#include <iostream>
#include <list>
#include "Platform.h"
#include "Mode.h"
#include "ASICPlatform.h"
#include "CPUPlatformTorch.h"
#include "CPUPlatform.h"
#include "GPUPlatform.h"

using namespace std;

/**
 * Class PlatformManager is managing all hetergenous Platforms
 */
class PlatformManager {
private:
    int NUM_PLATFORMS = 0; /// The number Of ASICPlatforms
    list<Platform*> platforms; /// List of all initialized platforms
    Mode mode; ///The Mode which was set by user
    string neuralNet;  /// The neural net which was set by user
public:
    /**
     * Standard Constructor
     */
    PlatformManager();

    /**
     * Standard class destructor
     */
    ~PlatformManager() ;

    /**
     * Getter for all available platforms corresponding to mode
     * @return all available platforms corresponding to mode
     */
    list<Platform *> getAvailablePlatforms();

    /**
     * Setter for the operation mode
     * @param mode mode which should be set
     */
    inline void setMode(Mode mode) {this->mode = mode;}

    /**
     * Setter for neural net
     * @param neuralNet neural net which should be set
     */
    inline void setNeuralNet(string neuralNet) {this->neuralNet = neuralNet;}

    /**
     * The method clears all image pahts in all platforms
     */
    inline void clearAllImagePaths() {for (auto platform:platforms) {platform->clearImagePaths();}}

    /**
     * The method determines the number of sticks
     */
    void setNumberOfSticks();

    /**
     * The method returns number of connected sticks
     * @return number of connected sticks
     */
    inline int getNumberOfSticks() {return NUM_PLATFORMS;}
};


#endif //ALEXLENS_PLATFORMMANAGER_H