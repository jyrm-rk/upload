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

#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;

namespace events {

class nPublished;

class nChannelIterate :
    public nCachedChannelAttributes {
  public:
    nChannelIterate(void);
    nChannelIterate(nBaseChannelAttributes *pAttrib, longlong eid, longlong timeout, int command, std::string& selector, longlong nameId, longlong sessionId);
	nChannelIterate(nBaseChannelAttributes *pAttrib, longlong eid, longlong timeout, int command, std::string& selector, longlong nameId, longlong sessionId, int prefetchSize);
    virtual ~nChannelIterate(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    std::list<nPublished*>& getEventWindow();
    nPublished* getEvent();

    int getCommand();

    static const int sFirst = 0;
    static const int sLast = 1;
    static const int sNext = 2;
    static const int sPrev = 3;
    static const int sOpen = 5;
    static const int sClose = 6;

  protected:
    int m_command;
    longlong m_EID;
    longlong m_timeout;
    std::string m_selector;
    longlong m_nameId;
    longlong m_sessionId;
    nPublished *m_pEvent;
    std::list<nPublished*> m_events;
	int m_prefetchSize = 1;

private:
	void clearEvents();
};

}
}
}
}
}
