//#include <GUIModule/Subject.h>
//#include <ManagerModule/Manager.cpp>
#include "catch.hpp"
#include <iostream>
//#include <ManagerModule/Manager.h>
#include <ManagerModule/Manager.cpp>
#include <PlatformModule/Mode.h>
using namespace std;

TEST_CASE("Manager: Setters and Getters") {

    Subject* subject = new Subject();
    Manager* manager = new Manager(subject);

    //getting Project directory
    // Get current dir of project
    size_t size = 256;
    char *path = NULL;
    path = getcwd(path, size);
    string path_str = std::string(path);
    path_str = path;
    size_t pos = path_str.find("/AlexLens/");
    path_str = path_str.erase(pos + 10);

    string project_dir_test = manager->getProjectDir();
    cout << project_dir_test << endl;
    SECTION("Project Directory is identified correctly") {
        REQUIRE(path_str == project_dir_test);
    }

    /*manager->addImage(path_str + "resources/testimages/bernese.jpg");
    manager->setMode(Mode::OPTIMAL);
    manager->setNeuralNet("alexnet");
    manager->runClassify();
    string rightResult = "82.73% Bernese mountain dog\n"
                         "2.21% Appenzeller\n"
                         "1.03% cocker spaniel\n"
                         "0.87% English springer spaniel\n"
                         "0.86% EntleBucher\n";
    SECTION("Classification Test 1 image") {
       REQUIRE(manager->getResults()[0] == rightResult);
    }*/
    manager->addImage(path_str + "resources/testimages/cat.jpg");

    manager->setNeuralNet("googlenet");
    manager->runClassify();
    string rightResult1 = "67.75% tabby cat\n"
                          "14.18% tiger cat\n"
                          "11.84% Egyptian cat\n"
                          "1.47% lynx, catamount\n"
                          "1.06% Persian cat\n";
    string rightResult2 = "78.77% Bernese mountain dog\n"
                          "5.13% Appenzeller\n"
                          "4.22% Greater Swiss Mountain dog\n"
                          "2.81% EntleBucher\n"
                          "0.36% English springer spaniel\n";

    SECTION("Classification Test batch 2 the 1st image") {
        REQUIRE((manager->getResults()[0] == rightResult1));
    }
    SECTION("Classification Test batch 2 the 2nd image") {
        REQUIRE((manager->getResults()[1] == rightResult2));
    }
    

}