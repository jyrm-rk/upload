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

#include <list>
#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;

class nChannelStatus :
    public Observable, public fExternalable {
  public:
    nChannelStatus(void);
    virtual ~nChannelStatus(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);
    virtual longlong getUniqueId();
    virtual float getCacheHitRatio();
    virtual longlong getCurrentNoOfConnections();
    virtual longlong getTotalNoOfConnections();
    virtual longlong getLastEID();
    virtual longlong getCurrentNumberOfEvents();
    virtual longlong getTotalPublished();
    virtual longlong getUsedSpace();
    virtual longlong getTotalConsumed();
    virtual int getPercentageFreeInStore();
    virtual std::list<std::string> getJoins();
    virtual int getACLUpdateCount();

    longlong m_longData[11];

    static const int sId = 0;
    static const int sCurCon = 1;
    static const int sTotCon = 2;
    static const int sEvtPub = 3;
    static const int sNoEvt = 4;
    static const int sUsedSpace = 5;
    static const int sEvtCon = 6;
    static const int sLastEID = 7;
    static const int sACLChange = 8;
    static const int sPrcent = 9;
    static const int sRatio = 10;

  protected:
    std::list<std::string> m_joins;
};

}
}
}
}
