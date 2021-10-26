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
#include "fBaseObject.h"
#include "fExternalable.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fBaseTransportObject :
    public fBaseObject, public fExternalable {
  public:
    DLL fBaseTransportObject(void);
    virtual DLL ~fBaseTransportObject(void);
};

}
}
}
}
