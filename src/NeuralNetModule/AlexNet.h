//
// Created by Viet Pham.
//

#ifndef ALEXLENS_ALEXNET_H
#define ALEXLENS_ALEXNET_H

#include "AlexNetWeightParser.h"
#include "Conv2D.h"
#include "ReLU.h"
#include "MaxPool2D.h"
#include "Normalization.h"
#include "FC.h"
#include "Softmax.h"
#include <vector>

const int IMAGE_SIZE = 227; ///Input image size compatible with AlexNet Neural Net
const int IMAGE_CHANNELS = 3; ///Input image color depth compatible with AlexNet Neural Net
const std::string LABELS_PATH = "../../resources/alexnet/alexnet_labels.txt"; ///Path to the object class labels file

/**
 * Class contains all information about the AlexNet Neural Net
 */
class AlexNet {
public:
    /**
     * AlexNet class constructor which initialises the AlexNet Neural Net
     * @param results results vector of String where the output of the classification is saved
     * @param mode true if running on GPU, false if running on CPU
     */
    AlexNet(std::vector<std::string> &results, bool mode);

    /**
     * Image classification function which runs the input through the AlexNet
     * @param imagePaths vector of paths of inputted images
     */
    void runClassify(std::vector<std::string> imagePaths);

private:

    void initWeights(); ///Initialising AlexNet weights

    void initLayers(); ///Initialising AlexNet layers

    void initLabels(); ///Initialising object class labels

    void splitTensor(ThreeDMatrix &input, ThreeDMatrix &output_1, ThreeDMatrix &output_2); ///Split tensor objects before splitted convolutional layers

    void mergeTensors(ThreeDMatrix &input_1, ThreeDMatrix &input_2, ThreeDMatrix &output); ///Merge tensor objects before splitted convolutional layers

    void convertImages(std::vector<std::string> &imagePaths, std::vector<ThreeDMatrix> &imageMatrices); ///Convert images to tensor objects

    void setResults(); ///Set the results vector with classification results

    std::vector<std::string> *results; /// Results vector
    bool GPUMode; /// Operation mode

    std::string classes[1000]; ///Object classes

    // Weights and biases
    FourDMatrix conv1_w;
    Vector conv1_b;

    FourDMatrix conv2_1_w;
    Vector conv2_1_b;

    FourDMatrix conv2_2_w;
    Vector conv2_2_b;

    FourDMatrix conv3_w;
    Vector conv3_b;

    FourDMatrix conv4_1_w;
    Vector conv4_1_b;

    FourDMatrix conv4_2_w;
    Vector conv4_2_b;

    FourDMatrix conv5_1_w;
    Vector conv5_1_b;

    FourDMatrix conv5_2_w;
    Vector conv5_2_b;

    Matrix dense1_w;
    Vector dense1_b;

    Matrix dense2_w;
    Vector dense2_b;

    Matrix dense3_w;
    Vector dense3_b;


    // Layers
    ReLU *reLU;
    Conv2D *conv_1;
    MaxPool2D *maxPool_1;
    Normalization *norm_1;
    Conv2D *conv_2_1;
    Conv2D *conv_2_2;
    MaxPool2D *maxPool_2;
    Normalization *norm_2;
    Conv2D *conv_3;
    Conv2D *conv_4_1;
    Conv2D *conv_4_2;
    Conv2D *conv_5_1;
    Conv2D *conv_5_2;
    MaxPool2D *maxPool_3;
    FC *fc_1;
    FC *fc_2;
    FC *fc_3;
    Softmax *softmax;

    // Output matrices
    ThreeDMatrix conv_1_output;
    ThreeDMatrix reLU_1_output;
    ThreeDMatrix maxPool_1_output;
    ThreeDMatrix norm_1_output;
    ThreeDMatrix norm_1_1_output; // for splitted conv 2
    ThreeDMatrix norm_1_2_output; // for splitted conv 2
    ThreeDMatrix conv_2_1_output;
    ThreeDMatrix conv_2_2_output;
    ThreeDMatrix conv_2_output;
    ThreeDMatrix reLU_2_output;
    ThreeDMatrix maxPool_2_output;
    ThreeDMatrix norm_2_output;
    ThreeDMatrix conv_3_output;
    ThreeDMatrix reLU_3_output;
    ThreeDMatrix reLU_3_1_output;
    ThreeDMatrix reLU_3_2_output;
    ThreeDMatrix conv_4_1_output;
    ThreeDMatrix conv_4_2_output;
    ThreeDMatrix conv_4_output;
    ThreeDMatrix reLU_4_output;
    ThreeDMatrix reLU_4_1_output;
    ThreeDMatrix reLU_4_2_output;
    ThreeDMatrix conv_5_1_output;
    ThreeDMatrix conv_5_2_output;
    ThreeDMatrix conv_5_output;
    ThreeDMatrix reLU_5_output;
    ThreeDMatrix maxPool_3_output;
    ThreeDMatrix fc_1_output;
    ThreeDMatrix reLU_6_output;
    ThreeDMatrix fc_2_output;
    ThreeDMatrix reLU_7_output;
    ThreeDMatrix fc_3_output;
    ThreeDMatrix reLU_8_output;
    Vector softmax_output;
};


#endif //ALEXLENS_ALEXNET_H
