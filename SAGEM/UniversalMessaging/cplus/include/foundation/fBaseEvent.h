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
#include "fExternalable.h"
#include "fPrioritized.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fEventDictionary;
}
namespace io {

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::fbase::collections;

class fBaseEvent :
    public fExternalable, public fPrioritized, public fBase, public NotifyableCountableObject {
  public:
    DLL fBaseEvent(void);
    virtual DLL ~fBaseEvent(void);

    virtual bool isMarked() = 0;
    virtual void setMarked() = 0;
    virtual const std::string getTypeString() = 0;
    virtual int getId() = 0;
    virtual bool isSynchronous() = 0;
    virtual fEventDictionary* getDictionary();
};

}
}
}
}
