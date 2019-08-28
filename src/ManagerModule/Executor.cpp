//
// Created by dmitrii on 7/18/19.
//

#include "../PlatformModule/ModeUtil.h"
#include "Executor.h"
#include <thread>


void thrFunction(Platform *platform) {
    platform->runClassify();
}

vector<string> Executor::classify(list<string> imagePaths, Mode mode, string neuralNet, string project_dir) {

    this->platformManager->setMode(mode);
    this->platformManager->setNeuralNet(neuralNet);

    list<Platform*> platforms = platformManager->getAvailablePlatforms();
    for(Platform* platform:platforms) {
        platform->setProjectDir(project_dir);
        platform->setNeuralNet(neuralNet);

    }

    //platforms.front()->setNeuralNet(neuralNet);

    //splitting all image paths between platforms
    int num_platforms = platforms.size();
    int num_imagePaths = imagePaths.size();
    list<string> split[num_platforms];
    for (int i = 0; i < num_platforms; i++) {
        list<string> list;
        split[i] = list;
    }

    int i = 0;
    for (auto path:imagePaths) {
        split[i].push_back(path);
        i++;
        if (i == num_platforms) i -= num_platforms;
    }

    i=0;
    for(Platform* platform:platforms) {
        platform->setImagePaths(split[i]);
        i++;
        if (i==num_platforms) break;
    }

    //starting threads
    vector<thread> threads;
    for(Platform* platform:platforms) {
        thread thr(thrFunction, platform);;
        threads.push_back(move(thr));
    }

    //joining all threads
    for (auto& t:threads) {
        t.join();
    }

    //joining all results into one vector
    vector<string> results;
    results.reserve(num_imagePaths);
    results.clear();
    for(Platform* platform:platforms) {
        vector<string> platformResults = platform->getResults();
        results.insert(results.end(), platformResults.begin(), platformResults.end());
    };

    return results;

}

Executor::Executor() {
    this->platformManager = new PlatformManager();
}

void Executor::train(string dirPath, Mode mode, string neuralNet, string project_dir) {
    this->platformManager->setMode(mode);
    list<Platform*> platforms = platformManager->getAvailablePlatforms();
    for (auto platform:platforms) {
        platform->setDatasetPath(dirPath);
        platform->setProjectDir(project_dir);
        platform->runTraining();
    }
}
