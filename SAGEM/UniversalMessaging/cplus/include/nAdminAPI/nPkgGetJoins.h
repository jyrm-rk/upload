/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fScheduledTask.h"
#include "Poco/SynchronizedObject.h"

#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class Joins;
class nLeafNode;

using namespace foundation::fbase;

class nPkgGetJoins :
    public fScheduledTask, public Poco::SynchronizedObject {
  public:
    nPkgGetJoins(void);
    virtual ~nPkgGetJoins(void);

    virtual void execute();
    virtual long reSchedule();

    void getJoinsForLeaf(nLeafNode *pLeaf);
    void close();

  private:
    std::list<Joins*> m_list;
    bool m_bScheduled;

    Poco::Mutex m_getJoinsMutex;
    Poco::Mutex m_rescheduleMutex;
};

}
}
}
}
