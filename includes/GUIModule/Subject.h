//
// Created by dmitrii on 7/20/19.
//

#ifndef ALEXLENS_SUBJECT_H
#define ALEXLENS_SUBJECT_H

#include "../GUIModule/IObserver.h"
#include <list>

using namespace std;

/**
 * Class Subject. The subject of observer design pattern.
 */
class Subject {
    list<IObserver*> observerList; /// List of all observers

private:
    bool classifyTab = true; /// bool flag for tabs

public:
    /**
     * Constructor for class Subject.
     */
    Subject() {}

    /**
     * Adds an new observer to list of observers.
     * @param observer
     */
    inline void attachObserver(IObserver* observer) {
        observerList.push_back(observer);
    }



    /**
     * Setter for differ observers for classification and training
     * @param flag flag to set
     */
    inline void setClassify(bool flag){
        this->classifyTab = flag;
    }
    /**
     * Inform the observers of the objects changes.
     */
    inline void informObservers() {
        for (auto observer:observerList) {
            if (observer->isClassifyTab() == this->classifyTab ) observer->invokeUpdate();
        }
    }
};

#endif //ALEXLENS_SUBJECT_H
