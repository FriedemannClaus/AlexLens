//
// Created by dmitrii on 14.07.19.
//

#include "ModeUtil.h"
 const map<string, Mode> ModeUtil::stringMode = {{"Hohe Energieeffizienz",       Mode::ENERGY_EFFICIENT},
                                            {"Geringer Leistungsverbrauch", Mode::LOW_POWER },
                                            {"Hohe Perfomance",             Mode::HIGH_PERFOMANCE},
                                            {"Optimal",                     Mode::OPTIMAL}};

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

