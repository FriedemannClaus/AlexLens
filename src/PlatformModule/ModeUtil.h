//
// Created by dmitrii on 14.07.19.
//

#ifndef ALEXLENS_MODEUTIL_H
#define ALEXLENS_MODEUTIL_H

#include "Mode.h"
#include <map>
#include <iterator>
#include <string>
#include <list>

using namespace std;

/**
 * Class ModeUtil determines operations with Modes
 */
class ModeUtil {
private:
    static const map<string, Mode> stringModeClassify; /// Corresponding string or all classification modes
    static const map<string, Mode> stringModeTraining; /// Corresponding string or all training modes
public:
    /**
     * Returns corresponding equivalent in sting for classification modes
     * @param mode input mode
     * @return xorresponding string equivalent Mode
     */
    static Mode whichModeClassify(const string &mode);
    /**
     * Returns corresponding equivalent in sting for training modes
     * @param mode input mode
     * @return xorresponding string equivalent Mode
     */
    static Mode whichModeTraining(const string &mode);
    /**
     * Getter for all classification modes
     * @return all classification modes in string
     */
    static list<string> getAllModesClassify();
    /**
     * Getter for all training modes
     * @return all training modes in string
     */
    static list<string> getAllModesTraining();
};


#endif //ALEXLENS_MODEUTIL_H