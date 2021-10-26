/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEvent.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

class nSynchronous :
    public nEvent {
  public:
    nSynchronous(int id = 0);
    virtual ~nSynchronous(void);

    virtual bool isSynchronous();
    int getRequestId();
    void setRequestId(int id);
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual bool isTypeSynchronous();
    void setSynchronous (bool flag);

  protected:
    bool m_bIsSync;
    int m_uniqueRequestId;

  private:
    static int m_sMyUniqueGenerator;
};

}
}
}
}
}
