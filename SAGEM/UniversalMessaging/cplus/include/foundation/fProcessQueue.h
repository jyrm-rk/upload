/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"
#include "fBaseEvent.h"

#include "Poco/SynchronizedObject.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fQueueHandler;
class CountableObject;

class fProcessQueue : public Poco::SynchronizedObject {
  public:
    fProcessQueue(fQueueHandler *pHandler, int lowWaterMark, int highWaterMark);
    virtual ~fProcessQueue(void);

    virtual long size();
    virtual void close();
    virtual void push(fBaseEvent *pObject);
    virtual void push(fBaseEvent *pObject, bool notifyImmediatly);
    virtual bool isSuspended();
    virtual int length();

    int getLowWaterMark();
    int getHighWaterMark();

  protected:
    int m_lowWaterMark;
    int m_highWaterMark;

  private:
    fQueueHandler *m_pHandler;
};

}
}
}
}
