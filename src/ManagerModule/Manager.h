//
// Created by dmitrii on 11.07.19.
//

#ifndef ALEXLENS_MANAGER_H
#define ALEXLENS_MANAGER_H

#include <list>
#include <iterator>
#include <string>
#include <GUIModule/Subject.h>
#include "../PlatformModule/Mode.h"
#include "../PlatformModule/ModeUtil.h"
#include "Executor.h"
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>


using namespace std;

/**
 * Class Manager. The Central Point of program
 * for realization of communication between GUI and Executor
 */
class Manager{
private:
    list<string> defaultModesClassify; /// Default Modes for Image classification  which will be shown at the start of program
    list<string> defaultModesTraining; /// Default Modes for Training which will be shown at the start of program
    list<string> defaultNeuralNets; /// Default Neural Nets for Image classification  which will be shown at the start of program
    Mode operationMode; ///current operation mode which was set in GUI
    string neuralNet; /// current Neural Net which was set in GUI
    list<string> imagePaths; /// Paths of images which should be classified
    string dataSetPath; ///Path od dataset for training
    Executor* executor; /// Insatnce for communication with Executor
    Subject* subject; /// Subject to inform all observers to update GUI
    vector<string> results; /// results of image classification
    string PROJECT_DIR; /// Project home directory

    bool net_model_bin; ///Boolean variable, true if model of type .bin for ASICPlatform (NCS) is found
    bool net_xml; ///Boolean variable, true if the file of type .xml for ASIC Platform (NCS) is found
    bool net_mapping; ///Boolean variable, true if the file of type .mapping for ASIC Platform (NCS) is found
    bool net_labels; ///Boolean variable, true if labels are found
    bool net_model_h5; ///Boolean variable, true if model of type .h5 for CPUPlatform is found
    bool net_model_pt;///Boolean variable, true if model of type .pz for CPUTPlatformTorch is found

public:
    /**
     * The standard constructor
     */
    Manager();
    /**
     * Constructor for class Manager
     * @param subject subject for observer pattern
     */
    Manager(Subject* subject);

    /**
     * Getter for project home directory
     * @return project home directory
     */
    inline string getProjectDir() {return this->PROJECT_DIR;}

    /**
     * Setter for dataset path for training
     * @param path rhe path to set
     */
    inline void setDatasetPath(string path) {this->dataSetPath = path;}
    /**
     * This method adds Image into imagePaths for later classification
     * @param imagePath Path of image which is added
     */
    inline void addImage(string imagePath) {this->imagePaths.push_front(imagePath);}

    /**
    * Setter for mode
    * @param mode mode which will be set
    */
    inline void setMode(Mode mode) {operationMode = mode;}

    /**
     * Setter for Neural Net
     * @param neuralNet neural net which will be set
     */
    inline void setNeuralNet(string neuralNet) {this->neuralNet = neuralNet;}

    /**
   * Getter for Neural net
   * @return neural net which is currently set
   */
    inline string getNeuralNet() {return this->neuralNet;}

    /**
     * Getter for default modes for Image Classification
     * @return default modes for Image Classification
     */
    inline list<string> getDefaultModesClassify() {return defaultModesClassify;}

    /**
     * Getter for default modes for Training
     * @return default modes for Training
     */
    inline list<string> getDefaultModesTraining() {return defaultModesTraining;}

    /**
     * Getter for default neural nets
     * @return default neural nets
     */
    inline list<string> getDeafaultNeuralNets() {return defaultNeuralNets;}

    /**
     * Getter for executor
     * @return executor
     */
    inline Executor* getExecutor() { return this->executor;}

    /**
     * Getter for subject
     * @return subject for observer pattern
     */
    inline Subject* getSubject() { return  this->subject;}

    /**
     * Getter for results of classification
     * @return results of classification
     */
    inline vector<string> getResults() { return this->results;}

    /**
     * Delete or clear all image Paths
     */
    inline void clearImagePaths() {this->imagePaths.clear();}

    /**
    * Add new available neural net
    * @param newNN new neural net
    */
    inline void addNeuralNet(string newNN) {this->defaultNeuralNets.push_back(newNN);}

    /**
     * Runs classification process
     */
    void runClassify();

    /**
     * Runs training process
     */
    void runTraining();

    /**
     * The method check wether the configuration which was set by user runnable or not
     * @return true if the configuration (neural net, mode) can be run
     */
    bool isRunnable();


private:
    /**
     * Check if file exists
     * @param name name of file
     * @return true if file with this name exists
     */
    bool exists_file (const std::string& name);

    /**
     * Setter for Project home directory
     */
    void setProjectDir();

    /**
     * Setter for default classification modes
     */
    void setDefaultModesClassify();

    /**
    * Setter for default training modes
    */
    void setDefaultModesTraining();

    /**
     * Setter for default neural nets
     */
    void setDefaultNeuralNets();

    /**
     * The methods determines which types of file are available in resources
     * and sets the corresponding bool variables such as net_model_bin
     */
    void whichFilesInResources();

    /**
     * The method constructs the readable name for the parameter panel from directory
     * @param imageDir the directory
     */
    void makeNameFromDir(std::string& imageDir);

};


#endif //ALEXLENS_MANAGER_H