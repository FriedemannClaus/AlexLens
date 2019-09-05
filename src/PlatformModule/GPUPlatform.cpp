//
// Created by viet on 01.09.19.
//

#include "GPUPlatform.h"

GPUPlatform::GPUPlatform() {
    this->alexNet = new AlexNet(this->results, true);
    this->type = PlatformType::GPU;
    this->statistic.setEnergyConsum(20);
    this->statistic.setFLOPS(432);
}

void GPUPlatform::runClassify() {
    this->results.clear();
    const clock_t begin_time = clock();
    alexNet->runClassify(this->imageNames);
    const float final_time = float( clock () - begin_time )/CLOCKS_PER_SEC*10000;
    this->imageNames.clear();
    cout<<"gpu"<<endl;
    cout<<final_time<<endl;
    cout<<final_time/results.size()<<endl;
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