//
// Created by dmitrii on 14.07.19.
//

#include "ModeUtil.h"

 const map<string, Mode> ModeUtil::stringModeClassify = {{"Optimal: Der optimale Modus, in dem so viel eigener Code benutzt wird, wie möglich. Es wird also die CPU benutzt. Ist AlexNet ausgewählt, wird zusätzlich die GPU verwendet.", Mode::OPTIMAL},
                                            {"Hohe Perfomance: Der schnellste und performanteste Modus, in dem alle verfügbaren heterogenen Plattformen benutzt werden.", Mode::HIGH_PERFOMANCE },
                                            {"Geringer Leistungsverbrauch: Der Modus mit der geringsten maximalen Last, in dem genau ein Intel Movidius Neural Compute Stick benutzt wird.", Mode::LOW_POWER},
                                            {"Hohe Energieeffizienz: Der Modus, in dem alle verfügbaren Intel Movidius Neural Compute Sticks benutzt werden.", Mode::ENERGY_EFFICIENT}};
 const map<string, Mode> ModeUtil::stringModeTraining = {{"Optimal: Der einzige und somit optimale Modus, in dem die CPU benutzt wird.", Mode::OPTIMAL}};

Mode ModeUtil::whichModeClassify(const string& mode) {
    for(auto const& pair: stringModeClassify) {
        if (pair.first.find(mode)== 0) {
            return stringModeClassify.at(pair.first);
        }
    }
}

Mode ModeUtil::whichModeTraining(const string& mode) {
    for(auto const& pair: stringModeTraining) {
        if (pair.first.find(mode)== 0) {
            return stringModeTraining.at(pair.first);
        }
    }
}

list<string> ModeUtil::getAllModesClassify() {
    list<string> allModes;
    for(auto const& pair: stringModeClassify) {
        allModes.push_front(pair.first);
    }

    return allModes;
}

list<string> ModeUtil::getAllModesTraining() {
    list<string> allModes;
    for(auto const& pair: stringModeTraining) {
        allModes.push_front(pair.first);
    }

    return allModes;
}
