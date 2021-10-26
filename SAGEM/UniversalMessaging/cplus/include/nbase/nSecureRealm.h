/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fDefaultSecureObject.h"
#include "fExternalable.h"
#include "fSortedList.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
namespace drivers {
class fConnectionDetails;
}
namespace security {
class fAclEntry;
class fSubject;
}
}
namespace nirvana {
namespace nbase {

using namespace foundation::security;
using namespace foundation::fbase;
using namespace foundation::drivers;
using namespace foundation::io;

class nSecureRealm :
    public fDefaultSecureObject, public CountableObject {
  public:
    nSecureRealm(void);
    nSecureRealm(const std::string& name, std::string* pConnections, int& numConnection);
    virtual ~nSecureRealm(void);

    virtual const std::string& getName();
    virtual void setName (const std::string& name);
    virtual std::list<fConnectionDetails*>& getConnections();
    virtual const std::string& getMountPoint();
    virtual bool add(fSubject *pSubject, longlong permission);
    virtual bool add(fSubject *pCaller, fSubject *pSubject, longlong permission);
    virtual bool remove(fSubject *pCaller, fSubject *pSubject, longlong permission);
    virtual longlong get(fSubject *pCaller, fSubject *pSubject);
    virtual longlong get(fSubject *pCaller, const std::string& subject);
    virtual bool check(fSubject *pSubject, longlong permission, bool warn = true);
    virtual std::string* getACLNames(int &nName);
    virtual std::string* getACLDescriptions(int &nDescription);
    virtual void readExternal(fEventInputStream *pEis);
    virtual void writeExternal(fEventOutputStream *pEos);
    virtual void setConnections(std::string *pConnections, int numConnection);
    void setRemoteClusterName(std::string name);
    std::string getRemoteClusterName();

    static const long ACL_ALL_PERMISSIONS = -1;

    static const long ACL_DEFAULT_ENTRY = 0;

    static const int ACL_ADD = 1;
    static const int ACL_REMOVE = 2;
    static const int ACL_LIST = 4;
    static const int ACL_ADMIN = 8;

  protected:
    std::list<fConnectionDetails*> m_connections;
    fSortedList<std::string, fAclEntry*> m_ACL;

  private:
    fAclEntry* get(fSubject* sub) {
        return fDefaultSecureObject::get(sub);
    };

    std::string m_name;
    std::string myClusterName;
    std::string m_mountPoint;
    fSubject *m_pDefaultCaller;
    Poco::Mutex m_checkMutex;
};

}
}
}
}
