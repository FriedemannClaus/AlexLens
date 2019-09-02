//
// Created by Viet Pham.
//

#include "CPUPlatform.h"

CPUPlatform::CPUPlatform() {
    this->alexNet = new AlexNet(this->results, false);
    this->type = PlatformType::CPU;
    this->statistic.setEnergyConsum(20);
    this->statistic.setFLOPS(19);
}


void CPUPlatform::runClassify() {
    this->results.clear();
    const clock_t begin_time = clock();
    alexNet->runClassify(this->imageNames);
    const float final_time = float( clock () - begin_time )/CLOCKS_PER_SEC*100;
    this->imageNames.clear();
    this->statistic.setTotalInferenceTime(final_time);
    this->statistic.setAvgIterationTime(final_time/results.size());
}


void CPUPlatform::runTraining() {
    //Py_SetProgramName(reinterpret_cast<const wchar_t *>(argv[0]));
    // Path of TransferLearning.py
    //char fileName[] = "/home/viet/CLionProjects/AlexLens/TransferLearning.py";
    string str = "src/TrainingModule/TransferLearning.py";
    char fileName[this->project_dir.length()+str.length()];
    string fileNamePath = this->project_dir + str;
    /*
    strcpy(fileName, fileNamePath.c_str());
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
    std::string command_str = "/home/dmitrii/anaconda3/bin/python ";
    command_str += fileNamePath + " ";
    command_str += this->datasetPath;
    const char *command = command_str.c_str();
    system(command);
    //syzscall variant end
}

