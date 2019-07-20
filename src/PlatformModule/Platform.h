//
// Created by dmitrii on 7/18/19.
//

#ifndef ALEXLENS_PLATFORM_H
#define ALEXLENS_PLATFORM_H

#include <iostream>
#include <list>
#include <string>
#include <vector>



class Platform {
public:
    virtual std::vector<std::string> runClassify(std::__cxx11::list<std::string> list);
};


#endif //ALEXLENS_PLATFORM_H