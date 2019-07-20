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
#include <samples/classification_results.h>

using namespace InferenceEngine;
using namespace std;


const size_t NUM_TOP_RESULTS = 5;
const size_t NUM_ITERATIONS = 1;


ASICPlatform::ASICPlatform() {
    myriadPlugin = initPlugin();
    net = readIR();
    inputInfo = net.getInputsInfo();


}

InferencePlugin ASICPlatform::initPlugin() {
    InferenceEnginePluginPtr pluginPtr = PluginDispatcher({"/opt/intel/openvino/deployment_tools/inference_engine/lib/intel64"}).getSuitablePlugin(TargetDevice::eMYRIAD);
    InferencePlugin plugin(pluginPtr);
    return plugin;
}

CNNNetwork ASICPlatform::readIR() {
    netReader.ReadNetwork("../alexnet-FP16/alexnet.xml");
    netReader.ReadWeights("../alexnet-FP16/alexnet.bin");
    net = netReader.getNetwork();
    return net;
}


vector<string> ASICPlatform::runClassify(__cxx11::list<string> list) {
    /*convertListToVector(list); // fine
    configInputOutput(); // fine
    ExecutableNetwork executableNetwork = loadModelToPlugin(); // fine
    inferRequest = executableNetwork.CreateInferRequest(); // fine
    prepareInput(); // fine
    inference(); // fine
    processOutput();*/
    vector<string> a = {"cat 0.9999 \n dog 0.01111 \n shark 0.0001 \n penguin 0.001 \n monkey 0.000 "};
    return a;
}

void ASICPlatform::configInputOutput() {

    auto inputInfoItem = *inputInfo.begin();
    inputInfoItem.second->setPrecision(Precision::U8); // Precision parameter
    inputInfoItem.second->setLayout(Layout::NCHW); // Layout of input data

    //transfer images from imagepaths to appropriate format in order to work with them
    for (auto & i: imageNames)
    {
        FormatReader::ReaderPtr reader(i.c_str());
        //check image loading read
        if (reader.get() == nullptr) continue;

        // Extract image data and store it
        shared_ptr<unsigned char> data(
                reader->getData(inputInfoItem.second->getTensorDesc().getDims()[3],
                                inputInfoItem.second->getTensorDesc().getDims()[2]));

        if (data.get() != nullptr) {
            imagesData.push_back(data);
        }
    }
    if (imagesData.empty()) throw logic_error("Keine gültigen Bilder gefunden!");

    net.setBatchSize(imagesData.size());
    batchSize = net.getBatchSize();
    //Prep Output
    outputInfo = net.getOutputsInfo();

    for (auto & item : outputInfo) {
        if (firstOutputName.empty()) {
            firstOutputName = item.first;
        }
        DataPtr outputData = item.second;
        if (!outputData) {
            throw logic_error("output data pointer is invalid");
        }

        item.second->setPrecision(Precision::FP32);
    }

    inputInfoItem.second = {};// Normally part of loading model
}


void ASICPlatform::convertListToVector(__cxx11::list<string> list) {
    for(string i: list) {
        imageNames.push_back(i);
    }
}

ExecutableNetwork ASICPlatform::loadModelToPlugin() {
    // 4. Load model to plugin
    ExecutableNetwork executableNetwork = myriadPlugin.LoadNetwork(net, {});
    outputInfo = {};
    net = {};
    netReader = {};
    return executableNetwork;
}

void ASICPlatform::prepareInput() {
    for (const auto & item : inputInfo) {
        // Creating input blob
        Blob::Ptr input = inferRequest.GetBlob(item.first);

        // Filling input tensor with images. First b channel, then g and r channels
        size_t num_channels = input->getTensorDesc().getDims()[1];
        size_t image_size = input->getTensorDesc().getDims()[2] * input->getTensorDesc().getDims()[3];

        auto data = input->buffer().as<PrecisionTrait<Precision::U8>::value_type*>();

        //Iterate over all input images
        for (size_t image_id = 0; image_id < imagesData.size(); ++image_id) {
            //Iterate over all pixel in image (b,g,r)
            for (size_t pid = 0; pid < image_size; pid++) {
                // Iterate over all channels
                for (size_t ch = 0; ch < num_channels; ++ch) {
                    // [images stride + channels stride + pixel id ] all in bytes
                    data[image_id * image_size * num_channels + ch * image_size + pid ] = imagesData.at(image_id).get()[pid*num_channels + ch];
                }
            }
        }
    }
    inputInfo = {};
}

void ASICPlatform::inference() {
    typedef chrono::high_resolution_clock Time;
    typedef chrono::duration<double, ratio<1, 1000>> ms;
    typedef chrono::duration<float> fsec;

    total = 0.0;

    // Start inference & calc performance
    for (size_t iterations = 0; iterations < NUM_ITERATIONS; ++iterations) {
        auto t0 = Time::now();
        inferRequest.Infer();
        auto t1 = Time::now();
        fsec fs = t1 - t0;
        ms d = chrono::duration_cast<ms>(fs);
        total += d.count();
    }
}

void ASICPlatform::processOutput() {
    const Blob::Ptr output_blob = inferRequest.GetBlob(firstOutputName);

    // Read labels for AlexNet
    string labelFileName = "../alexnet-FP16/alexnet.labels";
    vector<string> labels;
    ifstream inputFile;
    inputFile.open(labelFileName, ios::in);
    if (inputFile.is_open()) {
        string strLine;
        while (getline(inputFile, strLine)) {
            trim(strLine);
            labels.push_back(strLine);
        }
    }

    ClassificationResult classificationResult(output_blob, imageNames, batchSize, NUM_TOP_RESULTS, labels);
    classificationResult.print();

    cout << endl << "total inference time: " << total << endl;
    cout << "Average running time of one iteration: " << total / static_cast<double>(NUM_ITERATIONS) << " ms" << endl;
    cout << endl << "Throughput: " << 1000 * static_cast<double>(NUM_ITERATIONS) * batchSize / total << " FPS" << endl;
    cout << endl;
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
