//
// Created by dmitrii on 7/20/19.
//

#ifndef ALEXLENS_SUBJECT_H
#define ALEXLENS_SUBJECT_H

#include "../GUIModule/IObserver.h"
#include <list>
#include <iostream>
using namespace std;

class Subject {
    list<IObserver*> observerList;

public:
    Subject() {}
    inline void attachObserver(IObserver* observer) {
        observerList.push_back(observer);
    }

    inline void informObservers() {
        for (auto observer:observerList) {
            observer->invokeUpdate();
        }
    }
};

#endif //ALEXLENS_SUBJECT_H
