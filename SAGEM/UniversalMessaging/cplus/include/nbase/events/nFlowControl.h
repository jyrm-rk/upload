/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEvent.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

class nFlowControl :
    public nEvent {
  public:
    nFlowControl();
    nFlowControl(longlong channelId, bool flag);
    virtual ~nFlowControl(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    static const bool XON = true;
    static const bool XOFF = false;

  private:
    bool m_bFlag;
    longlong m_channelId;
};

}
}
}
}
}
