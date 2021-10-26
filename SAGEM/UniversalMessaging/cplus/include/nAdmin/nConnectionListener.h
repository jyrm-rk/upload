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

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSubject;
}
}
namespace nirvana {
namespace nAdmin {

using namespace com::pcbsys::foundation::security;
using namespace com::pcbsys::foundation::fbase;

class nConnectionListener : public CountableObject {
  public:
    nConnectionListener(void);
    virtual ~nConnectionListener(void);

    virtual void newConnection(const std::string& connectionId, fSubject *pSubject, const std::string &filter, const std::string &protocol) = 0;
    virtual void delConnection(const std::string& connectionId, bool clientClose) = 0;
};

}
}
}
}
