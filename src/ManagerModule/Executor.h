//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_EXECUTOR_H
#define ALEXLENS_EXECUTOR_H

#include <string>
#include <list>
#include "../PlatformModule/Mode.h"

#include <iostream>
#include <vector>
//#include "../../includes/GUIModule/outputclassifypanel.h"

using namespace std;


class Executor {

public:
    list<string> imagePaths;
    //OutputClassifyPanel* panel;

    //inline Subject* getSubject() { return this->subject;}

    Executor();

    //static void setOutputPanel(OutputClassifyPanel* panel) {
   //     Executor::panel=panel;
   // }


    vector<string> classify(list<string> imagePaths, Mode mode, string neuralNet);
    void train(list<string> trainPaths, Mode mode, string neuralNet);

};


#endif //ALEXLENS_EXECUTOR_H