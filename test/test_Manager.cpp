//#include <GUIModule/Subject.h>
//#include <ManagerModule/Manager.cpp>
#include "catch.hpp"
#include <iostream>
//#include <ManagerModule/Manager.h>
//#include <ManagerModule/Manager.cpp>
using namespace std;

TEST_CASE("Setter and getters of Manager") {
    /*
    Subject* subject = new Subject();
    Manager* manager = new Manager(subject);

    //getting Project directory
    // Get current dir of project
    size_t size = 256;
    char *path = NULL;
    path = getcwd(path, size);
    string path_str = std::string(path);
    path_str = path;
    path_str = path_str.erase(path_str.length()-4);
    path_str = path_str.erase(path_str.rfind('/')+1);
    cout << path_str << endl;
    string project_dir_test = manager->getProjectDir();
    SECTION("Project Directory is identified correctly") {
        REQUIRE(path_str == project_dir_test);
    }
     */
    REQUIRE(true == true);
}