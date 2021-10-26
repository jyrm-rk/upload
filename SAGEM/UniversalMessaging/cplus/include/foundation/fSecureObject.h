/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fSortedList.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {

class fSubject;
class fAclEntry;
class fAclList;

using namespace com::pcbsys::foundation::collections;

class fSecureObject {
  public:
    fSecureObject(void);
    virtual ~fSecureObject(void);

    virtual bool add(fSubject *pCaller, fSubject *pSubject, longlong permission) = 0;
    virtual bool remove(fSubject *pCaller, fSubject *pSubject, longlong permission) = 0;
    virtual bool check(fSubject *pSubject, longlong permission, bool permitAdmins) = 0;
    virtual std::string getACLName(longlong permission) = 0;
    virtual std::string getACLDescription(longlong permission) = 0;
    virtual fAclList* getACL() = 0;
    virtual std::string* getACLNames(int &nName) = 0;
    virtual std::string* getACLDescriptions(int &nDescription) = 0;
    virtual long getMaxLevel() = 0;
    virtual fSubject* getEveryone() = 0;
};

}
}
}
}
