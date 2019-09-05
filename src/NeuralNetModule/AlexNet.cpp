//
// Created by Viet Pham.
//
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "AlexNet.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <PlatformModule/Platform.h>
#include <Exceptions/ReadException.h>

using namespace std;
using namespace cv;

AlexNet::AlexNet(std::vector<std::string> &results, bool mode) {
    this->results = &results;
    this->GPUMode = mode;
    initWeights();
    initLayers();
    initLabels();
}


void AlexNet::initWeights() {
    AlexNetWeightParser *weightParser = new AlexNetWeightParser(
            conv1_w, conv1_b, conv2_1_w, conv2_1_b, conv2_2_w, conv2_2_b,
            conv3_w, conv3_b, conv4_1_w, conv4_1_b, conv4_2_w, conv4_2_b,
            conv5_1_w, conv5_1_b, conv5_2_w, conv5_2_b, dense1_w, dense1_b,
            dense2_w, dense2_b, dense3_w, dense3_b
    );
    GPUMode ? cout << "GPU Platform: " << endl : cout << "CPU Platform: " << endl;
    weightParser->parse();
}

void AlexNet::initLayers() {
    conv_1 = new Conv2D(96, 11, 4, 0, conv1_w, conv1_b, GPUMode);
    reLU = new ReLU();
    maxPool_1 = new MaxPool2D(3, 3, 2);
    norm_1 = new Normalization(2, 0.0001, 0.75, 5);
    conv_2_1 = new Conv2D(128, 5, 1, 2, conv2_1_w, conv2_1_b, GPUMode);
    conv_2_2 = new Conv2D(128, 5, 1, 2, conv2_2_w, conv2_2_b, GPUMode);
    maxPool_2 = new MaxPool2D(3, 3, 2);
    norm_2 = new Normalization(2, 0.0001, 0.75, 5);
    conv_3 = new Conv2D(384, 3, 1, 1, conv3_w, conv3_b, GPUMode);
    conv_4_1 = new Conv2D(192, 3, 1, 1, conv4_1_w, conv4_1_b, GPUMode);
    conv_4_2 = new Conv2D(192, 3, 1, 1, conv4_2_w, conv4_2_b, GPUMode);
    conv_5_1 = new Conv2D(128, 3, 1, 1, conv5_1_w, conv5_1_b, GPUMode);
    conv_5_2 = new Conv2D(128, 3, 1, 1, conv5_2_w, conv5_2_b, GPUMode);
    maxPool_3 = new MaxPool2D(3, 3, 2);
    fc_1 = new FC(4096, dense1_w, dense1_b, GPUMode);
    fc_2 = new FC(4096, dense2_w, dense2_b, GPUMode);
    fc_3 = new FC(1000, dense3_w, dense3_b, GPUMode);
    softmax = new Softmax();
}

void AlexNet::runClassify(std::vector<std::string> imagePaths) {
    vector<ThreeDMatrix> imageMatrices;
    convertImages(imagePaths, imageMatrices);

    for (int i = 0; i < imageMatrices.size(); i++) {
        conv_1->forward(imageMatrices[i], conv_1_output);
        reLU->forward(conv_1_output, reLU_1_output);

        maxPool_1->forward(reLU_1_output, maxPool_1_output);
        norm_1->forward(maxPool_1_output, norm_1_output);

        splitTensor(norm_1_output, norm_1_1_output, norm_1_2_output);
        conv_2_1->forward(norm_1_1_output, conv_2_1_output);
        conv_2_2->forward(norm_1_2_output, conv_2_2_output);
        mergeTensors(conv_2_1_output, conv_2_2_output, conv_2_output);
        reLU->forward(conv_2_output, reLU_2_output);

        maxPool_2->forward(reLU_2_output, maxPool_2_output);
        norm_2->forward(maxPool_2_output, norm_2_output);

        conv_3->forward(norm_2_output, conv_3_output);
        reLU->forward(conv_3_output, reLU_3_output);

        splitTensor(reLU_3_output, reLU_3_1_output, reLU_3_2_output);
        conv_4_1->forward(reLU_3_1_output, conv_4_1_output);
        conv_4_2->forward(reLU_3_2_output, conv_4_2_output);
        mergeTensors(conv_4_1_output, conv_4_2_output, conv_4_output);
        reLU->forward(conv_4_output, reLU_4_output);

        splitTensor(reLU_4_output, reLU_4_1_output, reLU_4_2_output);
        conv_5_1->forward(reLU_4_1_output, conv_5_1_output);
        conv_5_2->forward(reLU_4_2_output, conv_5_2_output);
        mergeTensors(conv_5_1_output, conv_5_2_output, conv_5_output);
        reLU->forward(conv_5_output, reLU_5_output);

        maxPool_3->forward(reLU_5_output, maxPool_3_output);

        fc_1->forward(maxPool_3_output, fc_1_output);
        reLU->forward(fc_1_output, reLU_6_output);
        fc_2->forward(reLU_6_output, fc_2_output);
        reLU->forward(fc_2_output, reLU_7_output);
        fc_3->forward(reLU_7_output, fc_3_output);
        reLU->forward(fc_3_output, reLU_8_output);

        softmax->apply(reLU_8_output, softmax_output);
        setResults();
    }
}

void AlexNet::splitTensor(ThreeDMatrix &input, ThreeDMatrix &output_1, ThreeDMatrix &output_2) {
    int inputNumChannels = input.rows();
    int inputNumRows = input(0).rows();
    int inputNumCols = input(0).cols();

    int outputNumChannels = inputNumChannels / 2;
    int outputNumRows = inputNumRows;
    int outputNumCols = inputNumCols;

    //resize both output matrices
    output_1.resize(outputNumChannels);
    output_2.resize(outputNumChannels);
    for (int i = 0; i < outputNumChannels; i++) {
        output_1(i).resize(outputNumRows, outputNumCols);
        output_2(i).resize(outputNumRows, outputNumCols);
    }

    // fill output_1
    for (int i = 0; i < outputNumChannels; i++) {
        for (int j = 0; j < outputNumCols; j++) {
            for (int k = 0; k < outputNumRows; k++) {
                output_1(i)(k, j) = input(i)(k, j);
            }
        }
    }

    // fill output_2
    for (int i = 0; i < outputNumChannels; i++) {
        for (int j = 0; j < outputNumCols; j++) {
            for (int k = 0; k < outputNumRows; k++) {
                output_2(i)(k, j) = input(i + outputNumChannels)(k, j);
            }
        }
    }
}

void AlexNet::mergeTensors(ThreeDMatrix &input_1, ThreeDMatrix &input_2, ThreeDMatrix &output) {
    int input1NumChannels = input_1.rows();
    int input1NumRows = input_1(0).rows();
    int input1NumCols = input_1(0).cols();

    int input2NumChannels = input_1.rows();
    int input2NumRows = input_1(0).rows();
    int input2NumCols = input_1(0).cols();

    // For AlexNet these asserts should be true
    assert(input1NumChannels == input2NumChannels);
    assert(input1NumRows == input2NumRows);
    assert(input1NumCols == input2NumCols);

    //resize outputMatrix
    int outputNumChannels = input1NumChannels + input2NumChannels;
    output.resize(outputNumChannels);
    for (int i = 0; i < outputNumChannels; i++) {
        output(i).resize(input1NumRows, input1NumCols);
    }

    // copy input_1 into output
    for (int i = 0; i < input1NumChannels; i++) {
        for (int j = 0; j < input1NumCols; j++) {
            for (int k = 0; k < input1NumRows; k++) {
                output(i)(k, j) = input_1(i)(k, j);
            }
        }
    }

    // copy input_2 into output
    for (int i = 0; i < input2NumChannels; i++) {
        for (int j = 0; j < input2NumCols; j++) {
            for (int k = 0; k < input2NumRows; k++) {
                output(i + input1NumChannels)(k, j) = input_2(i)(k, j);
            }
        }
    }
}

void AlexNet::initLabels() {
    //get classes
    ifstream file;
    file.open(LABELS_PATH);
    if (!file) {
        string msg("Es wurde keine Labels gefunden");
        throw (ReadException(msg));
    }
    int i = 0;
    for (string line; getline(file, line);) {
        classes[i] = line;
        i += 1;
    }
}

void AlexNet::convertImages(std::vector<std::string> &imagePaths, std::vector<ThreeDMatrix> &imageMatrices) {
    imageMatrices.resize(imagePaths.size());

    for (int i = 0; i < imagePaths.size(); i++) {
        Mat image = imread(imagePaths[i]); // automatically replicates channels if grayscale
        if(image.empty()) {
            string msg("Das eingelesene Bild ist beschädigt!");
            throw (ReadException(msg));
        }

        int preResizeHeight = image.rows;
        int preResizeWidth = image.cols;

        // Resize if needed
        Mat resizedImage;
        if (preResizeHeight != IMAGE_SIZE || preResizeWidth != IMAGE_SIZE) {
            double ratio = (double) IMAGE_SIZE / max(preResizeHeight, preResizeWidth);
            int newHeight = (int) (ratio * preResizeHeight);
            int newWidth = (int) (ratio * preResizeWidth);

            resize(image, resizedImage, Size(newWidth, newHeight));
        }
        else {
            resizedImage = image;
        }

        int afterResizeHeight = resizedImage.rows;
        int afterResizeWidth = resizedImage.cols;

        // Pad if needed
        Mat paddedImage;
        if (afterResizeHeight != IMAGE_SIZE || afterResizeWidth != IMAGE_SIZE) {
            int heightDelta = IMAGE_SIZE - afterResizeHeight;
            int widthDelta = IMAGE_SIZE - afterResizeWidth;
            int topPad = heightDelta / 2;
            int bottomPad = heightDelta - topPad;
            int leftPad = widthDelta / 2;
            int rightPad = widthDelta - leftPad;
            Scalar color;
            color = Scalar(0, 0, 0);
            copyMakeBorder(resizedImage, paddedImage, topPad, bottomPad, leftPad, rightPad, BORDER_CONSTANT, color);
        }
        else {
            paddedImage = resizedImage;
        }
        /*
        cv::namedWindow("resize", WINDOW_AUTOSIZE );
        cv::imshow("resize", paddedImage);
        waitKey(0);*/

        assert(paddedImage.rows == IMAGE_SIZE);
        assert(paddedImage.cols == IMAGE_SIZE);
        assert(paddedImage.channels() == IMAGE_CHANNELS);

        // Convert image to ThreeDMatrix
        ThreeDMatrix imageMatrix;
        imageMatrix.resize(3);
        imageMatrix(0).resize(IMAGE_SIZE, IMAGE_SIZE);
        imageMatrix(1).resize(IMAGE_SIZE, IMAGE_SIZE);
        imageMatrix(2).resize(IMAGE_SIZE, IMAGE_SIZE);

        for (int i = 0; i < IMAGE_SIZE; ++i) {
            for (int j = 0; j < IMAGE_SIZE; ++j) {
                for (int colour = 0; colour < IMAGE_CHANNELS; ++colour) {
                    Vec3b intensity = paddedImage.at<Vec3b>(i, j);
                    imageMatrix(colour)(i, j) = intensity.val[2 - colour]; // OpenCV delivers bgr
                }
            }
        }
        imageMatrices[i] = imageMatrix;
    }
}

void AlexNet::setResults() {
    //get top 5 results
    float top[5];
    int index[5];
    string resultString = "";
    for (int j = 0; j < 5; j++) {
        top[j] = 0;
        index[j] = 0;
        for (int k = 0; k < 1000; k++) {
            if (softmax_output(k) > top[j]) {
                top[j] = softmax_output(k);
                index[j] = k;
                softmax_output(k) = 0;
            }
        }
        resultString += Platform::floatToPercent(top[j]);
        //resultString += to_string(top[j]);
        //resultString += "   ";
        resultString += classes[index[j]];
        resultString += '\n';
    }
    results->push_back(resultString);
}
