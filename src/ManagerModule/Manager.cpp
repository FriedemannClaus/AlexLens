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
    setProjectDir();
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
    std::string PROJECT_DIR_temp = PROJECT_DIR+"resources/";
    char * projectdir = new char [PROJECT_DIR_temp.length()+1];
    strcpy (projectdir, PROJECT_DIR_temp.c_str());
    DIR *dir;
    struct dirent *ent;
    std::cout << projectdir << std::endl;
    if ((dir = opendir (projectdir)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if ((ent->d_name[0] != '.') && exists_file(PROJECT_DIR_temp+"/"+ent->d_name+"/"+ent->d_name+"_labels"+".txt") && exists_file(PROJECT_DIR_temp+"/"+ent->d_name+"/"+ent->d_name+"_model"+".pt")) {
                nets.push_back(ent->d_name);
            }
        }
        closedir (dir);
    } else {
        perror ("NO PROJECT DIRECTORY FOUND");
    }
    //nets.push_front("alexnet");
    this->defaultNeuralNets = nets;
}

void Manager::runClassify() {

    this->results = executor->classify(imagePaths, operationMode, neuralNet, this->PROJECT_DIR);
    this->subject->setClassify(true);
    this->subject->informObservers();

}

void Manager::runTraining() {
    string imageDir = imagePaths.front();

    this->executor->train(imageDir, operationMode, neuralNet, this->PROJECT_DIR);

    //make name from imageDir for ParameterPanel
    if(imageDir[imageDir.size()-1] == '/') {
        imageDir.erase(imageDir.size()-1,1);
    }
    int i;
    for(i = imageDir.size()-1; imageDir[i] != '/'; i--) {}
    imageDir.erase(0, i+1);

    defaultNeuralNets.push_back(imageDir);
    this->neuralNet = imageDir;
    this->subject->setClassify(false);
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

void Manager::setProjectDir() {
    // Get current dir of project
    size_t size = 256;
    char *path = NULL;
    path = getcwd(path, size);
    cout << "hey: " << path << endl;
    string path_str = std::string(path);
    path_str = path;
    path_str = path_str.erase(path_str.rfind('/')+1);
    this->PROJECT_DIR = path_str;
    cout << "here" << path_str << endl;
}

bool Manager::exists_file(const std::string &name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}
