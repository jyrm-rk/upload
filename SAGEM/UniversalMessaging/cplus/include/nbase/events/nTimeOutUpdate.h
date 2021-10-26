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

class nTimeOutUpdate :
    public nEvent {
  public:
    nTimeOutUpdate(void);
    virtual ~nTimeOutUpdate(void);

    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();

    void fromBytes(unsigned char *pBuffer, int length);
    long getEventWait();
    long getTxPubWait();
    int getLowWater();
    int getHighWater();
    int getAccessWaitLimit();
    int getPushWaitLimit();
    int getBlockLimit();
    long getKaWait();

  private:
    long m_eventWait;
    long m_txPubWait;
    int m_lowWater;
    int m_highWater;
    int m_accessWait;
    int m_pushWait;
    int m_blockWait;
    long m_discWait;
    long m_kaWait;
};

}
}
}
}
}
