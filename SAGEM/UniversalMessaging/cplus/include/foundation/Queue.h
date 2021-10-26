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
#include "fQueue.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class CountableObject;
}
namespace collections {

using namespace fbase;

class fCircularBuffer;

class Queue :
    public fQueue {
  public:
    DLL Queue(void);
    DLL Queue(int initialSize);
    virtual ~Queue(void);

    virtual int size();
    virtual CountableObject* pop();
    virtual CountableObject* top();
    virtual void put(CountableObject *pObject);
    virtual int getType ();

  private:
    fCircularBuffer *m_pQueue;
};

}
}
}
}
