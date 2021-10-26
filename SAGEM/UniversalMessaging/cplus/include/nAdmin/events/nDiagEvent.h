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
namespace nAdmin {
namespace events {

using namespace nbase::events;
using namespace foundation::io;

class nDiagEvent :
    public nSynchronous {
  public:
    nDiagEvent(int command = sNoOp);
    virtual ~nDiagEvent(void);

    virtual void performRead(fEventInputStream *pOis);
    virtual void performWrite(fEventOutputStream *pOos);
    virtual const std::string getTypeString();
    virtual nEvent* createInstance();
    virtual int getType();

    virtual const std::string& getMessages();

    static const int sNoOp = 0;

  private:
    std::string m_msg;
    int m_diagCommand;
};

}
}
}
}
}
