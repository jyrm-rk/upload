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

class nPublished;

class nPeekQueue :
    public nCachedChannelAttributes {
  public:
    nPeekQueue(void);
    nPeekQueue(nBaseChannelAttributes *pAttrib, int idx, int size, bool more, const std::string& filter);
    virtual ~nPeekQueue(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    int getIndex();
    int getWindowSize();
    bool hasMore();
    std::string getSelector();
    nPublished** getWindow(int& nWindow);

  protected:
    nPublished **m_ppWindow;
    int m_nWindow;
    int m_currentIdx;
    int m_windowSize;
    bool m_bHasMore;
    std::string m_filter;
};

}
}
}
}
}
