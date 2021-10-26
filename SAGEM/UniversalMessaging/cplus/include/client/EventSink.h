/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nChannel;
class nDataGroup;
class nRegisteredEvent;
class nConsumeEvent;

class EventSink {
  public:
    EventSink(nChannel *pChannel, nRegisteredEvent *pRegEvent);
    EventSink(nDataGroup *pGroup, nRegisteredEvent *pRegEvent);
    virtual ~EventSink(void);

    void publish(nConsumeEvent *pEvt);
    void publishTX(nConsumeEvent *pEvt);

  protected:
    nChannel *m_pChannel;
    nDataGroup *m_pGroup;
    nRegisteredEvent *m_pRegisteredEvent;

    friend class nRegisteredEvent;
};

}
}
}
}
