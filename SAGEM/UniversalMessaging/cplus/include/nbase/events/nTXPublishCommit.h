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
#include "nTransactionalEvent.h"

#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

class nPublished;

class nTXPublishCommit :
    public nSynchronous {
  public:
    nTXPublishCommit(void);
    nTXPublishCommit(longlong channelId, std::list<nPublished*>& events, longlong txid,
                     longlong TTL, longlong publishTime);
    virtual ~nTXPublishCommit(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual longlong getChannelAttributesId();

  protected:
    longlong m_TXId;
    longlong m_channelAttributeId;
    longlong m_TTL;
    longlong m_publishTime;
    std::list<nPublished*> m_events;
};

}
}
}
}
}

