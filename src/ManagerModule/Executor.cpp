//
// Created by dmitrii on 7/18/19.
//

#include "../PlatformModule/ModeUtil.h"
#include "Executor.h"
#include <thread>



std::list<std::exception_ptr> Executor::exceptionPointers; //multithreading bufffer for exceptions

/**
 * Thread function for starting all claffifications
 * @param platform
 */
void thrFunction(Platform *platform) {
    //catching all exceptions of different threads in multithreading buffer
    try {
        platform->runClassify();
    } catch (exception & e) {
        cout << "Caught Exception in Thread function" << endl;
        Executor::exceptionPointers.push_back(std::current_exception());
    }
}

vector<string> Executor::classify(list<string> imagePaths, Mode mode, string neuralNet, string project_dir) {
    this->platformManager->setMode(mode);
    this->platformManager->setNeuralNet(neuralNet);
    if ((platformManager->getNumberOfSticks() == 0) && (mode == Mode::LOW_POWER || mode == Mode::ENERGY_EFFICIENT)){
        string msg("Es ist kein Stick angeschlossen");
        throw (StickException(msg));
    }

    list<Platform*> platforms = platformManager->getAvailablePlatforms();
    for(Platform* platform:platforms) {
        platform->setProjectDir(project_dir);
        platform->setNeuralNet(neuralNet);

    }

    //splitting all image paths between platforms
    int num_platforms = platforms.size();
    int num_imagePaths = imagePaths.size();
    list<string> split[num_platforms];
    for (int i = 0; i < num_platforms; i++) {
        list<string> list;
        split[i] = list;
    }

    int i = 0;
    int j = 0;
    int avg_rate = num_imagePaths / num_platforms;
    if ((num_imagePaths % num_platforms) != 0) avg_rate++;
    for (auto path:imagePaths) {
        split[i].push_back(path);
        j++;
        if (j >= avg_rate) {
            num_platforms -= 1;
            num_imagePaths -= j;
            if (num_imagePaths == 0) break;
            avg_rate = (int) num_imagePaths / num_platforms;
            if ((num_imagePaths % num_platforms) != 0) avg_rate++;
            j = 0;
            i++;
        }
    }

    num_platforms = platforms.size();
    num_imagePaths = imagePaths.size();

    i=0;
    for(Platform* platform:platforms) {
        platform->setImagePaths(split[i]);
        i++;
        if (i==num_platforms) break;
    }

    //starting threads
    vector<thread> threads;
    for (Platform *platform:platforms) {
        if (platform->getSizeOgImagePath() == 0) continue;
        thread thr(thrFunction, platform);
        threads.push_back(move(thr));
    }

    //joining all threads
    for (auto& t:threads) {
        t.join();
    }

    //throwing exception of multithreading buffer
    for (auto it = Executor::exceptionPointers.begin(); it != Executor::exceptionPointers.end(); ++it) {
        if (*it) {
            try {
                std::rethrow_exception(*it);
            } catch (const std::exception &e) {
                cout << "Caught exception in Executor, size of Thread buffer" << exceptionPointers.size() << endl;
                Executor::exceptionPointers.erase(it--);
                platformManager->clearAllImagePaths();
                Executor::exceptionPointers.clear();
                //TODO
                //delete this->platformManager;
                //this->platformManager = new PlatformManager();
                throw;
            }
        }
    }

    //joining all results into one vector
    vector<string> results;
    results.reserve(num_imagePaths);
    results.clear();
    for(Platform* platform:platforms) {
        vector<string> platformResults = platform->getResults();
        results.insert(results.end(), platformResults.begin(), platformResults.end());
    }


    return results;


}

Executor::Executor() {
    this->platformManager = new PlatformManager();
}

void Executor::train(string dirPath, Mode mode, string neuralNet, string project_dir) {
    this->platformManager->setMode(mode);
    this->platformManager->setNeuralNet(neuralNet);
    list<Platform*> platforms = platformManager->getAvailablePlatforms();
    for (auto platform:platforms) {
        platform->setDatasetPath(dirPath);
        platform->setProjectDir(project_dir);
        platform->setNeuralNet(neuralNet);
        platform->runTraining();
    }
}
