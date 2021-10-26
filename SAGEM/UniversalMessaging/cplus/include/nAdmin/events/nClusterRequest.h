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
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nbase {
class nSecureRealm;
}

namespace nAdmin {

class nLatticeMember;

namespace events {

using namespace nbase;
using namespace nbase::events;
using namespace foundation::io;

class nClusterRequest :
    public nSynchronous {
  public:
    nClusterRequest(int command = 0, const std::string& clusterName = "");
    nClusterRequest(int command, nSecureRealm *pRealm);
    nClusterRequest(int command, const std::string& clusterName, nSecureRealm *pRemoteRealm);
    virtual ~nClusterRequest(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);

    virtual void setSynchronous(bool flag);
    virtual void setSiteName(const std::string& siteName);
    virtual void setRemoteRealmName(const std::string& name);
    virtual void setPrimeSite(bool primeSite);
    virtual int getCommand();
    virtual const std::string& getClusterName();
    virtual const std::string& getRemoteRealmName();
    virtual std::string* getClusterMembers(int& nMember);
    virtual bool isPrimeSite();
    virtual const std::string& getSiteName();
    virtual nLatticeMember* getStatus();
    virtual void setClusterName(const std::string& name);
    virtual void setDeleteStore(bool flag);
    virtual void setMasterOrDeleteStoreFlag(bool masterOrDeleteStoreFlag);

    static const int sCreate = 1;
    static const int sConverting = 2;
    static const int sAddMember = 10;
    static const int sInsertRequest = 15;
    static const int sGetMembers = 20;
    static const int sDelMember = 30;
    static const int sDestroy = 40;
    static const int sUpdate = 50;
    static const int sSessionRequest = 100;

  protected:
    bool m_bSync;
    bool m_bPrimeSite;
    std::string m_siteName;
    std::string m_remoteRealmName;
    std::string m_clusterName;
    int m_command;
    std::string* m_pClusterMembers;
    int m_nClusterMember;
    nLatticeMember *m_pStatus;
    bool m_bMasterOrDeleteStoreFlag;
};

}
}
}
}
}
