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
    setDefaultModes();
    setDefaultNeuralNets();
    this->subject = subject;
    Executor* executor = new Executor();
    this->executor = executor;
}

void Manager::setDefaultModes() {
    list<string> mods = ModeUtil::getAllModes();
    this->defaultModes = mods;
}

void Manager::setDefaultNeuralNets() {
    list<string> nets;
    //TODO
    //nets.push_front("AlexNet");
    //this->defaultNeuralNets = nets;
    this->defaultNeuralNets = Manager::findNeuralNets();
}

void Manager::runClassify() {
    this->results = executor->classify(imagePaths, operationMode, neuralNet);
    for (auto a: results) cout << a << endl;
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


