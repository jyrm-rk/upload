/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NDATAGROUPSTREAMTRANSITIONMANGER_H
#define NDATAGROUPSTREAMTRANSITIONMANGER_H

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {
class nPublished;
class nDataGroupStreamTransitionManager {
  private:
    longlong myId;
    std::string myName;
    longlong myTCPID;
    longlong myMulticastId;
    longlong TCPEventTime;

    bool _inSync;

    std::list<nPublished*>* myUnprocessed;

    void alignUnprocessedQueue();

  public:
    nDataGroupStreamTransitionManager(longlong id, std::string name);

    longlong getId();

    std::string getName();

    int size();

    void setInsync();

    bool inSync();

    nPublished* getNext();

    bool process(nPublished* pub);
    longlong lastTCPEventIn();
    Poco::Mutex modificationLock;
};
}
}
}
}
}

#endif
