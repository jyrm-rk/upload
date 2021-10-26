/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NACLENTRYFACTORY_H
#define NACLENTRYFACTORY_H

#include "Poco/Mutex.h"
#include "fSortedList.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSubject;
class fAclEntry;

using namespace com::pcbsys::foundation::collections;

class fAclEntryFactory : public Poco::Mutex {

  private:
    static fAclEntryFactory* sMyFactory;//readonly?
    fSortedList<fSubject*, std::list<fAclEntry*>*>* myEntries;			//readonly?
    fAclEntryFactory();

  public:
    static fAclEntryFactory* getInstance();

    virtual fAclEntry* findEntry(fSubject* sub, longlong priv);
    virtual fAclEntry* delEntry(fSubject* sub, longlong priv);
    virtual fAclEntry* createEntry(fSubject* sub, longlong priv);

    std::string toString();

    virtual int size();

};
}
}
}
}

#endif
