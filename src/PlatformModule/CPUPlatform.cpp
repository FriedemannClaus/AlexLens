//
// Created by dmitrii on 7/21/19.
//

#include "CPUPlatform.h"
#include <torch/script.h>
#include <torch/torch.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <Python.h>

#include <iostream>
#include <memory>
#include <vector>

#include <string>
//#include <bits/stdc++.h>

using namespace std;

void CPUPlatform::runClassify() {
    this->results.clear();

    std::cout << model_path <<std::endl;
    std::cout << label_path <<std::endl;
    //model_path = "/home/dmitrii/alexnetTr.pt";
    // Deserialize the ScriptModule from a file using torch::jit::load().
    //std::string model_path = "/home/dmitrii/repos/cpp-pytorch/caltech.pt";//"/home/dmitrii/alexnetTr.pt";
    //std::string label_path = "/home/dmitrii/Downloads/Telegram Desktop/imagenet_classes.txt";
    //std::string image_path = "/home/dmitrii/Downloads/Telegram Desktop/test/test/bear/009_0071.jpg";
    torch::jit::script::Module module = torch::jit::load(model_path);


    for (auto image_path:imageNames) {
        // load image with opencv and transform
        cv::Mat image;
        image = cv::imread(image_path, 1);
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        cv::Mat img_float;
        image.convertTo(img_float, CV_32F, 1.0/255);
        cv::resize(img_float, img_float, cv::Size(224, 224));

        at::Tensor img_tensor = torch::from_blob(img_float.data, {1, 224, 224, 3});
        img_tensor = img_tensor.permute({0,3,1,2});
        img_tensor[0][0] = img_tensor[0][0].sub_(0.485).div_(0.229);
        img_tensor[0][1] = img_tensor[0][1].sub_(0.456).div_(0.224);
        img_tensor[0][2] = img_tensor[0][2].sub_(0.406).div_(0.225);

        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(img_tensor);

        // Execute the model and turn its output into a tensor.
        torch::Tensor out_tensor = module.forward(inputs).toTensor();

        // Load labels
        std::string label_file = label_path;
        std::ifstream rf(label_file.c_str());
        CHECK(rf) << "Unable to open labels file " << label_file;
        std::string line;
        std::vector<std::string> labels;
        while (std::getline(rf, line))
            labels.push_back(line);

        // print predicted top-5 labels
        std::tuple<torch::Tensor,torch::Tensor> result = out_tensor.sort(-1, true);

        torch::Tensor top_scores = std::get<0>(result)[0];
        torch::Tensor top_idxs = std::get<1>(result)[0].toType(torch::kInt32);

        auto top_scores_a = top_scores.accessor<float,1>();
        auto top_idxs_a = top_idxs.accessor<int,1>();

        std::string resultVector = "";
        for (int i = 0; i < 5; ++i) {
            int idx = top_idxs_a[i];
            resultVector+= std::to_string(top_scores_a[i]);
            resultVector+=" ";
            resultVector+=labels[idx];
            resultVector+="\n";
        }


        this->results.push_back(resultVector);
    }
    this->imageNames.clear();
}

CPUPlatform::CPUPlatform() {
    this->type = PlatformType::CPU;
}

void CPUPlatform::runClassifyOne(string imagePath) {

}

void CPUPlatform::setImagePaths(list<string> imagePaths) {
    convertListToVector(imagePaths, &imageNames);
}

void CPUPlatform::convertListToVector(list<string> list, vector<string> *imageNames) {
    for(string i : list) {
        imageNames->push_back(i);
    }
}

vector<string> CPUPlatform::getResults() {
    return this->results;
}

void CPUPlatform::runTraining() {
    //Py_SetProgramName(reinterpret_cast<const wchar_t *>(argv[0]));
    // Path of TransferLearning.py
    //char fileName[] = "/home/viet/CLionProjects/AlexLens/TransferLearning.py";
    string str = "TransferLearning.py";
    char fileName[this->project_dir.length()+str.length()];
    string fileNamePath = this->project_dir + str;
    std::cout << fileNamePath << std::endl;
    strcpy(fileName, fileNamePath.c_str());
    FILE* fp;
    Py_Initialize();
    fp = _Py_fopen(fileName, "r");
    // Path of dataset
    char path[this->datasetPath.length()];
    strcpy(path, this->datasetPath.c_str());
    char* py_argv[] = {strdup(path)};
    wchar_t *w_py_argv[] = {Py_DecodeLocale(py_argv[0], NULL)};
    PySys_SetArgv(1, w_py_argv);
    PyRun_SimpleFile(fp, fileName);
    free(py_argv[0]);
    Py_Finalize();
    //syscall variant start
    /*std::string command_str = "/home/dmitrii/anaconda3/bin/python /home/dmitrii/AlexLens/TransferLearning.py ";
    command_str += this->datasetPath;
    const char *command = command_str.c_str();
    system(command);*/
    //syzscall variant end
}

