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
#include "nNamedObject.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

using namespace client;

class nNamedObjectHelper :
    public nNamedObject {
  public:
    nNamedObjectHelper(const std::string& name, longlong eid, longlong id, bool persist, bool clusterWide, bool priority, bool shared);
    nNamedObjectHelper(const std::string& name, longlong eid, longlong id, bool persist, unsigned char val, longlong queueSize);
    virtual ~nNamedObjectHelper(void);

    DLL longlong getId();
};

}
}
}
}
}
