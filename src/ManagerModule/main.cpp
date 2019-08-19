#include "GUIModule/mainwindow.h"
#include <QApplication>
#include<QFileDialog>
#include <fstream>
#include "Manager.h"
#include "TrainingModule/ITraining.h"
#include "../MathModule/Skalar.h"
#include "../NeuralNetModule/NeuralNet.h"
#include <Eigen/Core>
//OpenCV for loading the image
#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
int main(int argc, char *argv[])
{
    //load a test image
    Layer::ThreeDMatrix imageMatrix;
    imageMatrix.resize(3);
    imageMatrix(0).resize(227, 227);
    imageMatrix(1).resize(227, 227);
    imageMatrix(2).resize(227, 227);

    // load image with opencv and transform it to a ThreeDMatrix
    string image_path = "../cat.jpg";
    Mat image = imread(image_path);

    for (int i = 0; i < 227; ++i) {
        for (int j = 0; j < 227; ++j) {
            for (int colour = 0; colour < 3; ++colour) {
                Vec3b intensity = image.at<Vec3b>(i, j);
                imageMatrix(colour) (i, j) = intensity.val[2 - colour]; // OpenCV delivers bgr
            }
        }
    }
    cout<< " r:" << imageMatrix(0)(0, 0) << " g:" << imageMatrix (1)(226, 0) << " b:" << imageMatrix (2)(226, 226);
    cout << "Test-Image loaded correctly\n";

    //Classify the image
    auto neuralNet = new NeuralNet();
    neuralNet->init();
    Layer::Vector propabilities;
    neuralNet->classify(imageMatrix, propabilities);

    // Take the 5 highest values of the result (and calculate total)...
    Layer::Vector propabilitiesCopy;
    propabilitiesCopy.resize(1000);

    float total = 0;
    for (int i = 0; i < 1000; i++) {
        total += propabilities(i);
        propabilitiesCopy(i) = propabilities(i);
    }

    Layer::Vector floats;
    floats.resize(5);

    Layer::Vector indices;
    indices.resize(5);

    for (int i = 0; i < 5; i++) {
        floats(i) = 0;
        for (int j = 0; j < 1000; j++) {
            if (propabilitiesCopy(j) > floats(i)) {
                floats(i) = propabilitiesCopy(j);
                indices(i) = j;
            }
        }
        propabilitiesCopy(indices(i)) = 0;
    }

    //...and print them
    cout <<"It is category " << indices(0) + 1 << " with a value of " << floats(0) << endl;
    cout <<"It is category " << indices(1) + 1 << " with a value of " << floats(1) << endl;
    cout <<"It is category " << indices(2) + 1 << " with a value of " << floats(2) << endl;
    cout <<"It is category " << indices(3) + 1 << " with a value of " << floats(3) << endl;
    cout <<"It is category " << indices(4) + 1 << " with a value of " << floats(4) << endl;
    cout << "(Started counting at 1 not 0)" << endl;
    cout << "Values add up to a sum of " << total << endl;

    //delete what we have used
    delete neuralNet;

    //Start the application
    QApplication a(argc, argv);
//    Manager* manager = new Manager();
//    MainWindow* w = new MainWindow(manager);
//    w->show();

    return a.exec();
}