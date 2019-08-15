//
// Created by dmitrii on 7/20/19.
//

#ifndef ALEXLENS_IOBSERVER_H
#define ALEXLENS_IOBSERVER_H

/**
 * Abstract class IObserver. The observer of observer design pattern.
 */
class IObserver {
public:
    /**
     * Invoke the update methods on object.
     */
    virtual void invokeUpdate() {}

    /**
     * @return whether this tab is classify tab
     */
    virtual bool isClassifyTab() {}
};
#endif //ALEXLENS_IOBSERVER_H
