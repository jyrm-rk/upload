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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;

namespace events {

using namespace nbase;

class nGetDetails :
    public nCachedChannelAttributes {
  public:
    nGetDetails(void);
    nGetDetails(nBaseChannelAttributes *pAttrib);
    virtual ~nGetDetails(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    int getNoOfReaders();
    void setNoOfReaders(int readers);
    int getNoOfEvents();
    void setNoOfEvents(int events);
    longlong getFirstEventTime();
    void setFirstEventTime(longlong time);
    longlong getLastEventTime();
    void setLastEventTime(longlong time);
    longlong getTotalMemorySize();
    void setTotalMemorySize(longlong size);

  private:
    int m_noOfReaders;
    int m_noEvents;
    longlong m_firstEventTime;
    longlong m_lastEventTime;
    longlong m_totalSize;
};

}
}
}
}
}
