/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nRequestCallback.h"
#include "fBase.h"

#include <map>

#include "Poco/Mutex.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nClientChannelList;
namespace events {
class nEvent;
}
}
namespace client {

class nChannel;
class nSubscriptionAttributes;
class nSession;

using namespace nbase;
using namespace nbase::events;

class FindAndSubscribeCallback :
    public nRequestCallback {
  public:
    FindAndSubscribeCallback(nSession *pSession, std::map<longlong, nClientChannelList*> *pList);
    virtual ~FindAndSubscribeCallback(void);

    virtual void response(nEvent *pRequest, nEvent *pResponse);

  protected:
    nChannel **m_ppChannels;
    int m_nChannel;
    nSubscriptionAttributes **m_ppAttribs;
    int m_nAttrib;
    nSession *m_pSession;
    std::map<longlong, nClientChannelList*> *m_pChannelList;
    Poco::Mutex m_channelListLock;
//	Timer *m_pTimer;

    friend class nSession;
};

}
}
}
}
