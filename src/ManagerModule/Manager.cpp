//
// Created by dmitrii on 11.07.19.
//
#include <stdio.h>
#ifdef WINDOWS
#include <direct.h>
    #define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <string>
#include <iostream>
#include <dirent.h>
#include <regex>

#include "Manager.h"
#include "Executor.h"


Manager::Manager(Subject* subject) {
    setDefaultModesClassify();
    setDefaultModesTraining();
    setDefaultNeuralNets();
    this->subject = subject;
    Executor* executor = new Executor();
    this->executor = executor;
}

void Manager::setDefaultModesClassify() {
    list<string> mods = ModeUtil::getAllModesClassify();
    this->defaultModesClassify = mods;
}

void Manager::setDefaultModesTraining() {
    list<string> mods = ModeUtil::getAllModesTraining();
    this->defaultModesTraining = mods;
}


void Manager::setDefaultNeuralNets() {
    list<string> nets;
    nets.push_front("AlexNet");
    this->defaultNeuralNets = nets;
}

void Manager::runClassify() {

    this->results = executor->classify(imagePaths, operationMode, neuralNet);
    this->subject->informObservers();

}
list<string> Manager::findNeuralNets(){
    list<string> *nets = new list<string>;

    char cCurrentPath[FILENAME_MAX];
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        //TODO
        //throw ;
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

    DIR *dir;
    dirent *ent;

    string modelPath = "/../Model";
    string path = cCurrentPath + modelPath;
    int n = path.length();
    char charPath[n+1];
    strcpy(charPath, path.c_str());

    if ((dir = opendir (charPath)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if(ent->d_name[0] != '.')
                nets->push_front(ent->d_name);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        //TODO
        //throw error on not opening the directory
    }
    return *nets;
}
void Manager::runTraining() {


}