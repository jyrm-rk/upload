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
namespace nbase {
class nBaseChannelAttributes;

namespace events {

class nTXIsCommitted :
    public nSynchronous {
  public:
    nTXIsCommitted(void);
    nTXIsCommitted(longlong id);
    virtual ~nTXIsCommitted(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    longlong getKey();
    bool isCommitted();
    bool isAborted();

    static const int ABORTED = 3;
    static const int COMMITTED = 2;
    static const int UNKNOWN = 1;

  private:
    longlong m_TXId;
    longlong m_TTL;
    int m_state;
};

}
}
}
}
}
