//
// Created by dmitrii on 9/3/19.
//

#ifndef SRC_GUIMODULE_ALEXLENS_READEXCEPTION_H
#define SRC_GUIMODULE_ALEXLENS_READEXCEPTION_H

#include <iostream>
#include <exception>
#include <string>
using namespace std;
class StickException : public exception {
    string msg = "initial ReadException";
public:
    StickException(string& msg) {
        this->msg = msg;
    }
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};


#endif //SRC_GUIMODULE_ALEXLENS_READEXCEPTION_H
