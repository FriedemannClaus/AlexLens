//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_PLATFORM_H
#define ALEXLENS_PLATFORM_H

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include "PlatformType.h"
#include "PlatformStatistic.h"
#include <sstream>


using namespace std;

/**
 * The abstract class Platform, which represents a heterogenous platform.
 * For creating of a new platform extend this abstract class.
 */
class Platform {
protected:
    int id; ///ID of platform
    PlatformType type; ///Type of platform
    PlatformStatistic statistic; ///All statistics after executing of platform
    vector<string> imageNames; ///Input image paths
    vector<string> results; ///Results of classification
    std::string project_dir; ///Project directory
    std::string datasetPath; ///Path of dataset for training
    string model_path; ///path of saved model
    string label_path; ///path of labels

public:
    /**
     * Runs classification of platform
     */
    virtual void runClassify();
    /**
     * Runs transfer learning process of platform
     */
    virtual void runTraining();
    /**
     * Setter for the neural net and corresponding paths of model
     * @param neuralNet the neural net to set
     */
    inline virtual void setNeuralNet(string neuralNet){};

    /**
     * Getter for platform type
     * @return the platform type
     */
    inline PlatformType getType() {return this->type;}
    /**
     * Setter for dataset path
     * @param path the dataset path
     */
    inline void setDatasetPath(std::string path)  {this->datasetPath = path;}
    /**
     * Getter for platform statistics
     * @return the platform statistics
     */
    inline PlatformStatistic getStatistic()  { return this->statistic;}
    /**
     * Setter for project directory
     * @param dir the project directory
     */
    inline void setProjectDir(std::string dir)  {this->project_dir = dir;}
    /**
     * Getter for classification results
     * @return the results of classification
     */
    inline vector<string> getResults() {return this->results;}
    /**
     * Setter for image paths
     * @param imagePaths the image paths, which should be classified
     */
    inline void setImagePaths(list<string> imagePaths) {convertListToVector(imagePaths, &imageNames);}
    /**
     * Getter for ID of platform
     * @return the id of platform
     */
    inline virtual string getId() {return to_string(this->id+1);};

    /**
     * The methid clears all image paths in platform
     */
    inline void clearImagePaths() {imageNames.clear();}

    /**
     * The method transform float number into percent
     * @param a float number
     * @return percent
     */
    inline static string floatToPercent(float a) {
        std::string result = "";
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << a*100.0f;
        result += stream.str();
        result += "% ";
        return result;

    }
    /**
     * The method returns the number of images to classify
     * @return size of images to classify
     */
    inline int getSizeOgImagePath() {return imageNames.size();}

private:
    /**
     * The methid converts std::list into std::vector
     * @param list the std::list to convert
     * @param imageNames std::vector of image paths
     */
    void convertListToVector(list<string> list, vector<string> *imageNames);
};


#endif //ALEXLENS_PLATFORM_H