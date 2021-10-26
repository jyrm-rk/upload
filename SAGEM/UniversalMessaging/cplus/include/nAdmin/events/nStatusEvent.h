/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nPublished.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace nbase::events;

class nStatusEvent :
    public nPublished {
  public:
    nStatusEvent(void);
    virtual ~nStatusEvent(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
};

}
}
}
}
}
