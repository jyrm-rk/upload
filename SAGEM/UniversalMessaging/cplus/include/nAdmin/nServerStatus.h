/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fExternalable.h"
#include "fBase.h"

#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fEventDictionary;
}
}
namespace nirvana {
namespace nbase {
class nChannelStatus;
class nConnectionStatus;
class nBaseInterfaceStatus;
}
namespace nAdmin {

using namespace foundation::fbase;
using namespace nbase;

class nServerStatus :
    public fExternalable, public CountableObject {
  public:
    nServerStatus(void);
    virtual ~nServerStatus(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);

    virtual fEventDictionary* getThreadPoolData();
    virtual longlong getTotalPublishes();
    virtual longlong getTotalSubscriptions();
    virtual longlong getTotalConnections();
    virtual longlong getTotalMemory();
    virtual longlong getFreeMemory();
    virtual std::list<nConnectionStatus*>& getConnectionStatus();
    virtual std::list<nBaseInterfaceStatus*>& getInterfaceStatus();
    virtual std::list<nChannelStatus*>& getChannelStatus();
    virtual int getNoThreads();
    virtual time_t getStartTime();				// TODO: time_t? milliseconds?
    virtual time_t getDate();
    virtual int getTotalRealms();

  private:
    fEventDictionary *m_pData;
    std::list<nChannelStatus*> m_channelStatus;
    std::list<nConnectionStatus*> m_connectionStatus;
    std::list<nBaseInterfaceStatus*> m_interfaceStatus;

    static const std::string sThreadPools;
    static const std::string sTotMem;
    static const std::string sFreeMem;
    static const std::string sThreads;
    static const std::string sName;
    static const std::string sTotCon;
    static const std::string sTotPub;
    static const std::string sTotSub;
    static const std::string sDate;
    static const std::string sStart;
    static const std::string sAclCount;
    static const std::string sRealmCount;
};

}
}
}
}
