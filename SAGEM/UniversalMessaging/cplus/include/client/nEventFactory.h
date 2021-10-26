/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBaseEventFactory.h"

#include "Poco/Mutex.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSubject;
}
}
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;
namespace events {

class nConnectionUpdate;
class nEvent;

using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::security;
using namespace com::pcbsys::nirvana::nbase;

class nEventFactory :
    public fBaseEventFactory {
        
  public:
    static fBaseEventFactory* getInstance(int version);
    static fBaseEventFactory* getDefault();
    static DLL void destroyFactories ();
    static void setInstance(nEventFactory *pFactory, int version);

    nEventFactory(void);

    virtual ~nEventFactory(void);
    virtual fBaseEvent* getEvent(int id);
    virtual int getEventId(fBaseEvent *pEvent);
    virtual fBaseEvent* getKeepAlive();
    virtual fBaseEvent* getKeepAlive(fConnection *pCon);
    virtual const std::string getName(int id);
    virtual int getType();

    int getVersion();
    bool isMulticastEnabled();
    bool enableCompression();

    const static int MainVersion = 18;
    const static int LowestSupportedVersion = MainVersion;
    const static int sTracerMask = 0x80;

    static const int ADD_CHANNEL = 1;
    static const int DEL_CHANNEL = 2;
    static const int GET_LAST_EID = 3;
    static const int PURGE = 4;
    static const int USER_FIND = 5;
    static const int MOD_CHANNEL = 6;
    static const int GET_LAST_STORED_EID = 7;
    // 8
    static const int PUBLISH_REQUEST = 9;
    static const int PUBLISHED = 10;
    static const int PUBLISHED_JOIN = 11;
    static const int USER_SUBSCRIBE = 12;
    static const int USER_TX_PUBLISH_REQUEST = 13;
    static const int USER_TX_COMMIT = 14;
    static const int USER_TX_ABORT = 15;
    static const int USER_TX_ACK = 16;
    static const int USER_UNSUBSCRIBE = 17;
    static const int USER_DISCONNECT = 18;
    static const int USER_TX_ISCOMMITTED = 19;
    static const int USER_TX_PUBLISH_COMMIT = 20;
    static const int USER_CONNECTION_REQUEST = 21;
    static const int USER_FLOW_CONTROL = 22;
    static const int USER_GET_CHANNEL_LIST = 23;
    // 24
    static const int ADD_JOIN = 25;
    static const int DEL_JOIN = 26;
    static const int JOIN_FIND = 27;
    static const int GET_JOIN = 28;
    static const int USER_GET_JOIN = 29;
    static const int ADD_REALM = 30;
    static const int DEL_REALM = 31;
    static const int GET_REALM = 32;
    static const int QUEUE_POP = 33;
    static const int QUEUE_DETAILS = 34;
    static const int QUEUE_PEEK = 35;
    static const int CLIENT_CANCEL_REQUESTS = 36;
    static const int ADD_CHANNELS = 37;
    static const int DEL_CHANNELS = 38;
    // 39
    static const int SECURITY_EXCEPTION = 40;
    static const int SERVER_DISCONNECT = 41;
    static const int REDIRECTION = 42;
    static const int DISCONNECT_USER = 43;
    static const int MAINTAIN_CHANNEL = 44;
    // 45
    // 46
    static const int SERVER_REDIRECT = 47;
    // 48
    static const int SECURITY_REQUEST = 49;
    static const int SECURITY_CHANNEL_ACL = 50;
    static const int SECURITY_REALM_ACL = 51;
    static const int REQUEST_CONFIG = 52;
    static const int SET_CONFIG = 53;
    static const int UPDATE_CONFIG = 54;
    static const int SERVER_MAP = 55;
    static const int REALM_MAP = 56;
    static const int CHANNEL_MAP = 57;
    static const int TIMEOUT_VALUES = 58;
    static const int STATUS_UPDATE = 59;
    static const int SERVER_JOIN = 60;
    static const int JOIN_RESTART = 61;
    static const int SECURITY_INTERFACE_ACL = 62;
    static const int SECURITY_CONTAINER_ACL = 63;
    static const int SECURITY_GROUP = 64;
    static const int HEARTBEAT = 65;
    static const int SERVER_HANDSHAKE = 66;
    static const int CLIENTHEARTBEAT = 67;
    // 68
    // 69
    static const int PARENT_REALM = 70;
    // 71
    static const int FIND_SUBSCRIBE = 72;
    // 73
    // 74
    static const int EXCEPTION = 75;
    static const int CHANNEL_CONNECTION_UPDATE = 76;
    static const int LOG_MESSAGE = 77;
    static const int AUDIT_EVENT = 78;
    // 79
    static const int MANAGE_ADAPTER = 80;
    static const int CONTROL_ADAPTER = 81; // start/stop/delete later pause/resume
    static const int GET_ADAPTER = 82;
    static const int GET_PLUGIN = 83;
    // 84
    static const int MGR_NAMEDSUB = 85;
    static const int ACK_NAMEDSUB = 86;
    // 87
    static const int SERVER_EXTENSION = 88;
    static const int CHANNEL_ITERATE = 89;
    static const int QUEUE_TRANSACTION = 90;
    static const int DATA_STREAM_PUBLISH = 91;
    static const int DATA_GROUP_ADMIN = 92;
    static const int DATA_GROUP_UPDATE = 93;
    // 94
    // 95
    // 96
    // 97
    static const int MULTICAST_CONNECTION_DETAILS = 98;

    static const int BATCH_PUBLISH=99;
    static const int ADMIN_CONTAINER = 100;
    static const int CLUSTER_EVENT = 101;
    static const int CLUSTER_REQUEST = 102;
    static const int SCHEDULER_REQUEST = 103;
    // 104
    static const int DIAG_COMMAND = 105;
    static const int DELAY_TRIGGER = 106;
    static const int SERVER_EVENT = 107;
    static const int CLUSTER_QUEUE = 108;
    static const int CLUSTER_STORE_STATE = 109;
    static const int CL_STORE_RECOVERY = 110;
	static const int MANAGE_REMOTE_INTEREST = 111;
	static const int ZONE_EVENT = 112;
	static const int CHANNEL_NOT_FOUND_EXCEPTION_EVENT = 114;
    // 115
    static const int USER_PAUSE = 116;

    //
    // Must be the last entry
    //
    static const int MAX_EVENT_ID = 117;
    static const int OOB_PLACEHOLDER = 150;
    static const int sHeartBeatId = HEARTBEAT;

  protected:
    nEvent* m_pEventGenerator[MAX_EVENT_ID];
    nEvent* getObject(int id);

  private:
    static nEventFactory** setupFactory();

    static nEventFactory** m_ppFactories;
    static int m_ppFactoriesSize;
    static Poco::Mutex m_mutex;
};

}
}
}
}
}
