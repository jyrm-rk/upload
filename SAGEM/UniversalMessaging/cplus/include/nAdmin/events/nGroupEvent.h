/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NGROUPEVENT_H
#define NGROUPEVENT_H

#include "nSynchronous.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
namespace security {
class fAclGroup;
class fSubject;
}
}
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace com::pcbsys::nirvana::nbase::events;
using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::security;

class nGroupEvent : public nSynchronous {
  private:
    int type;
    std::vector<std::string> groupNames;

    std::list<fAclGroup*>* myGroups;
    std::list<fSubject*>* myMembers;

    std::vector<std::string> memberNames;

  public:
    static const int GROUPS_STATUS = 6;
    static const int REMOVE_GROUP_MEMBER = 5;
    static const int ADD_GROUP_MEMBER = 4;
    static const int GET_GROUPS = 3;
    static const int REMOVE_GROUP = 2;
    static const int ADD_GROUP = 1;

    nGroupEvent();
    virtual ~nGroupEvent();

    nGroupEvent(int type);

    nEvent* createInstance();

    virtual int getGroupEventType();

    virtual void setGroupEventType(int type);

    virtual int getType();

    virtual const std::string getTypeString();

    virtual std::list<fAclGroup*>* getGroups();

    virtual void setGroups(std::list<fAclGroup*>* myGroups);

    virtual void addGroup(fAclGroup* grp);

    virtual std::list<fSubject*>* getMembers();

    virtual void setMembers(std::list<fSubject*>* mem);

    void readExternal(fEventInputStream* ois);

    void writeExternal(fEventOutputStream* oos);

    virtual std::string* getGroupNames(int& numGroups);

    virtual void setGroupNames(std::string* groupNames, int numGroups);

    virtual void setMemberNames(std::string* members, int numMembers);

    virtual std::string* getMemberNames(int& numMembers);
};
}
}
}
}
}

#endif
