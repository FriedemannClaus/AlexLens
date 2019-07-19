//
// Created by dmitrii on 14.07.19.
//

#include "ModeUtil.h"
 const map<string, Mode> ModeUtil::stringMode = {{"Optimal",       Mode::OPTIMAL},
                                            {"Hohe Perfomance", Mode::HIGH_PERFOMANCE },
                                            {"Geringer Leistungsverbrauch",             Mode::LOW_POWER},
                                            {"Hohe Energieeffizienz",                     Mode::ENERGY_EFFICIENT}};

Mode ModeUtil::whichMode(const string& mode) {
    return stringMode.at(mode);
}

list<string> ModeUtil::getAllModes() {
    list<string> allModes;
    for(auto const& pair: stringMode) {
        allModes.push_back(pair.first);
    }

    return allModes;
}

