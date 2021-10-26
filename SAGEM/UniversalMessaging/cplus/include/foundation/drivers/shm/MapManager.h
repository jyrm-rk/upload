/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace shm {

using namespace com::pcbsys::foundation::fbase;

class DLL MapManager : public CountableObject {

  public:
    virtual void isIdle()=0;
    virtual void isActive()=0;
};
}
}
}
}
}
#endif

