/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nCachedChannelAttributes.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;

namespace events {

class nUserSubscribe :
    public nCachedChannelAttributes {
  public:
    nUserSubscribe(void);
    nUserSubscribe(nBaseChannelAttributes *pAttrib, longlong startEID, std::string selector, longlong nameId, longlong sessionId, bool purge);
    virtual ~nUserSubscribe(void);

    void setReconnect(bool reconnect);
    void setSynchronous(bool flag);
    void setPaused(bool isPaused);
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual bool isSynchronous();
    bool isPaused();
    bool isMaintainPriority();
    void setMaintainPriority(bool bMaintainPriority);

  protected:
    std::string m_selector;
    longlong m_EID;
    longlong m_nameId;
    longlong m_sessionId;
    bool m_bSendPurgeRequests;
    bool m_bRecon;
    bool m_bSync;
    bool m_bMaintainPriority;
    bool m_bPaused;

  private:
      static const char SEND_PURGE_REQUESTS = 1;
      static const char IS_RECONNECT = 2;
      static const char MAINTAIN_PRIORITY = 4;
      //static const char USE_MULTICAST = 8;
      //static const char INFINITE_WINDOW = 16;
      static const char IS_PAUSED = 32;
};

}
}
}
}
}
