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
namespace nirvana {
namespace nbase {
namespace events {

class nServerHandshake :
    public nSynchronous {
  public:
    nServerHandshake();
    nServerHandshake(longlong sessionId, longlong transTTL, std::string& realmName, std::string& clientHostname, std::string& clientuser);
    virtual ~nServerHandshake(void);

    void setSyncMode(bool flag);
    void setDisconnectIfClusterFails(bool flag);
    longlong getSessionId();
    longlong getTransactionTTL();
    std::string getRealmName();
    longlong getMaxBufferSize();
    std::string getClientHostName();
    std::string getClientUser();
    std::string getServerRNames();
	const std::string& getDataStreamId();
	const std::string& getBuildName();
	void setDataStreamId(const std::string& dataStreamId);
    bool isEnableDataStream();
    void setEnableDataStream(bool enableDataStream);
	bool isMemberOfCluster();
	void setMemberOfCluster(bool memberOfCluster);

    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();

    bool isMulticastSupport();
    void setMulticastSupport(bool support);
    UM_DEPRECATED bool isRequestPriorityConnection();
    /*DEPRECATED. The priority connection will be removed in future versions.*/
    UM_DEPRECATED void setRequestPriorityConnection(bool requestPriorityConnection);

	bool isRequestUnthrottledConnection();
	void setRequestUnthrottledConnection(bool requestUnthrottledConnection);

    void setMasterRealm(std::string name);

    std::string getMasterRealm();

    bool sendMasterRealm();
    void setSendMasterRealm(bool getMaster);

    void setAdmin(bool admin);
    bool isAdmin();

  protected:
    longlong m_sessionId;
    longlong m_transactionTTL;
    longlong m_maxBufferSize;
    std::string m_realmName;
    std::string m_clientHostname;
    std::string m_clientUser;
    std::string m_javaVersion;
    std::string m_OSVersion;
    std::string m_OSName;
    std::string m_buildName;
    std::string m_buildDate;
    bool myGetMasterRealm;
    bool m_bRequestClusterClosure;
    std::string m_serverRNames;
    bool m_bEnableDataStream;
    std::string m_dataStreamId;
    /*DEPRECATED. The priority connection will be removed in future versions.*/
    bool requestPriorityConnection;
	bool requestUnthrottledConnection;
    bool myMulticastSupport;
    std::string myMasterRealmName;
    bool m_isMemberOfCluster;
    bool _isAdmin;
};

}
}
}
}
}

