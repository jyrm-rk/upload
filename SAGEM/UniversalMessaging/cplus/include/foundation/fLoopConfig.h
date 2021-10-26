/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fDriverConfig.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {

class fLoopConfig :
    public fDriverConfig {
  public:
    fLoopConfig(void);
    virtual ~fLoopConfig(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);
    virtual void readOldExternal(fEventInputStream *pEis);
    virtual void readOrigExternal(fEventInputStream *pEis);
};

}
}
}
}
}
