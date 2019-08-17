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

    cout << catMatrix(1)(226,226) << endl;
    cout << "Test-Image loaded correctly\n";



    neuralNet->init();
    neuralNet->classify(catMatrix);


    return a.exec();
}
