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
namespace drivers {
namespace configuration {
class fDriverConfig;
}
}
}
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace nbase::events;
using namespace foundation::drivers::configuration;

class nManageAdapters :
    public nSynchronous {
  public:
    nManageAdapters(void);
    nManageAdapters(fDriverConfig *pCfg, int command, int status);
    virtual ~nManageAdapters(void);

    virtual int getType();
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();

    virtual int getCommand();
    virtual int getStatus();
    virtual fDriverConfig* getConfig();
    virtual void readExternal(fEventInputStream *pIstream);
    virtual void writeExternal(fEventOutputStream *pOstream);

    static const int ADD = 0;
    static const int DEL = 1;
    static const int MOD = 2;

  private:
    int m_command;
    int m_status;
    fDriverConfig* m_pConfig;

};

}
}
}
}
}
