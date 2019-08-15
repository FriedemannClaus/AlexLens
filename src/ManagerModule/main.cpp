#include "GUIModule/mainwindow.h"
#include <QApplication>
#include<QFileDialog>
#include <fstream>
#include "Manager.h"
#include "TrainingModule/ITraining.h"
#include "../MathModule/Skalar.h"
#include "../NeuralNetModule/NeuralNet.h"
#include <Eigen/Core>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager* manager = new Manager();
    MainWindow* w = new MainWindow(manager);
    w->show();
    auto neuralNet = new NeuralNet();
    neuralNet->init();

    //load a cat image for testing
    Layer::ThreeDMatrix catMatrix;
    catMatrix.resize(3, 1);
    catMatrix(0, 0).resize(227, 227);
    catMatrix(1, 0).resize(227, 227);
    catMatrix(2, 0).resize(227, 227);

    //load the cat.jpg file
    ifstream inFile;
    inFile.open("../cat.jpg");

    if (!inFile) {
        cerr << "Unable to load cat-file.";
        exit(1);
    }
    for (int i = 0; i < 227; ++i) {
        for (int j = 0; j < 227; ++j) {
            for (int colour = 0; colour < 2; ++colour) {
      //          catMatrix(colour) (i, j) = inFile.imread(i, j, colour); // OpenCV could do that.
            }
        }
    }

    neuralNet->classify(catMatrix);

    return a.exec();
}
