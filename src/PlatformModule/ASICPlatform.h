//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_ASICPLATFORM_H
#define ALEXLENS_ASICPLATFORM_H

#include <list>
#include <vector>
#include <string>

#include <inference_engine.hpp>
#include <thread>
#include <mutex>

#include "Platform.h"
#include "PlatformType.h"
#include "PlatformStatistic.h"

using namespace std;
using namespace InferenceEngine;

const std::string whiteSpaces( " \f\n\r\t\v" );

class ASICPlatform : public Platform {
public:
    string model_path;
    string label_path;
    string project_dir;
    string structure_path;
    string mapping_path;
    ASICPlatform(const int id);
    void runClassify() override;
    void setImagePaths(list<string> imagePaths);
    PlatformType getType ();
    PlatformStatistic getStatistic();
    vector<string> getResults();
    inline void setNeuralNet(string neuralNet) override {
        this->model_path = this->project_dir + "resources/" + neuralNet + "/";
        this->model_path += neuralNet + "_model" + ".bin";
        this->structure_path = this->project_dir +  "resources/" + neuralNet + "/";
        this->structure_path += neuralNet + ".xml";
        this->mapping_path = this->project_dir +  "resources/" + neuralNet + "/";
        this->mapping_path += neuralNet + ".mapping";
        this->label_path = this->project_dir + "resources/" + neuralNet + "/";
        this->label_path += neuralNet + "_labels" + ".txt";
    }

    inline void setProjectDir(std::string dir) override {this->project_dir = dir;}

    static std::mutex mutex;
    string getId() override {return to_string(this->id+1);};

private:

    InferencePlugin initPlugin();
    CNNNetwork readIR();

    void loadModelToPlugin(ExecutableNetwork *executableNetwork);
    void configInputOutput(vector<string> *imageNames, vector<shared_ptr<unsigned char>> *imagesData, size_t *batchSize, string *firstOutputName);
    void convertListToVector(list<string> list, vector<string>* imageNames);
    void prepareInput(InferRequest *inferRequest, vector<shared_ptr<unsigned char>> *imagesData);
    void inference(double *total, InferRequest *inferRequest);
    void loadLabels(vector<string> *labels);
    void trim(string& str, const string& trimChars = whiteSpaces);
    void trimRight(std::string& str, const string& trimChars = whiteSpaces);
    void trimLeft(string& str, const string& trimChars = whiteSpaces);
    void reset();
    void createResultVector(Blob::Ptr _outBlob, vector<string> *imageNames, size_t *batchSize,
                            vector<string> *labels, double *total, vector<string> *resultVector);
    void setStatistics(double *total, size_t *batchSize);

    // Attributes
    InferencePlugin myriadPlugin;
    //CNNNetReader netReader;
    CNNNetwork net;
    InputsDataMap inputInfo;
    OutputsDataMap outputInfo;

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