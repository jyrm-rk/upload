/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nChannel.h"

#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nChannelImpl;
}
namespace nAdmin {

using namespace client;

class nStatusListener;
class nEventMapping;

class nStatusChannel :
    public nChannel {
  public:
    nStatusChannel(nChannelImpl *pChannel);
    virtual ~nStatusChannel(void);

    virtual void addSubscriber(nStatusListener *pNel, longlong eid);
    virtual void addSubscriber(nStatusListener *pNel, const std::string& selector, longlong eid);

  private:
    std::list<nEventMapping*> m_listenerList;
};

}
}
}
}
