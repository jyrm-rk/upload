/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nAdminEventListener.h"
#include "nPkgCloseListener.h"
#include "fSortedList.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nSecureChannel;
namespace events {
class nMakeChannel;
class nDeleteChannel;
class nAddJoin;
class nDelJoin;
}
}
namespace nAdmin {
namespace events {
class nChangeAttributes;
class nSecurityEvent;
class nControlAdapters;
class nManageAdapters;
class nSchedulerRequest;
class nClusterRequest;
class nClusterEvent;
class nACLEntryRequests;
class nZoneEvent;
class nRemoteInterestEvent;
}
}
namespace nAdminAPI {

class nNode;

using namespace com::pcbsys::nirvana::nAdmin;
using namespace com::pcbsys::nirvana::nAdmin::events;
using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::nirvana::nbase::events;
using namespace com::pcbsys::foundation::collections;

class nPkgAdminListener :
    public nAdminEventListener, public nPkgCloseListener {
  public:
    nPkgAdminListener(nRealmNode *pRealm);
    virtual ~nPkgAdminListener(void);

    virtual void adminEvent(nEvent *pEvt);
    virtual void closed(nRealmNode *pClose);

  protected:
    virtual void addChannel(nMakeChannel *pMake);
    virtual void delChannel(nDeleteChannel *pDel);
    virtual void modChannel(nChangeAttributes *pMod);
    virtual void modChannelAcl(nSecurityEvent *pChanAcl);
    virtual void modContainerAcl(nSecurityEvent *pContAcl);
    virtual void modRealmAcl(nSecurityEvent *pRealmAcl);
    virtual void controlAdapter(nControlAdapters *pControl);
    virtual void manageAdapter(nManageAdapters *pManage);
    virtual void handleNewJoin(nAddJoin *pJoin);
    virtual void handleDelJoin(nDelJoin *pJoin);
    virtual void handleSchedulerEvents(nSchedulerRequest *pSchedule);
    void securityRequest(nACLEntryRequests *pRequests);

  private:
    void modInterfaceVia(nSecurityEvent *pInt_acl);
    void handleClusterEvent(nClusterRequest *pCl);
    void nClusterUpdate(nClusterEvent *pCl);
    void searchNodes(fSortedList<std::string, nNode*>& nodes, nSecurityEvent *pContAcl);
    void searchNodes(nNode *pNode, nACLEntryRequests *pContAcl);
	void handleZoneEvent(nZoneEvent* pZoneEvt);
	void handleRemoteInterestEvent(nRemoteInterestEvent* pRmtIntEvt);

    nRealmNode *m_pRealm;
};

}
}
}
}
