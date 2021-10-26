/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nChannelImpl;
}
namespace nbase {
namespace events {
class nEvent;
}

class nBaseChannelAttributes;
class Reconnect;
class nBaseConsumeEvent;

using namespace client;
using namespace events;
using namespace foundation::fbase;

class nChannelQueue : public Countable {
  public:
    DLL nChannelQueue(void);
    DLL virtual ~nChannelQueue(void);

    DLL void reconnectSub();
    DLL void reconnectListeners();
    DLL void stopFlow();
    DLL void startFlow();

    bool isSubscriptionPaused();

  protected:
    nBaseChannelAttributes *m_pNca;
	longlong m_lastEID;
	longlong m_namedSubId;
	longlong m_lastAck;
	bool m_bRequestPurge;
	bool m_bAutoAck;
	std::string m_selector;
	bool m_bMaintainPriority;
    bool m_bIsPaused;

  private:
    virtual nEvent* writeEvent(nEvent *pEvent, longlong timeout) = 0;

    /// <summary>
    /// Acknowledges the event with the specified event ID for the reader with the given unique ID. This method works for queues only.
    /// </summary>
    /// <param name="readerUniqueId">The unique ID of the reader. The server will use this to identify the reader that has consumed this event and acknowledge it.</param>
    /// <param name="eid">The event ID to acknowledge.</param>
    virtual void commit(longlong readerUniqueId, longlong eid) = 0;
    virtual void sendNamedAck(longlong eid, longlong id) = 0;
    /// <summary>
    /// Rolls back the event with the specified event ID for the reader with the given unique ID. This method works for queues only.
    /// </summary>
    /// <param name="readerUniqueId">The unique ID of the reader. The server will use this to identify the reader that has consumed this event and acknowledge it.</param>
    /// <param name="eid">The event ID to roll back</param>
    virtual void rollback(longlong readerUniqueId, longlong eid) = 0;
    virtual void sendNamedRollback(longlong eid) = 0;

    long m_sessionId;
    Reconnect *m_pReconTask;
    bool m_bHasFlowOff;
    nEvent *m_pFlowOff;
    nEvent *m_pFlowOn;

    friend class nClientChannelList;
    friend class nPushTask;
    friend class nChannelImpl;
    friend class nBaseConsumeEvent;
};
/*
  m_pNca(NULL), m_lastEID(-1), m_namedSubId(-1), m_sessionId(0), m_lastAck(-1),
    m_bRequestPurge(false), m_bAutoAck(false), m_bHasFlowOff(false),
    m_pFlowOff(NULL), m_pFlowOn(NULL), m_bMaintainPriority(false) {
    m_pReconTask = new Reconnect(this);
 */

}
}
}
}
