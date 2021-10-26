/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nStatusListener.h"
#include "nPkgCloseListener.h"
#include "nDataStreamListener.h"
#include "fSortedList.h"
#include <iostream>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
}
namespace Net {
class Stream;
}
}
namespace nirvana {
namespace client {
class nEventProperties;
}
namespace nAdminAPI {

class nRealmNode;

using namespace com::pcbsys::nirvana::nAdmin;
using namespace com::pcbsys::nirvana::client;
using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::collections;
using namespace com::pcbsys::foundation::Net;

class StatusHandler {
  public:
    StatusHandler(std::string key, nRealmNode* node);
    virtual ~StatusHandler();
    std::string getKey();
    unsigned char* processData(nEventProperties* props, int& len);
    virtual void processEvent(nConsumeEvent*) = 0;
  protected:
    nRealmNode* myRealm;
  private:
    std::string myKey;
    Stream* sbais;
    Stream* sbaos;
    unsigned char* tmp;
    int tmpsize;
};
class RealmStatusHandler : public StatusHandler {
  public:
    RealmStatusHandler(nRealmNode* node);
    virtual ~RealmStatusHandler();
    virtual void processEvent(nConsumeEvent* evt);
};
class ThreadPoolStatusHandler : public StatusHandler {
  public:
    ThreadPoolStatusHandler(nRealmNode* node);
    virtual ~ThreadPoolStatusHandler();
    virtual void processEvent(nConsumeEvent* evt);
};
class StoreStatusHandler : public StatusHandler {
  public:
    virtual ~StoreStatusHandler();
    Stream* bais;
    fEventInputStream* myInputStream;
    StoreStatusHandler(nRealmNode* node);
    virtual void processEvent(nConsumeEvent* evt);
};
class DataGroupStatusHandler : public StatusHandler {
  public:
    virtual ~DataGroupStatusHandler();
    Stream* bais;
    fEventInputStream* myInputStream;
    DataGroupStatusHandler(nRealmNode* node);
    virtual void processEvent(nConsumeEvent* evt);
};
class ConnectionStatusHandler : public StatusHandler {
  public:
    virtual ~ConnectionStatusHandler();
    Stream* bais;
    fEventInputStream* myInputStream;
    ConnectionStatusHandler(nRealmNode* node);
    virtual void processEvent(nConsumeEvent* evt);
};
class InterfaceStatusHandler : public StatusHandler {
  public:
    virtual ~InterfaceStatusHandler();
    Stream* bais;
    fEventInputStream* myInputStream;
    InterfaceStatusHandler(nRealmNode* node);
    virtual void processEvent(nConsumeEvent* evt);
};

class nPkgStatusListener :
    public nStatusListener, public nPkgCloseListener, public nDataStreamListener {
  public:
    nPkgStatusListener(nRealmNode *pNode);
    virtual ~nPkgStatusListener(void);

    virtual void go(nServerStatus *pEvt);
    virtual void closed(nRealmNode *pClose);

    virtual void onMessage(nConsumeEvent* evt);

    fSortedList<std::string, StatusHandler*>* myHandlers;
    nRealmNode *myRealm;
    bool isClosed;
};

}
}
}
}
