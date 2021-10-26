/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nBaseDataStream.h"
#include "fBase.h"
#include "fSortedList.h"
#include "fPrioritized.h"
#include "Poco/Mutex.h"
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fBaseConnection;
}
namespace security {
class fAclEntry;
}
}
namespace nirvana {
namespace nbase {
namespace events {
class nPublished;
}

using namespace foundation::collections;
using namespace com::pcbsys::foundation::fbase::collections;
using namespace foundation::io;
using namespace foundation::security;
using namespace events;

class nBaseDataGroup :
    public nBaseDataStream, public fPrioritized {
  public:
    nBaseDataGroup();
    nBaseDataGroup(const std::string& name, const std::string& subject);
    virtual ~nBaseDataGroup(void);

    nBaseDataGroup* getClone();
    virtual void close();
    virtual longlong getID();
    virtual void addStream(nBaseDataStream *pSub);
    virtual nBaseDataStream* delStream(const std::string& name);
    virtual void addListener(const std::string& id, fBaseConnection *pCon);
    virtual void delListener(const std::string& id);
    void resetStreams();
    virtual fSortedList<std::string, fBaseConnection*>& getListeners();
    virtual void addPublisher(const std::string& sub);
    virtual std::string delPublisher(const std::string& name);
    virtual nBaseDataStream* get(const std::string& name);
    virtual fSortedList<std::string, nBaseDataStream*> getMap();
    virtual nBaseDataStream** getStreams(int& nEndNode);
    virtual int children();
    virtual int totalChildren();
    virtual std::string ToString();
    virtual void writeExternal(fEventOutputStream *pEos);
    virtual void readExternal(fEventInputStream *pEis);
    virtual bool containsPublisher(const std::string& sub);
    virtual bool isGlobal();
    virtual int getType();
    nPublished* getSnapshotEvent(Object *pKey);
    void addSnapshotEvent(Object *pKey, nPublished *pPub);
    nPublished* delSnapshotEvent(Object *pKey);
    void replaceSnapshotEvent(Object *pKey, nPublished *pPub);
    nPublished** getEvents(int& numPublished);
    longlong getConflationInterval();
    void setConflationInterval(longlong conflationInterval);
    bool isMergeEvents();
    void setMergeEvents(bool bMergeEvents);
    void replaceStream(nBaseDataStream *pSub);

    void addSnoopStream(nBaseDataStream *pSub);
    nBaseDataStream* delSnoopStream(const std::string& name);
    nBaseDataStream* getSnoop(const std::string& name);
    fSortedList<std::string, nBaseDataStream*> getSnoopMap();

    int totalAllChildren();
    void createAllEndNodes();

    bool isEnableMulticast();
    void setEnableMulticast(bool _enableMulticast);

    virtual unsigned int getPriority();
    virtual void setPriority(int newPriority);

  private:
    void createEndNodes();
    void createEndNodes(fSortedList<std::string, nBaseDataStream*>& vec, bool isAll);
    void dump(std::string& sb);
    void dump(std::string& sb, const std::string& path);

    fSortedList<std::string, nBaseDataStream*> m_map;
    fSortedList<std::string, nBaseDataStream*> mySnoopMap;
    fSortedList<std::string, fAclEntry*> m_publishers;
    fSortedList<std::string, fBaseConnection*> m_registeredListeners;
    fSortedList<Object*, nPublished*> m_snapshotEvents;

    longlong m_id;
    bool m_bGlobal;
    nBaseDataStream** m_pEndNodes;
    nBaseDataStream** myAllEndNodes;
    int m_nEndNode;
    int m_nAllEndNode;
    bool m_bChanged;
    bool m_bWriteLocked;
    bool hasSnoopChanged;
    bool enableMulticast;

    bool m_bMergeEvents;
    longlong m_conflationInterval;

    int priority;

    Poco::Mutex m_syncMutex;
};

}
}
}
}
