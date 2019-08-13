//
// Created by dmitrii on 7/18/19.
//
/*
 * ALL OPENVINO STUFF IS COMMENTED OUT
 */
#ifndef ALEXLENS_ASICPLATFORM_H
#define ALEXLENS_ASICPLATFORM_H

#include <list>
#include <vector>
#include <string>

//#include <inference_engine.hpp>
#include <thread>
#include <mutex>
//#include <samples/classification_results.h>

#include "Platform.h"
#include "PlatformType.h"
#include "PlatformStatistic.h"

using namespace std;
//using namespace InferenceEngine;

const std::string whiteSpaces( " \f\n\r\t\v" );

class ASICPlatform : public Platform {
public:
    ASICPlatform(const int id);
    void runClassify() override;
    void setImagePaths(list<string> imagePaths) override;
    PlatformType getType () override;
    PlatformStatistic getStatistic() override;
    vector<string> getResults() override;
    string getId() override {return to_string(this->id+1);};

    static std::mutex mutex;

private:

   // InferencePlugin initPlugin();
    //CNNNetwork readIR();

    //void loadModelToPlugin(ExecutableNetwork *executableNetwork);
    //void configInputOutput(vector<string> *imageNames, vector<shared_ptr<unsigned char>> *imagesData, size_t *batchSize, string *firstOutputName);
    void convertListToVector(list<string> list, vector<string>* imageNames);
    //void prepareInput(InferRequest *inferRequest, vector<shared_ptr<unsigned char>> *imagesData);
   // void inference(double *total, InferRequest *inferRequest);
   // void loadLabels(vector<string> *labels);
    void trim(string& str, const string& trimChars = whiteSpaces);
    void trimRight(std::string& str, const string& trimChars = whiteSpaces);
    void trimLeft(string& str, const string& trimChars = whiteSpaces);
    void reset();
    //void createResultVector(Blob::Ptr _outBlob, vector<string> *imageNames, size_t *batchSize,
//                            vector<string> *labels, double *total, vector<string> *resultVector);
    void setStatistics(double *total, size_t *batchSize);
/*
    // Attributes
    InferencePlugin myriadPlugin;
    CNNNetReader netReader;
    CNNNetwork net;
    InputsDataMap inputInfo;
    OutputsDataMap outputInfo;
*/
    int id;
    PlatformType type;
    PlatformStatistic statistic;
    vector<string> imageNames;
    vector<string> results;

    // Constants
    const size_t NUM_TOP_RESULTS = 5;
    const size_t NUM_ITERATIONS = 1;

};


#endif //ALEXLENS_ASICPLATFORM_H