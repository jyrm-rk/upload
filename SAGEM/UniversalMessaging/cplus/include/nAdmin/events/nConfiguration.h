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
namespace configuration {
class fConfigObject;
}
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nbase {
namespace events {

using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::configuration;

class nConfiguration :
    public nSynchronous {
  public:
    nConfiguration(void);
    nConfiguration(int request);
    nConfiguration(int request, std::list<fConfigObject*>& newConfig);
    virtual ~nConfiguration(void);

    virtual std::list<fConfigObject*>& getConfigObjects();

    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);
    virtual const std::string getTypeString();
    virtual nEvent* createInstance();
    virtual int getType();

  private:
    void copyVector(std::list<fConfigObject*>& newConfig);

    std::list<fConfigObject*> m_configObjects;
};

}
}
}
}
}
