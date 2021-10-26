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
#include "Poco/SynchronizedObject.h"
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {
class nPublished;
class nEvent;
}
}
namespace client {

class nChannel;
class nNamedObject;
class nConsumeEvent;

using namespace nbase::events;

/**
 * This class iterates synchronously over a Nirvana Realm channel. By using the methods the channel
 * can be traversed forwards/backwards
 */
class nChannelIterator  {
  public:
    virtual ~nChannelIterator(void);

    /**
     * This method will initiate a close to the server for this Iterator
     *
     * @since 4.0
     */
    DLL void close();

    /**
     * Returns the next event in the channel, or will block until an event is published
     *
     * @return a nConsumeEvent
     * @throws nSecurityException If the client does not have the ability to subscribe to the channel
     * @throws nChannelNotFoundException The channel is no longer valid
     * @throws nSessionNotConnectedException The session has been disconnected
     * @throws nUnexpectedResponseException Unknown response from server. Please contact support
     * @throws nSessionPausedException The session is currently paused, please resume
     * @throws nSelectorParserException Invalid selector specified
     * @throws nRealmNotFoundException The remote realm could not be found
     */
    DLL nConsumeEvent* getNext();

    /**
     * Returns the next event in the channel, or if none will block for the time in milliseconds
     * for the next event to be published onto the channel
     *
     * @param timeout time in milliseconds to wait for the event
     * @return a nConsumeEvent
     * @throws nSecurityException If the client does not have the ability to subscribe to the channel
     * @throws nChannelNotFoundException The channel is no longer valid
     * @throws nSessionNotConnectedException The session has been disconnected
     * @throws nRequestTimedOutException if the time out for the event to be published is exceeded
     * @throws nUnexpectedResponseException Unknown response from server. Please contact support
     * @throws nSessionPausedException The session is currently paused, please resume
     * @throws nSelectorParserException Invalid selector specified
     * @throws nRealmNotFoundException The remote realm could not be found
     */
    DLL nConsumeEvent* getNext(long timeout);

    /**
     * This returns the first event in the channel or null if there are no events in the channel
     *
     * @return a nConsumeEvent or null
     * @throws nSecurityException If the client does not have the ability to subscribe to the channel
     * @throws nChannelNotFoundException The channel is no longer valid
     * @throws nSessionNotConnectedException The session has been disconnected
     * @throws nRequestTimedOutException if the time out for the event to be published is exceeded
     * @throws nUnexpectedResponseException Unknown response from server. Please contact support
     * @throws nSessionPausedException The session is currently paused, please resume
     * @throws nSelectorParserException Invalid selector specified
     * @throws nRealmNotFoundException The remote realm could not be found
     */
    DLL nConsumeEvent* getFirst();

    /**
     * This returns the last event in the channel or null if there are no events in the channel
     *
     * @return a nConsumeEvent or null
     * @throws nSecurityException If the client does not have the ability to subscribe to the channel
     * @throws nChannelNotFoundException The channel is no longer valid
     * @throws nSessionNotConnectedException The session has been disconnected
     * @throws nRequestTimedOutException if the time out for the event to be published is exceeded
     * @throws nUnexpectedResponseException Unknown response from server. Please contact support
     * @throws nSessionPausedException The session is currently paused, please resume
     * @throws nSelectorParserException Invalid selector specified
     * @throws nRealmNotFoundException The remote realm could not be found
     */
    DLL nConsumeEvent* getLast();

    /**
     * Gets the previous event in the channel or null if there are no more previous events
     *
     * @return a nConsumeEvent or null
     * @throws nSecurityException If the client does not have the ability to subscribe to the channel
     * @throws nChannelNotFoundException The channel is no longer valid
     * @throws nSessionNotConnectedException The session has been disconnected
     * @throws nRequestTimedOutException if the time out for the event to be published is exceeded
     * @throws nUnexpectedResponseException Unknown response from server. Please contact support
     * @throws nSessionPausedException The session is currently paused, please resume
     * @throws nSelectorParserException Invalid selector specified
     * @throws nRealmNotFoundException The remote realm could not be found
     */
    DLL nConsumeEvent* getPrev();

	/**
	 * Returns the next batch of events available on the channel, with maximum count up to the prefetchSize value,
	 * or if none will block for the next event to be published onto the channel.
	 *
	 * @param prefetchSize maximum amount of events to be delivered on a single call.
	 * @return a list<nConsumeEvent*>, can be NULL if no events were available
	 * @throws nSecurityException If the client does not have the ability to subscribe to the channel
	 * @throws nChannelNotFoundException The channel is no longer valid
	 * @throws nSessionNotConnectedException The session has been disconnected
	 * @throws nRequestTimedOutException if the time out for the event to be published is exceeded
	 * @throws nUnexpectedResponseException Unknown response from server. Please contact support
	 * @throws nSessionPausedException The session is currently paused, please resume
	 * @throws nSelectorParserException Invalid selector specified
	 * @throws nRealmNotFoundException The remote realm could not be found
	 */
	DLL std::list<nConsumeEvent*>* getNextEvents(int prefetchSize);

	/**
	 * Returns the next batch of events available on the channel, with maximum count up to the prefetchSize value,
     * or if none will block for the time in milliseconds for the next event to be published onto the channel.
	 *
	 * @param prefetchSize maximum amount of events to be delivered on a single call.
	 * @param timeout time in milliseconds to wait for the event
	 * @return a list<nConsumeEvent*>, can be NULL if no events were available
	 * @throws nSecurityException If the client does not have the ability to subscribe to the channel
	 * @throws nChannelNotFoundException The channel is no longer valid
	 * @throws nSessionNotConnectedException The session has been disconnected
	 * @throws nRequestTimedOutException if the time out for the event to be published is exceeded
	 * @throws nUnexpectedResponseException Unknown response from server. Please contact support
	 * @throws nSessionPausedException The session is currently paused, please resume
	 * @throws nSelectorParserException Invalid selector specified
	 * @throws nRealmNotFoundException The remote realm could not be found
	 */
	DLL std::list<nConsumeEvent*>* getNextEvents(int prefetchSize, long timeout);

  private:
    nChannelIterator(nChannel *pChannel, longlong startEid, const std::string& selector, nNamedObject *pName);
    nConsumeEvent* handleResponse(nEvent *pResp);
    nChannel *m_pChannel;
    std::string m_selector;
    longlong m_namedId;
    longlong m_currentIdx;
    longlong m_startEID;
    bool m_bFirstReq;
    std::list<nPublished*> m_window;

    friend class nChannel;
};

}
}
}
}
