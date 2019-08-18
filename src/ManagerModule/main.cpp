#include "GUIModule/mainwindow.h"
#include <QApplication>
#include<QFileDialog>
#include <fstream>
#include "Manager.h"
#include "TrainingModule/ITraining.h"
#include "../MathModule/Skalar.h"
#include "../NeuralNetModule/NeuralNet.h"
#include <Eigen/Core>
//OpenCV for the Cat-Image
#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager* manager = new Manager();
    MainWindow* w = new MainWindow(manager);
    w->show();
    auto neuralNet = new NeuralNet();

    //load a cat image for testing
    Layer::ThreeDMatrix catMatrix;
    catMatrix.resize(3);
    catMatrix(0).resize(227, 227);
    catMatrix(1).resize(227, 227);
    catMatrix(2).resize(227, 227);

//    //load the cat.jpg file
//    ifstream inFile;
//    inFile.open("../cat.jpg");
//
//    if (!inFile) {
//        cerr << "Unable to load cat-file.";
//        exit(1);
//    }

    // load image with opencv and transform
    string image_path = "../cat.jpg";
    Mat image = imread(image_path);
    //cvtColor(image, image, COLOR_BGR2RGB);



    for (int i = 0; i < 227; ++i) {
        for (int j = 0; j < 227; ++j) {
            for (int colour = 0; colour < 2; ++colour) {
                Vec3b intensity = image.at<Vec3b>(i, j);
                catMatrix(colour) (i, j) = intensity.val[2 - colour]; //bgr: b = 0
            }
        }
    }

    cout << "Test-Image loaded correctly\n";



    neuralNet->init();
    Layer::Vector propabilities;
    neuralNet->classify(catMatrix, propabilities);

    cout << "Result: ";
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
    for (int i = 0; i < 1000; ++i) {
        cout << propabilities(i) << "; ";
        if ((i % 10) == 9) {
            cout << endl;
        }

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

    cout <<"It is category " << max1i + 1 << " with a value of " << max1 << endl;
    cout <<"It is category " << max2i + 1 << " with a value of " << max2 << endl;
    cout <<"It is category " << max3i + 1 << " with a value of " << max3 << endl;
    cout <<"It is category " << max4i + 1 << " with a value of " << max4 << endl;
    cout <<"It is category " << max5i + 1 << " with a value of " << max5 << endl;
    cout << "(Started counting at 1 not 0)" << endl;

    return a.exec();
}