/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEventListener.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace Net {
class MemoryStream;
}
}
namespace nirvana {
namespace client {
class nConsumeEvent;
}
namespace nAdmin {

class nStatusListener;
class nServerStatus;

using namespace client;
using namespace foundation::Net;

class nEventMapping :
    public nEventListener {
  public:
    nEventMapping(nStatusListener *pList);
    virtual ~nEventMapping(void);

    virtual int getType();
    virtual void go(nConsumeEvent *pEvt);

  protected:
    virtual nServerStatus* convert(nConsumeEvent *pEvt);

  private:
    nStatusListener *m_pListener;
    MemoryStream *m_pBaos;
};

}
}
}
}
