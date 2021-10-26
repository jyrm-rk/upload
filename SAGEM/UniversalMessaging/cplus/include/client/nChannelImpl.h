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
#include "nChannelQueue.h"
#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nClientChannelList;
namespace events {
class nPublished;
class nPeekQueue;
}
}
namespace client {

using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::nirvana::nbase::events;
using namespace com::pcbsys::foundation::fbase;

class nChannelAttributes;
class nSession;
class nUnexpectedResponseException;
class nEventListener;
class nConsumeEvent;
class nQueueDetails;
class nChannelConnectionListener;
class nNamedObject;
class nJoinInformation;
class nQueuePeekContext;
class nAbstractChannel;

class nChannelImpl :
    public nChannelQueue {
  public:
    virtual ~nChannelImpl(void);

    nChannelAttributes* getChannelAttributes();
    nBaseChannelAttributes* getBaseChannelAttributes();

    /**
    * Gets the last event id of this channel
    *
    * @return a long specifying the last event id of this channel
    */

    longlong getLastEID();
    longlong getLastStoredEID();
    void addSubscriber(nEventListener *pNel, const std::string& selector, longlong eid);
    void addSubscriber(nEventListener *pNel, nNamedObject *pNname, const std::string& selector, bool bAutoAck);
    void removeSubscriber(nEventListener *pNel);
    nQueueDetails* getQueueDetails();
    void purgeEvents(longlong startEID, longlong endEID, const std::string& selector, bool sync, bool purgeJoins);
    void addConnectionListener(nChannelConnectionListener *pListener, bool sync = false);
    void removeConnectionListener(nChannelConnectionListener *pListener);
    void removeAllConnectionListener();
    void handleSubscriberPause(bool isPause);
    std::string getName();

    longlong getUniqueId();
    /**
    * Method to determine if this channel / queue has a subscriber
    *
    * @return if there is a subscriber
    */

    bool isSubscribed();
    void setupSubscription(nEventListener *pListener);
    nSession* getSession();

	static void createChannelImplandClientChannelList(nBaseChannelAttributes* pCa, nSession* session, nChannelImpl*& pChannel, nClientChannelList*& pB);

  private:
	/**
	* Constructs a new nChannel with the specified channel attributes and session
	*
	* @param ca      A nChannelAttributes object specifying the channel's attributes
	* @param session an nSession object specifying the connection to the realm this
	*                channel exists within
	* @throws nIllegalArgumentException
	*/
	nChannelImpl(nBaseChannelAttributes *pCa, nSession *pSession);

    nEvent* writeEvent(nEvent *pEvent);
    virtual nEvent* writeEvent(nEvent *pEvent, longlong timeout);
    
    /// <summary>
    /// Acknowledges the event with the specified event ID for the reader with the given unique ID. This method works for queues only.
    /// </summary>
    /// <param name="readerUniqueId">The unique ID of the reader. The server will use this to identify the reader that has consumed this event and acknowledge it.</param>
    /// <param name="eid">The event ID to acknowledge.</param>
    virtual void commit(longlong readerUniqueId, longlong eid);

    /// <summary>
    /// Rolls back the event with the specified event ID for the reader with the given unique ID. This method works for queues only.
    /// </summary>
    /// <param name="readerUniqueId">The unique ID of the reader. The server will use this to identify the reader that has consumed this event and acknowledge it.</param>
    /// <param name="eid">The event ID to roll back</param>
    virtual void rollback(longlong readerUniqueId, longlong eid);

    virtual void sendNamedAck(longlong eid, longlong id);
    nUnexpectedResponseException handleUnexpectedResponse(nEvent *pResponse, const std::string& method);
    void addSubscriber(nEventListener *pNel, const std::string& selector, longlong eid, bool bUpdate);
    void addSubscriber(nEventListener *pNel, const std::string& selector, longlong eid, bool bUpdate, bool bMaintainPriority);
    void removeSubscriber(nEventListener *pNel, bool isSync);
    void validateSelector(const std::string& selector);
    void publish(nConsumeEvent *pEvent);
    void sendNamedRollback(longlong eid, longlong nameId);
    virtual void sendNamedRollback(longlong eid);
    nNamedObject* createNamedObject(const std::string& name, bool persistent, bool clusterWide, longlong eid);
    void delNamedObject(nNamedObject *pObj);
    nNamedObject* getNamedObject(const std::string& name);
    nNamedObject** getNamedObject(int& numObject);
    nJoinInformation** getJoinInformation(int& numJoin);
    void joinChannel(nAbstractChannel *pDest, bool isRouted, int hopCount, const std::string& selector, bool purge);
    void joinChannel(nChannelImpl *pDest, bool isRouted, int hopCount, const std::string& selector, bool purge, bool archival);
    void deleteJoin(nAbstractChannel *pDest);
    void reSubscribe(nNamedObject *pName, const std::string& selector);
    void reSubscribe(const std::string& selector, longlong eid);
    void unbindNamedObject(nNamedObject *pObj);
    int getEventCount();
    nPeekQueue* peekQueue(nQueuePeekContext *pCtx);
    nClientChannelList* getChannelList();

    nSession *m_pSession;
    std::string m_channelName;
    int m_channelType;
    nClientChannelList *m_pChannelList;
    std::string m_namedSub;

    friend class nChannel;
    friend class nTransactionAttributes;
    friend class nTransaction;
    friend class nChannelIterator;
    friend class nQueueSyncTransactionReader;
    friend class nQueueSyncReader;
    friend class nQueueAsyncTransactionReader;
    friend class nQueueAsyncReader;
    friend class nQueue;
    friend class nAbstractChannel;
    friend class nQueueReader;
	friend class nClientChannelList;
};

}
}
}
}
