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

class nPurge :
    public nCachedChannelAttributes {
  public:
    nPurge(void);
    nPurge(nBaseChannelAttributes *pAttrib, longlong start, longlong end, const std::string& selector, bool purgeJoins);
    virtual ~nPurge(void);

    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();

    longlong getStartEID();
    longlong getEndEID();
    std::string& getSelector();
    void setSyncFlag(bool value);

  protected:
    longlong m_startEID;
    longlong m_endEID;
    bool m_bPurgeJoinsFlag;
    std::string m_selector;
    bool m_bSyncFlag;
};

}
}
}
}
}
