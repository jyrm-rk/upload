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

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {

using namespace fbase;

class fQueue : public NotifyableCountableObject {
  public:
    fQueue(void);
    virtual ~fQueue(void);

    virtual int size() = 0;
    virtual CountableObject* pop() = 0;
    virtual CountableObject* top() = 0;
    virtual void put(CountableObject *pObj) = 0;
};

}
}
}
}
