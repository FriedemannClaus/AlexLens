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
    string image_path = "../snail.jpg";
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
    float max1 = 0.1;
    int max1i;
    float max2 = 0.05;
    int max2i;
    float max3 = 0.025;
    int max3i;
    float max4 = 0.02;
    int max4i;
    float max5 = 0.015;
    int max5i;

    float total;
    for (int i = 0; i < 1000; ++i) {
//        cout << propabilities(i) << "; ";
//        if ((i % 10) == 9) {
//            cout << endl;
//        }
        total += propabilities(i);

        if(propabilities(i) >= max1) {
            max1 = propabilities(i);
            max1i = i;
        } else{
            if(propabilities(i) >= max2) {
                max2 = propabilities(i);
                max2i = i;
            } else {
                if(propabilities(i) >= max3) {
                    max3 = propabilities(i);
                    max3i = i;
                } else {
                    if (propabilities(i) >= max4) {
                        max4 = propabilities(i);
                        max4i = i;
                    } else {
                        if (propabilities(i) >= max5) {
                            max5 = propabilities(i);
                            max5i = i;
                        }
                    }
                }
            }
        }
    }

    //...and print them
    cout <<"It is category " << max1i + 1 << " with a value of " << max1 << endl;
    cout <<"It is category " << max2i + 1 << " with a value of " << max2 << endl;
    cout <<"It is category " << max3i + 1 << " with a value of " << max3 << endl;
    cout <<"It is category " << max4i + 1 << " with a value of " << max4 << endl;
    cout <<"It is category " << max5i + 1 << " with a value of " << max5 << endl;
    cout << "(Started counting at 1 not 0)" << endl;
    cout << "Values add up to a sum of " << total << endl;

    //Start the application
    QApplication a(argc, argv);
    Manager* manager = new Manager();
    MainWindow* w = new MainWindow(manager);
    w->show();

    return a.exec();
}