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

class nPopQueue :
    public nCachedChannelAttributes {
  public:
    enum class Command : unsigned char { Pop, Close };
    nPopQueue(void);
    nPopQueue(nBaseChannelAttributes *pAttrib, longlong readerUniqueId, std::string& selector);
    nPopQueue(nBaseChannelAttributes *pAttrib, Command command, longlong readerUniqueId);
	nPopQueue(nBaseChannelAttributes *pAttrib, longlong readerUniqueId, std::string& selector, bool ack);
	nPopQueue(nBaseChannelAttributes *pAttrib, longlong readerUniqueId, std::string& selector, bool ack, int prefetchSize);
    virtual ~nPopQueue(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    void setTimeout(longlong timeout);
    void setWindowSize(int windowSize);
    nPublished* getEvent();
    bool isMaintainPriority();
    void setMaintainPriority(bool maintainPriority);
    bool isAutoAck();
    void setAutoAck(bool autoAck);
    int getPrefetchSize();
    void setPrefetchSize(int prefetchSize);
    nPublished** getEvents();
    int getEventsSize();
    void setEvents(nPublished** events, int size);
    Command getCommand();
    longlong getReaderUniqueId();

  protected:
    Command m_command;
    longlong m_readerUniqueId;
    longlong m_timeout;
    std::string m_selector;
    int m_windowSize;
    longlong m_deliveryId;
    nPublished *m_pEvent;
    nPublished **m_pEventArray;
    int m_pEventArraySize;
    bool m_bMaintainPriority;
    bool m_bAutoAck;
    int m_prefetchSize;
};

}
}
}
}
}
