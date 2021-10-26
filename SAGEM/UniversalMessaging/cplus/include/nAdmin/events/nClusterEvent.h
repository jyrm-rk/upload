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

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fMulticastConfig;
}
}
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
namespace security {
class fSubject;
}
}
namespace nirvana {
namespace nAdmin {
class nLatticeMember;

namespace events {

class nAdminEventFactory;

using namespace nAdmin;
using namespace nbase::events;
using namespace foundation::io;
using namespace foundation::security;
using namespace foundation::drivers::configuration;

class nClusterEvent :
    public nSynchronous {
  public:
    nClusterEvent(void);
    virtual ~nClusterEvent(void);

    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);
    virtual const std::string getTypeString();
    virtual nEvent* createInstance();
    virtual int getType();

    int getCommand();
    const std::string& getName();
    const std::string& getSource();
    nLatticeMember* getUpdate();

    static const int sConnect = 0;
    static const int sReset = 1;
    static const int sResend = 2;
    static const int sAck = 3;
    static const int sPublish = 4;
    static const int sData = 5;
    static const int sStatus = 6;
    static const int sRequestVote = 7;
    static const int sVote = 8;
    static const int sLatticeUpdate = 9;
    static const int sMaster = 10;
    static const int sConfigRequest = 11;
    static const int sStateChange = 12;
    static const int sHeartBeat = 13;
    static const int sPing = 14;
    static const int sRecovery = 15;
    static const int sStartMulticast = 18;

  private:
    static const int bsEvent = 0x001;
    static const int bsSubject = 0x002;
    static const int bsVote = 0x004;
    static const int bsUpdate = 0x008;
    static const int bsSRealm = 0x010;
    static const int bsDebug = 0x020;
    static const int bsState = 0x040;
    static const int bsBCast = 0x080;
    static const int bsSrcCon = 0x100;
    static const int bsClusterId = 0x200;
    static const int uniqueRealmByteId = 0x400;
    static const int bsIgnoreAcl = 0x800;

    int m_command;
    std::string m_vote;
    std::string m_sourceRealm;
    nLatticeMember* m_pUpdate;
    nEvent* m_pEvent;
    fSubject *m_pSubject;
    bool m_bBcast;
    std::string m_sourceConId;
    bool m_bDebug;
    bool m_bStateEvent;
    longlong m_clusterId;
    fMulticastConfig* myConfig;
    unsigned char myUniqueRealmId;

    static nAdminEventFactory *m_pFactory;
};

}
}
}
}
}
