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
    std::string PROJECT_DIR_temp = PROJECT_DIR+"/resources/";
    char * projectdir = new char [PROJECT_DIR_temp.length()+1];
    strcpy (projectdir, PROJECT_DIR_temp.c_str());
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (projectdir)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if ((ent->d_name[0] != '.') &&
            exists_file(PROJECT_DIR_temp+"/"+ent->d_name+"/"+ent->d_name+"_labels"+".txt") &&
                (exists_file(PROJECT_DIR_temp+"/"+ent->d_name+"/"+ent->d_name+"_model"+".pt") ||
                    exists_file(PROJECT_DIR_temp+"/"+ent->d_name+"/"+ent->d_name+"_model"+".h5") ||
                    exists_file(PROJECT_DIR_temp+"/"+ent->d_name+"/"+ent->d_name+"_model"+".bin")) ) {
                nets.push_front(ent->d_name);
            }
        }
        closedir (dir);
    } else {
        perror ("NO PROJECT DIRECTORY FOUND");
    }
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

    makeNameFromDir(imageDir);

    cout << imageDir << endl;

    bool found_imageDir = (std::find(defaultNeuralNets.begin(), defaultNeuralNets.end(), imageDir) != defaultNeuralNets.end());
    if (!found_imageDir) {
        defaultNeuralNets. push_back(imageDir);
    }
    //defaultNeuralNets. push_back(imageDir);
    this->neuralNet = imageDir;
    this->subject->setClassify(false);
    this->subject->informObservers();

}

void Manager::setProjectDir() {
    // Get current dir of project
    size_t size = 256;
    char *path = NULL;
    path = getcwd(path, size);
    string path_str = std::string(path);
    path_str = path;
    path_str = path_str.erase(path_str.length()-4);
    path_str = path_str.erase(path_str.rfind('/')+1);
    std::cout << path_str << std::endl;
    this->PROJECT_DIR = path_str;
}

bool Manager::exists_file(const std::string &name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

bool Manager::isRunnable() {
    whichFilesInResources();
    if (!net_labels) return false;

    switch (operationMode) {
        case Mode::OPTIMAL:
            if (neuralNet == "alexnet") {
                if (net_model_h5) {
                    return true;
                } else {
                    return false;
                }
            } else {
                if(net_model_pt) {
                    return  true;
                } else {
                    return false;
                }
            }
            break;
        case Mode::HIGH_PERFOMANCE:
            if (neuralNet == "alexnet") {
                if (net_model_h5 && net_model_bin && net_mapping && net_xml) {
                    return true;
                }
            } else {
                if(net_model_pt && net_model_bin && net_mapping && net_xml) {
                    return  true;
                } else {
                    return false;
                }
            }
            break;
        case Mode::LOW_POWER:
            if (net_model_bin && net_mapping && net_xml) {
                return true;
            } else {
                return false;
            }
            break;
        case Mode::ENERGY_EFFICIENT:
            if (net_model_bin && net_mapping && net_xml) {
                return true;
            } else {
                return false;
            }
            break;
    }
    return false;
}

void Manager::whichFilesInResources() {
    net_model_bin = false;
    net_model_pt = false;
    net_model_h5 = false;
    net_labels = false;
    net_mapping = false;
    net_xml = false;

    std::string PROJECT_DIR_temp = PROJECT_DIR+"resources/" + neuralNet +"/" +neuralNet;

    if (exists_file(PROJECT_DIR_temp+"_labels"+".txt")) {
        net_labels = true;
    }
    if (exists_file(PROJECT_DIR_temp+"_model"+".pt")) {
        net_model_pt = true;
    }
    if(exists_file(PROJECT_DIR_temp+"_model"+".h5")) {
        net_model_h5 = true;
    }
    if(exists_file(PROJECT_DIR_temp+"_model"+".bin")) {
        net_model_bin = true;
    }
    if(exists_file(PROJECT_DIR_temp+".xml")) {
        net_xml = true;
    }
    if (exists_file(PROJECT_DIR_temp+".mapping")) {
        net_mapping = true;
    }
}

void Manager::makeNameFromDir(std::string &imageDir) {
    //make name from imageDir for ParameterPanel
    if(imageDir[imageDir.size()-1] == '/') {
        imageDir.erase(imageDir.size()-1,1);
    }
    int i;
    for(i = imageDir.size()-1; imageDir[i] != '/'; i--) {}
    imageDir.erase(0, i+1);
}

