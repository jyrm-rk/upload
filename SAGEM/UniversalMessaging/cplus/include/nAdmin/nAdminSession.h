/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSession.h"
#include "fBase.h"
#include "nZone.h"

#include <list>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace configuration {
class fConfigObject;
}
namespace fbase {
class fLoggerListener;
class fAuditListener;
}
namespace security {
class fAclEntry;
class fAclGroup;
class fAclList;
class fSubject;
}
namespace drivers {
namespace configuration {
class fDriverConfig;
}
}
}
namespace nirvana {
namespace client {
class nReconnectHandler;
}
namespace nbase {
class nPluginDetails;
class nSecureChannel;
class nSecureRealm;
class nDriverStatus;

namespace events {
class nEvent;
}
}
namespace nAdminAPI {
class nClusterConversionStatus;
class nZone;
class nLeafNode;
}
namespace nAdmin {
class nRemoteInterestEntry;
namespace events {
class nGroupEvent;
class nClusterRequest;
}

class nConnectionListener;
class nAdminEventListener;
class nAdminQueue;
class nConfigListener;
class nStatusChannel;
class nTXChannel;

using namespace com::pcbsys::nirvana::client;
using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::nirvana::nbase::events;
using namespace com::pcbsys::nirvana::nAdmin::events;
using namespace com::pcbsys::nirvana::nAdminAPI;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::configuration;
using namespace com::pcbsys::foundation::collections;
using namespace com::pcbsys::foundation::security;
using namespace com::pcbsys::foundation::drivers::configuration;

class nAdminSession :
    public nSession {
  public:
    nAdminSession(nSessionAttributes *pAttr);
    nAdminSession(nSessionAttributes *pAttr, nReconnectHandler *pHandler, std::string username);
    virtual ~nAdminSession(void);

    virtual void addAdminEventListener(nAdminEventListener *pListener);
    virtual std::list<fConfigObject*>* getConfiguration();

    virtual void addConfigListener(nConfigListener *pListener);
    virtual nStatusChannel* findStatusChannel();
    virtual std::list<nPluginDetails*>* getPluginConfiguration();
    virtual std::list<nDriverStatus*>* getInterfaces();
    virtual void sendClusterRequest(nClusterRequest *pReq);
    virtual std::list<nSecureChannel*>* getChannelStats(const std::string chanName = "");
    virtual nChannel* getChannel(nBaseChannelAttributes *pCa);
    virtual nQueue* getQueue(nBaseChannelAttributes *pCa);
    virtual void setChannelACL(nChannelAttributes *pCa, fAclList *pAL);
    virtual void setChannelACL(nSecureChannel *pNcl);
    virtual nSecureRealm* getRealmStats(const std::string& realmName);
    virtual std::list<nSecureRealm*>* getRealmStats();
    virtual void delAdminEventListener();
    virtual std::string getServerStats();
    void addACLs(fAclEntry **ppEntries, int numEntry, std::string *pNodes, int numNode, bool bChannels = true, bool bQueues = true);
    void addRealmACL(fAclEntry **ppEntries, int numEntry);
    void delACLs(fAclEntry **ppEntries, int numEntry, std::string *pNodes, int numNode, bool bChannels = true, bool bQueues = true);
    void delRealmACL(fAclEntry **ppEntries, int numEntry);
    virtual nClusterRequest* getClusterStatus();
    virtual void addRemoteClusterNode(nRealm* node, nSession* remoteSession, std::string clusterName, std::string localClusterName);
    virtual void addConnectionListener(nConnectionListener *pListener);
    virtual void addLogListener(fLoggerListener *pListener);
    virtual void delLogListener(fLoggerListener *pListener);
    virtual void setRealmACL(nSecureRealm *pNr);
    virtual nRealm* getRealm(const std::string& name);
    virtual void deleteCluster(const std::string& clusterName, bool deleteStore);
    virtual void deleteCluster(const std::string& realm, const std::string& clusterName, bool deleteStore);
    virtual void joinCluster(const std::string& clusterName, nRealm *pRemote, bool canBeMaster);
    virtual void addToCluster(nRealm *pRemote, bool canBeMaster);
    virtual void createCluster(const std::string& name, bool convertLocal, nClusterConversionStatus *pCallback);
    virtual void setContainerACL(fAclList* acl, const std::string container, bool onChannels = true, bool onQueues = true, bool onServices = true);
    virtual void defragStorage(const std::string& channelName);
    virtual void addAuditListener(fAuditListener *pListener, bool replay);
    virtual void addAccessListener(fLoggerListener *pListener);
    virtual void addErrorListener(fLoggerListener *pListener);
    virtual void changeStatusFile(int type, long age, int capacity);
    virtual void changeTransactionFile(int type, long age, int capacity);
    virtual void setConfiguration(std::list<fConfigObject*>& newConfig);
    virtual nTXChannel* findTXChannel();
    virtual void delAuditListener(fAuditListener *pListener);
    virtual void delConnectionListener(nConnectionListener *pListener);
    virtual void delAccessListener(fLoggerListener *pListener);
    virtual void delErrorListener(fLoggerListener *pListener);
    virtual std::string diagnosticRequest(int command);
    virtual void disconnectConnection(const std::string& clientId, bool sendServerRedirect, bool sendReset);
    virtual void rollAuditLog();
    virtual void setInterfaceACL(fDriverConfig *pDc);
    virtual void setInterfaceACL(const std::string& name, fAclList* acl);
    virtual void addInterface(fDriverConfig *pCfg);
    virtual void delInterface(fDriverConfig *pCfg);
    virtual void modInterface(fDriverConfig *pCfg);
    virtual void startInterface(const std::string& name);
    virtual void stopInterface(const std::string& name);
    void setGroupListener(nDataGroupListener* listener);
    nDataGroupListener* getGroupListener();

    virtual std::list<fAclGroup*>* getSecurityGroups();
    virtual void addSecurityGroup(fAclGroup* grp);
    virtual void addSecurityGroups(std::list<fAclGroup*>* grps);
    virtual void removeSecurityGroup(std::string group);
    virtual void removeAclGroupMember(nGroupEvent* grpEvt);
    virtual void removeAclGroupMember(std::string group, std::string member);
    virtual void removeAclGroupMembers(std::string group, std::string* members, int numMembers);
    virtual void removeAclGroupMembers(std::string* groups, int numGroups, std::string* members, int numMembers);
    virtual void AddAclGroupMember(nGroupEvent* grpEvt);
    virtual void AddAclGroupMember(std::string group, fSubject* member);

    std::string getMasterRealm();
    void setGetMasterRealm(bool getMaster);

	virtual void addRemoteInterestEntry(nRemoteInterestEntry* entry);
	virtual void addRemoteInterestEntries(std::list<nRemoteInterestEntry*>& entries);
	virtual void removeRemoteInterestEntry(nRemoteInterestEntry* entry);
	virtual void removeRemoteInterestEntries(std::list<nRemoteInterestEntry*>& entries);

	virtual std::list<nRemoteInterestEntry*>* getRemoteInterestEntries();

	virtual nZone* getZone();
	virtual void joinZone(nZone* zone);
	virtual void leaveZone(nZone* zone);

protected:
    virtual bool handleAsynchronousEvents(nEvent *pEvt);
    virtual void mainClose();

  private:
    void report(fLoggerListener *pListener, const std::string& message);
    void callBaseAsync(nEvent *pEvt);

    nConnectionListener *m_pListener;
    nAdminEventListener *m_pAdminListener;
    fAuditListener *m_pAuditListener;
    nAdminQueue *m_pAdminQ;
    std::list<nConfigListener*> m_configListeners;
    fLoggerListener *m_pLogListener;
    fLoggerListener *m_pAccessListener;
    fLoggerListener *m_pErrorListener;
    fLoggerListener *m_pPluginListener;
    bool m_bHasRequestedConfiguration;

	friend class nAdminAPI::nLeafNode;
	friend class nAdminQueue;
};

}
}
}
}
