//
// Created by viet on 01.09.19.
//

#include "GPUPlatform.h"
#include <sys/time.h>

GPUPlatform::GPUPlatform() {
    this->alexNet = new AlexNet(this->results, true);
    this->type = PlatformType::GPU;
    this->statistic.setEnergyConsum(18);
    this->statistic.setFLOPS(432);
}

void GPUPlatform::runClassify() {
    this->results.clear();

    struct timespec begin, finish;
    clock_gettime(CLOCK_MONOTONIC, &begin);
    alexNet->runClassify(this->imageNames);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    const float final_time = (finish.tv_sec - begin.tv_sec) + (finish.tv_nsec - begin.tv_nsec) / 1000000.0;
    this->imageNames.clear();
    this->statistic.setTotalInferenceTime(final_time);
    this->statistic.setAvgIterationTime(final_time/results.size());
}


void GPUPlatform::runTraining() {
    string str = "src/TrainingModule/TransferLearning.py";
    char fileName[this->project_dir.length()+str.length()];
    string fileNamePath = this->project_dir + str;

    strcpy(fileName, fileNamePath.c_str());
    /*
    FILE* fp;
    Py_Initialize();
    fp = _Py_fopen(fileName, "r");
    // Path of dataset
    char path[this->datasetPath.length()];
    strcpy(path, this->datasetPath.c_str());
    char* py_argv[] = {strdup(path)};
    wchar_t *w_py_argv[] = {Py_DecodeLocale(py_argv[0], NULL)};
    PySys_SetArgv(1, w_py_argv);
    PyRun_SimpleFile(fp, fileName);
    free(py_argv[0]);
    Py_Finalize();
*/

    //syscall variant start
    std::string command_str = "python3 ";
    command_str += fileNamePath + " ";
    command_str += this->datasetPath;
    const char *command = command_str.c_str();
    system(command);
    //syscall variant end
}