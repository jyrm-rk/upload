/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fSubject.h"
#include "fSortedList.h"
#include "Observer.h"
#include "Observable.h"
#include "fEventInputStream.h"
#include "fEventOutputStream.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
using namespace com::pcbsys::foundation::collections;

class fAclGroup : public fSubject , public Observer, public Object {

  public:
    fSortedList<std::string, fSubject*> myMembers;
    fAclGroup();
    ~fAclGroup();
    fAclGroup(std::string name);
    fAclGroup(std::string name, std::list<fSubject*> members);
    virtual int getType() {
        return fBase::ACLGROUP;
    }
    void addAll(std::vector<fSubject*> subjects);
    void add(fSubject* member);
    void addObserver(Observer* obs);
    void deleteObserver(Observer* obs);
    std::list<fSubject*>* getMembers();
    bool contains(std::string name);
    fSubject* get(std::string member);
    fSubject* get(fSubject* member);
    fSubject* remove(fSubject* member);
    fSubject* remove(std::string member);
    fSubject* lookup(fSubject* sub, bool strict);
    fSubject* lookup(fSubject* sub);
    virtual bool isGroup();
    std::string toString();
    std::string getUser();
    void readExternal(fEventInputStream* ois);
    void readExternalfAclGroup(fEventInputStream *pIstream);
    void writeExternal(fEventOutputStream *pOstream);
    void deregister();
    std::list<fAclGroup*> getGroups();
    bool equals(fSubject* other);
    void update(Observable *pObs, void *pArg);
    class fAclGroupObservable : public Observable {
      public:
        void dereg() {
            deleteObservers();
        }
        virtual void setChanged() {
            Observable::setChanged();
        }
      private:
    };
    class SubjectIndexer {
      public:
        SubjectIndexer();
        ~SubjectIndexer();
        void put(std::string key, fSubject* value);
        fSubject* lookup(std::string key);
        void remove(std::string key, fSubject* value);
        std::string ToString();
        fSortedList<std::string, fSubject*>* myMapping;
      private:
    };
    class GroupIndexer {
      public:
        GroupIndexer();
        ~GroupIndexer();
        void put(std::string key, fAclGroup* value);
        fAclGroup* lookup(std::string key);
        void remove(std::string key);
        std::string toString();
        fSortedList<std::string, fAclGroup*>* myMapping;
      private:
    };

    fAclGroupObservable membersObservable;

  private:
    SubjectIndexer* myHosts;
    SubjectIndexer* myNames;
    GroupIndexer* myGroups;
};
}
}
}
}