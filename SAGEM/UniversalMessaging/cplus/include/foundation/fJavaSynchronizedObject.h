/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FJAVASYNCHRONIZEDOBJECT_H
#define	FJAVASYNCHRONIZEDOBJECT_H
#include "Poco/SynchronizedObject.h"
#include "fBase.h"
#include <iostream>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fJavaSynchronizedObject : public Poco::SynchronizedObject {

  public:
    fJavaSynchronizedObject():Poco::SynchronizedObject() {}

    virtual ~fJavaSynchronizedObject() {}

    void wait() const {
        unlock(); // Unlock prior to entering the wait to allow other threads in
        try {
            Poco::SynchronizedObject::wait();
        } catch(Poco::Exception timeout) {}
        lock(); // Ensure we are locked before we exit
    }

    void wait(long milliseconds) const {
        unlock(); // Unlock prior to entering the wait to allow other threads in
        try {
            Poco::SynchronizedObject::wait(milliseconds);
        } catch(Poco::Exception timeout) {}
        lock(); // Ensure we are locked before we exit
    }

};

}
}
}
}
#endif	/* FJAVASYNCHRONIZEDOBJECT_H */

