/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"
#include "Observer.h"
#include "fSortedList.h"
#include "fEventInputStream.h"
#include "fEventOutputStream.h"

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::collections;
using namespace com::pcbsys::foundation::io;

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fObject;
}

namespace security {
class fSubject;
class fAclEntryFactory;
class fAclEntry;
class fAclGroup;

class fAclList : public Observable, public Observer {
  public:
    fAclList();
    virtual ~fAclList();

    virtual fAclList* getClone();
    virtual void clear();
    virtual void add(fSubject* sub, longlong priv);
    virtual void add(fAclEntry* entry);
    virtual fAclEntry* get(fSubject* entry);
    virtual fAclEntry* remove(fSubject* name);
    virtual fAclEntry* remove(fAclEntry* entry);
    virtual fAclEntry* remove(std::string sub);
    virtual fAclEntry* find(fAclEntry* entry);
    virtual fAclEntry* find(fSubject* entry);
    virtual fAclEntry* lookup(fSubject* subject);
    virtual fAclEntry* lookup(fSubject* sub, bool strict);
    virtual fAclEntry* find(std::string sub);
    virtual int size();
    virtual std::string toString();
    virtual void writeExternal(fEventOutputStream* oos);
    virtual void readExternal(fEventInputStream* ois);
    virtual std::vector<fAclEntry*>* excludes(fAclList* list);
    virtual std::vector<fAclEntry*>* modified(fAclList* list);
    virtual std::vector<fAclEntry*>* getVector();
    virtual bool checkPerms(fSubject* subject, longlong permission);
    virtual bool checkPerms(fSubject* subject, longlong permission, bool strict);
    virtual void update(Observable* observable, void* o);
    virtual fSortedList<std::string, fAclEntry*>::iterator begin();
    virtual fSortedList<std::string, fAclEntry*>::iterator end();
  protected:
  private:
    bool checkPermission(fAclEntry* entry, longlong perm);
    bool doPermCheck(fSubject* subject, longlong permission, bool strct);

    static fAclEntryFactory* sMyFactory;

    fSortedList<std::string, fAclEntry*>* myACL;
    fSortedList<std::string, fAclEntry*>* myHostLookup;
    fSortedList<std::string, fAclEntry*>* myNameLookup;

    fSortedList<std::string, fAclGroup*>* myGroups;

    fAclEntry* myWildcardEntry;
};

}
}
}
}
