//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_EXECUTOR_H
#define ALEXLENS_EXECUTOR_H

#include <string>
#include <list>
#include <iostream>
#include <vector>

#include "../PlatformModule/Mode.h"
#include <GUIModule/Subject.h>
#include "../PlatformModule/PlatformManager.h"
#include "../PlatformModule/Platform.h"
#include "../PlatformModule/ASICPlatform.h"

using namespace std;

/**
 * Class Executor executes classification or training and communicates with platforms
 */
class Executor {
private:
    PlatformManager* platformManager; /// Instance of Platform Manager to get all platforms for computaion

public:
    list<string> imagePaths;

    //inline Subject* getSubject() { return this->subject;}

    /**
    * Standard Constructor
    */
    Executor();

    /**
     * Executes classification
     * @param imagePaths image paths which should be classified
     * @param mode mode, which was set by user and determines how classification should be executed
     * @param neuralNet neural net which should be used for classification
     * @param project_dir project home directory
     * @return results of image classification
     */
    vector<string> classify(list<string> imagePaths, Mode mode, string neuralNet, string project_dir);

    /**
     * Executes training
     * @param dirPath directory path where dataset for training is situated
     * @param mode mode mode, which was set by user and determines how training should be executed
     * @param neuralNet neural net which should be used for training
     * @param project_dir project home directory
     */
    void train (string dirPath, Mode mode, string neuralNet, string project_dir);

    /**
     * Getter for Platform Manager
     * @return Platform Manager
     */
    inline PlatformManager* getPlatformManager() {return this->platformManager;}

};


#endif //ALEXLENS_EXECUTOR_H