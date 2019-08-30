//
// Created by dmitrii on 7/21/19.
//

#include "CPUPlatformTorch.h"
#include <torch/script.h>
#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Python.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

void CPUPlatformTorch::runClassify() {
    this->results.clear();
    torch::jit::script::Module module = torch::jit::load(model_path);

    const clock_t begin_time = clock();
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

        torch::Tensor top_scores = std::get<0>(result)[0].softmax(0);
        torch::Tensor top_idxs = std::get<1>(result)[0];

        std::string resultVector = "";
        for (int i = 0; i < 5; ++i) {
            int idx = top_idxs[i].item<int>();
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << top_scores[i].item<float>()*100.0f;
            resultVector += stream.str();
            resultVector+="% ";
            resultVector+=labels[idx];
            resultVector+="\n";
        }


        this->results.push_back(resultVector);
    }
    const float final_time = float( clock () - begin_time )/CLOCKS_PER_SEC*100;

    this->statistic.setTotalInferenceTime(final_time);
    this->statistic.setAvgIterationTime(final_time/results.size());
    this->imageNames.clear();
}

CPUPlatformTorch::CPUPlatformTorch() {
    this->type = PlatformType::CPU_TORCH;
    this->statistic.setEnergyConsum(20);
    this->statistic.setFLOPS(19);
}

void CPUPlatformTorch::setNeuralNet(string neuralNet) {
    this->model_path = this->project_dir + "resources/" + neuralNet + "/";
    this->model_path += neuralNet + "_model" + ".pt";
    this->label_path = this->project_dir + "resources/" + neuralNet + "/";
    this->label_path += neuralNet + "_labels" + ".txt";
}
