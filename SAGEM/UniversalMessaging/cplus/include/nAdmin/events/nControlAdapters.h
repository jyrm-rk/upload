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
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace com::pcbsys::nirvana::nbase::events;

class nControlAdapters :
    public nSynchronous {
  public:
    nControlAdapters(void);
    nControlAdapters(const std::string& name, int command);
    virtual ~nControlAdapters(void);

    virtual int getType();
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();

    virtual int getCommand();
    virtual const std::string getName();
    virtual void readExternal(fEventInputStream *pIstream);
    virtual void writeExternal(fEventOutputStream *pOstream);

    static const int STOP = 0;
    static const int START = 1;
    static const int PAUSE = 2;
    static const int RESUME = 3;
    static const int ERR = 4;

  private:
    std::string m_name;
    int m_command;
};

}
}
}
}
}
