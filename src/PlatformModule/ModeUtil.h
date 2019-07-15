//
// Created by dmitrii on 14.07.19.
//

#ifndef ALEXLENS_MODEUTIL_H
#define ALEXLENS_MODEUTIL_H

#include "Mode.h"
#include <map>
#include <iterator>
#include <string>

using namespace std;

class ModeUtil {
private:
    static const map<string, Mode> stringMode;
public:
    static Mode whichMode(const string &mode);
};


#endif //ALEXLENS_MODEUTIL_H
