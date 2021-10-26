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

class nAddJoin :
    public nCachedChannelAttributes {
  public:
    nAddJoin(void);
    nAddJoin(nBaseChannelAttributes *pSource, nBaseChannelAttributes *pDestination, int hopCount, bool routable,
             const std::string& selector, bool purge, bool archival = false);
    virtual ~nAddJoin(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    nBaseChannelAttributes* getDestination();
    const std::string& getSelector();
    int getHopCount();
    bool allowPurge();
    bool canRoute();
    bool isArchival();

  private:
    int m_hopCount;
    bool m_bCanRoute;
    bool m_bAllowPurge;
    std::string m_selector;
    nBaseChannelAttributes *m_pDestination;
    bool m_bArchival;
};

}
}
}
}
}
