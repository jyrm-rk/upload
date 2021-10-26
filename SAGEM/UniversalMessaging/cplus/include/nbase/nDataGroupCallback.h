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
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;

class nDataGroupCallback {
  public:
    nDataGroupCallback(void);
    virtual ~nDataGroupCallback(void);

    virtual void execute(Object *pEvt) = 0;
    virtual void close() = 0;
};

}
}
}
}
