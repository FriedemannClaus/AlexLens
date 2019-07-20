//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_ASICPLATFORM_H
#define ALEXLENS_ASICPLATFORM_H

#include <list>
#include <vector>
#include <string>

#include <inference_engine.hpp>

#include "Platform.h"

using namespace std;
using namespace InferenceEngine;

const std::string whiteSpaces( " \f\n\r\t\v" );

class ASICPlatform : public Platform {
    vector<string> runClassify(__cxx11::list<string> list);
public:
    ASICPlatform();
private:

    void convertListToVector(std::__cxx11::list<std::string> list);
    InferencePlugin initPlugin();
    CNNNetwork readIR();
    void configInputOutput();
    ExecutableNetwork loadModelToPlugin();
    void prepareInput();
    void inference();
    void processOutput();

    void trim(string& str, const string& trimChars = whiteSpaces);
    void trimRight(std::string& str, const string& trimChars = whiteSpaces);
    void trimLeft(string& str, const string& trimChars = whiteSpaces);

    // Attributes
    InferencePlugin myriadPlugin;
    CNNNetReader netReader;
    CNNNetwork net;
    InputsDataMap inputInfo;
    OutputsDataMap outputInfo;
    InferRequest inferRequest;
    vector<shared_ptr<unsigned char>> imagesData; //vector of images in appropriate format
    string firstOutputName;
    double total;
    vector<string> imageNames;
    size_t batchSize;
};


#endif //ALEXLENS_ASICPLATFORM_H