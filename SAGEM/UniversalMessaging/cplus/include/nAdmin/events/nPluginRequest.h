/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSynchronous.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nbase {
class nPluginDetails;

namespace events {

using namespace foundation::io;

class nPluginRequest :
    public nSynchronous {
  public:
    nPluginRequest(void);
    virtual ~nPluginRequest(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);
    virtual int getType();

    virtual std::list<nPluginDetails*>& getConfiguration();

  private:
    std::list<nPluginDetails*> m_configurations;
};

}
}
}
}
}
