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
#include "fBase.h"
#include "fAclList.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclEntry;
}
}
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace nbase::events;
using namespace foundation::collections;
using namespace foundation::security;

class nSecurityEvent :
    public nSynchronous {
  public:
    nSecurityEvent(void);
    nSecurityEvent(int requestId, longlong id, fAclEntry *pAcl);
    nSecurityEvent(int requestId, longlong id, fAclList* list);
    nSecurityEvent(int requestId, const std::string& name, fAclList* list, bool bIsContainerAcl = false);

    virtual ~nSecurityEvent(void);

    virtual const std::string getTypeString();
    virtual int getType();
    virtual nEvent* createInstance();

    virtual void setName (const std::string& name);
    virtual fAclList* getAcl();
    virtual const std::string& getName();
    virtual fAclEntry* getAclEntry();
    virtual bool removeAcl();
    virtual bool isAcl();
    virtual bool isSetChannels();
    virtual bool isSetQueues();
    virtual bool isSetServices();
    virtual longlong getChannelId();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual void setChannels(bool setChannels);
    virtual void setQueues(bool setQueues);
    virtual void setServices(bool setServices);

  private:
    std::string m_name;
    fAclList* m_ACL;
    fAclEntry* m_pEntry;
    bool m_bRemove;
    bool m_bAcl;
    bool m_bAclEntry;
    bool m_bSetChannels;
    bool m_bSetQueues;
    bool m_bSetServices;
    longlong m_chanId;
};

}
}
}
}
}

