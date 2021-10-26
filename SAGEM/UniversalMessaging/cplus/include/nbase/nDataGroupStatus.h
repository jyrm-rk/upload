/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"
#include "fExternalable.h"
#include "Poco/Mutex.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;

class nBaseDataGroup;

class nDataGroupStatus : public Observable, fExternalable {
  public:
    nDataGroupStatus(void);
    nDataGroupStatus(nBaseDataGroup *pDg, bool bNewGrp = true);
    virtual ~nDataGroupStatus(void);

    static const unsigned char sId        = 0;
    static const unsigned char sCurCon    = 1;
    static const unsigned char sTotCon    = 2;
    static const unsigned char sEvtPub    = 3;
    static const unsigned char sNoEvt     = 4;
    static const unsigned char sUsedSpace = 5;
    static const unsigned char sEvtCon    = 6;
    static const unsigned char sLastEID   = 7;
    static const unsigned char sFanout    = 8;

    longlong	m_longData[9];

    void setUniqueID(longlong uniqueId);
    std::string tostring();
    longlong getCurrentNoOfConnections();
    longlong getTotalNoOfConnections();
    longlong getUniqueId();
    longlong getTotalPublished();
    longlong getUsedSpace();
    longlong getTotalConsumed();
    longlong getLastEID();
    longlong getCurrentNumberOfEvents();
    void updateEventsConsumed(longlong count);
    void incrementConnectionCount();
    void incrementPublishCount(int count);
    void incrementSubscribedCount(int count);
    void setLastEid(longlong eid);
    void setUsedSpace(longlong used);
    void setNumberOfEvents(longlong numEvents);
    void setFanoutLatency(longlong time);
    longlong getFanoutLatency();
    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);
    int getSize();
    bool hasChanged();
    void setChanged(bool bChanged);

  private:
    bool m_bHasChanged;
    Poco::Mutex m_syncMutex;
};

}
}
}
}
