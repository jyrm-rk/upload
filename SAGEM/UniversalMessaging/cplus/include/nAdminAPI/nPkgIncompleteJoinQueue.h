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
#include "Poco/Mutex.h"

#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nJoinInformation;
}
namespace nAdminAPI {

class nLeafNode;

using namespace foundation::fbase;
using namespace client;

class incompleteJoin {
    incompleteJoin (nJoinInformation *pJoin, nLeafNode *pSource);
    virtual ~incompleteJoin(void);

  private:
    nJoinInformation *m_pJoin;
    nLeafNode *m_pSource;

    friend class nPkgIncompleteJoinQueue;
};

class nPkgIncompleteJoinQueue :
    public fScheduledTask {
  public:
    nPkgIncompleteJoinQueue(void);
    virtual ~nPkgIncompleteJoinQueue(void);

    virtual void execute();
    virtual long reSchedule();
    void addJoin(nJoinInformation *pJoin, nLeafNode *pSource);

  private:
    std::list<incompleteJoin*> m_list;
    bool m_bScheduled;

    Poco::Mutex m_executeMutex;
    Poco::Mutex m_reScheduleMutex;
    Poco::Mutex m_addJoinMutex;
};

}
}
}
}
