/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBaseTransportObject.h"
#include "fSecureObject.h"
#include "fSortedList.h"
#include "fAclList.h"
#include "Observer.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {

class fAclEntry;
class fSubject;
class fSecurityGroupManager;

using namespace fbase;

class fDefaultSecureObject :
    public fBaseTransportObject, public fSecureObject, public Observer {
  public:
    fDefaultSecureObject(bool addsuperuser = false, bool addEveryone = true, fSecurityGroupManager* secManager = NULL);
    fDefaultSecureObject(fSubject* defaultCaller);
    virtual ~fDefaultSecureObject(void);

    virtual void readExternal(fEventInputStream *pEis);
    virtual void writeExternal(fEventOutputStream *pEis);

    virtual void update(Observable* obs, void* obj);

    virtual void init();
    virtual void destroy();
    virtual void clear();

    virtual fAclList* updateGroupReferences();
    virtual void setACL(fAclList* acls);
    virtual fAclList* getACL();
    virtual std::vector<fAclEntry*>* getVector();

    virtual void add(fAclEntry* entry);
    virtual bool add(fSubject* asubject, longlong permission);
    virtual bool add(fSubject *pCaller, fSubject *pSubject, longlong permission);

    virtual bool contains(fSubject*sub);

    virtual fAclEntry* get(fSubject* sub);

    virtual void remove(std::string name);
    virtual void remove(fSubject* subject);
    virtual bool remove(fAclEntry* entry);
    virtual bool remove(fSubject* asubject, longlong permission);
    virtual bool remove(fSubject* caller, fSubject* asubject, longlong permission);

    virtual bool check(fSubject *pSubject, longlong permission, bool permitAdmins);
    virtual bool check(fSubject *pSubject, longlong Permission, bool permitAdmins, bool warn);

    virtual std::string getACLName(longlong permission);
    virtual std::string getACLDescription(longlong permission);
    virtual std::string* getACLNames(int &nName);
    virtual std::string* getACLDescriptions(int &nDescription);
    virtual long getMaxLevel();

    virtual fSubject* getEveryone();
    static fSubject* getEveryoneUser();
    static fSubject* getEveryoneGroup();
    static std::list<fSubject*> getAdmins();

    static const longlong ACL_DEFAULT_ENTRY = 0;
    static const longlong ACL_ALL_PERMISSIONS = -1;

    static const int ACL_ADD = 1;
    static const int ACL_REMOVE = 2;
    static const int ACL_LIST = 4;
    static const int ACL_ADMIN = 8;

    static const long MAX_LEVEL = 8;

  protected:
    bool doCheck(fSubject *pSubject, longlong Permission);

    fAclList* m_acl;
    fSecurityGroupManager* securityManager;

    static std::string ACL_NAMES[4];
    static std::string ACL_DESCRIPTIONS[4];

  private:
    bool performSecurityCheck(fAclEntry *pResult, longlong permission);

    fSubject *m_pDefaultCaller;
    fAclEntry* myEntry;
    bool ignoreEveryonePermission;

    static fSubject* m_pEveryoneUser;
};

}
}
}
}
