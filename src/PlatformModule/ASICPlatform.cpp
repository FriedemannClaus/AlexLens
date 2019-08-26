//
// Created by vietp on 7/18/19.
//

#include "ASICPlatform.h"
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

#include <inference_engine.hpp>
#include <format_reader_ptr.h>

using namespace InferenceEngine;
using namespace std;

std::mutex ASICPlatform::mutex;

ASICPlatform::ASICPlatform(const int id) {
    this->id = id;
    this->type = PlatformType::ASIC;
    this->myriadPlugin = initPlugin();
    this->net = readIR();
    this->inputInfo = net.getInputsInfo();
    this->statistic.setEnergyConsum(2);
    this->statistic.setFLOPS(100);
}

InferencePlugin ASICPlatform::initPlugin() {
    InferenceEnginePluginPtr pluginPtr = PluginDispatcher({"/opt/intel/openvino/deployment_tools/inference_engine/lib/intel64"}).getSuitablePlugin(TargetDevice::eMYRIAD);
    InferencePlugin plugin(pluginPtr);
    return plugin;
}

CNNNetwork ASICPlatform::readIR() {
    netReader.ReadNetwork("../../resources/alexnet-FP16/alexnet.xml");
    netReader.ReadWeights("../../resources/alexnet-FP16/alexnet.bin");
    net = netReader.getNetwork();
    return net;
}

void ASICPlatform::runClassify() {
    //vector<string> imageNames;
    //convertListToVector(list, &imageNames);

    vector<shared_ptr<unsigned char>> imagesData;
    size_t batchSize;
    string firstOutputName;
    configInputOutput(&imageNames, &imagesData, &batchSize, &firstOutputName);

    ExecutableNetwork executableNetwork;

    loadModelToPlugin(&executableNetwork);

    InferRequest inferRequest = executableNetwork.CreateInferRequest();

    prepareInput(&inferRequest, &imagesData);

    double total;
    inference(&total, &inferRequest);

    vector<string> labels;
    loadLabels(&labels);


    const Blob::Ptr output_blob = inferRequest.GetBlob(firstOutputName);
    size_t nTop = 5;
    vector<string> resultVector;
    createResultVector(output_blob, &imageNames, &batchSize, &labels, &total, &resultVector);

    setStatistics(&total, &batchSize);

    reset();
    this->results = resultVector;
    cout << "this was stick " << this->id << endl;
    //return resultVector;
}

void ASICPlatform::convertListToVector(list<string> list, vector<string> *imageNames) {
    for(string i : list) {
        imageNames->push_back(i);
    }
}

void ASICPlatform::configInputOutput(vector<string> *imageNames, vector<shared_ptr<unsigned char>> *imagesData, size_t *batchSize, string *firstOutputName) {

    auto inputInfoItem = *inputInfo.begin();
    inputInfoItem.second->setPrecision(Precision::U8); // Precision parameter
    inputInfoItem.second->setLayout(Layout::NCHW); // Layout of input data

    //transfer images from imagepaths to appropriate format in order to work with them
    for (auto & i: *imageNames)
    {
        FormatReader::ReaderPtr reader(i.c_str());
        //check image loading read
        if (reader.get() == nullptr) continue;

        // Extract image data and store it
        shared_ptr<unsigned char> data(
                reader->getData(inputInfoItem.second->getTensorDesc().getDims()[3],
                                inputInfoItem.second->getTensorDesc().getDims()[2]));

        if (data.get() != nullptr) {
            imagesData->push_back(data);
        }
    }
    if (imagesData->empty()) throw logic_error("Keine gültigen Bilder gefunden!");

    net.setBatchSize(imagesData->size());
    *batchSize = net.getBatchSize();
    //Prep Output
    outputInfo = net.getOutputsInfo();

    for (auto & item : outputInfo) {
        if (firstOutputName->empty()) {
            *firstOutputName = item.first;
        }
        DataPtr outputData = item.second;
        if (!outputData) {
            throw logic_error("output data pointer is invalid");
        }

        item.second->setPrecision(Precision::FP32);
    }
    inputInfoItem.second = {};// Normally part of loading model
}

void ASICPlatform::loadModelToPlugin(ExecutableNetwork *executableNetwork) {
    // 4. Load model to plugin
    mutex.lock();
    *executableNetwork = myriadPlugin.LoadNetwork(net, {});
    mutex.unlock();
    outputInfo = {};
    net = {};
    netReader = {};
}

void ASICPlatform::prepareInput(InferRequest *inferRequest, vector<shared_ptr<unsigned char>> *imagesData) {
    for (const auto & item : inputInfo) {
        // Creating input blob
        Blob::Ptr input = inferRequest->GetBlob(item.first);

        // Filling input tensor with images. First b channel, then g and r channels
        size_t num_channels = input->getTensorDesc().getDims()[1];
        size_t image_size = input->getTensorDesc().getDims()[2] * input->getTensorDesc().getDims()[3];

        auto data = input->buffer().as<PrecisionTrait<Precision::U8>::value_type*>();

        //Iterate over all input images
        for (size_t image_id = 0; image_id < imagesData->size(); ++image_id) {
            //Iterate over all pixel in image (b,g,r)
            for (size_t pid = 0; pid < image_size; pid++) {
                // Iterate over all channels
                for (size_t ch = 0; ch < num_channels; ++ch) {
                    // [images stride + channels stride + pixel id ] all in bytes
                    data[image_id * image_size * num_channels + ch * image_size + pid ] = (*imagesData).at(image_id).get()[pid*num_channels + ch];
                }
            }
        }
    }
    inputInfo = {};
}

void ASICPlatform::inference(double *total, InferRequest *inferRequest) {
    typedef chrono::high_resolution_clock Time;
    typedef chrono::duration<double, ratio<1, 1000>> ms;
    typedef chrono::duration<float> fsec;

    *total = 0.0;

    // Start inference & calc performance
    for (size_t iterations = 0; iterations < NUM_ITERATIONS; ++iterations) {
        auto t0 = Time::now();
        inferRequest->Infer();
        auto t1 = Time::now();
        fsec fs = t1 - t0;
        ms d = chrono::duration_cast<ms>(fs);
        *total += d.count();
    }
}

void ASICPlatform::loadLabels(vector<string> *labels) {

    // Read labels for AlexNet
    string labelFileName = "../../resources/alexnet-FP16/alexnet.labels";
    ifstream inputFile;
    inputFile.open(labelFileName, ios::in);
    if (inputFile.is_open()) {
        string strLine;
        while (getline(inputFile, strLine)) {
            trim(strLine);
            labels->push_back(strLine);
        }
    }

    /*
    ClassificationResult classificationResult(output_blob, *imageNames, *batchSize, NUM_TOP_RESULTS, labels);
    classificationResult.print();
    cout << endl << "total inference time: " << *total << endl;
    cout << "Average running time of one iteration: " << *total / static_cast<double>(NUM_ITERATIONS) << " ms" << endl;
    cout << endl << "Throughput: " << 1000 * static_cast<double>(NUM_ITERATIONS) * *batchSize / *total << " FPS" << endl;
    cout << endl;*/

}


void ASICPlatform::trimRight(string& str, const string& trimChars)
{
    string::size_type pos = str.find_last_not_of(trimChars);
    str.erase(pos + 1);
}


void ASICPlatform::trimLeft(string& str, const string& trimChars)
{
    string::size_type pos = str.find_first_not_of(trimChars);
    str.erase(0, pos);
}

void ASICPlatform::trim(string &str, const string &trimChars) {
    trimRight(str, trimChars);
    trimLeft(str, trimChars);
}

void ASICPlatform::reset() {
    net = readIR();
    inputInfo = net.getInputsInfo();
    this->imageNames.clear();
}

void ASICPlatform::createResultVector(Blob::Ptr _outBlob, vector<string> *imageNames, size_t *batchSize,
                                      vector<string> *labels, double *total, vector<string> *resultVector) {

    string _classidStr = "classid";
    string _probabilityStr = "probability";
    string _labelStr = "label";


    /** This vector stores id's of top N results **/
    vector<unsigned> results;
    TopResults(NUM_TOP_RESULTS, *_outBlob, results);

    /** Print the result iterating over each batch **/
    //cout << endl << "Top " << *nTop << " results:" << endl << endl;
    for (unsigned int image_id = 0; image_id < *batchSize; ++image_id) {
        string resultString = "";

        cout << "Image " << (*imageNames)[image_id] << endl;
        //resultString = (*imageNames)[image_id];

        /*// Header
        cout << _classidStr << " " << _probabilityStr;
        if (!labels->empty())
            cout << " " << _labelStr;
        string classidColumn(_classidStr.length(), '-');
        string probabilityColumn(_probabilityStr.length(), '-');
        string labelColumn(_labelStr.length(), '-');
        cout << endl << classidColumn << " " << probabilityColumn;
        if (!labels->empty())
            cout << " " << labelColumn;
        cout << endl;*/

        for (size_t id = image_id * NUM_TOP_RESULTS, cnt = 0; id < (image_id + 1) * NUM_TOP_RESULTS; ++cnt, ++id) {
            cout.precision(7);
            /** Getting probability for resulting class **/
            const auto result = _outBlob->buffer().
                    as<InferenceEngine::PrecisionTrait<InferenceEngine::Precision::FP32>::value_type*>()
            [results[id] + image_id * (_outBlob->size() / *batchSize)];

            //cout << setw(static_cast<int>(_classidStr.length())) << left << results[id] << " ";
            //cout << left << setw(static_cast<int>(_probabilityStr.length())) << fixed << result;
            resultString += to_string(result);

            if (!labels->empty()) {
                //cout << " " + (*labels)[results[id]];
                resultString += "   ";
                resultString += (*labels)[results[id]];

            }
            //cout << endl;
            resultString += '\n';
        }
        resultVector->push_back(resultString);
        //cout << endl;
    }
}

void ASICPlatform::setStatistics(double *total, size_t *batchSize) {
    cout << endl << "Total inference time: " << *total << endl;
    cout << "Average running time of one iteration: " << *total / static_cast<double>(NUM_ITERATIONS) << " ms" << endl;
    cout << "Throughput: " << 1000 * static_cast<double>(NUM_ITERATIONS) * *batchSize / *total << " FPS" << endl;
    cout << endl;

    statistic.setTotalInferenceTime(*total);
    statistic.setAvgIterationTime(*total / static_cast<double>(NUM_ITERATIONS)); // ms
    statistic.setThroughput(1000 * static_cast<double>(NUM_ITERATIONS) * *batchSize / *total); // FPS
}

PlatformType ASICPlatform::getType() {
    return this->type;
}

PlatformStatistic ASICPlatform::getStatistic() {
    return this->statistic;
}


void ASICPlatform::setImagePaths(list<string> imagePaths) {
    convertListToVector(imagePaths, &imageNames);
}


vector<string> ASICPlatform::getResults() {
    return this->results;
}