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
#include "nQueueReader.h"
#include "Poco/SynchronizedObject.h"

#include <string>
#include <vector>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nQueue;
class nQueueReaderContext;
class nConsumeEvent;


/**
 * This class provides the client with a synchronous interface into a Nirvana Queue. Events will only be delivered to this
 * client when a call to <code>pop</code> is made.
 *
 */
class nQueueSyncReader :
    public nQueueReader, public Poco::SynchronizedObject {
  public:
    virtual ~nQueueSyncReader(void);

    /**
     * Close the subscription, and notify the server
     */
    virtual void close();

    /**
     * Close the subscription, but do not notify the server
     */
    virtual void closeLocally();

    /**
    * This method places the client on the queue and will block until an event
    * is placed onto the queue.
    *
    * @return The popped event or null if the timeout expired
    * @throws nSessionNotConnectedException Client is not currently
    *                                          connected to the server
    * @throws nSecurityException If your not authorized to perform the operation on the queue
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */
    DLL nConsumeEvent* pop();

    /**
    * This method places the client on the queue and will block until an event
    * is placed onto the queue or the specified timeout expires.
    *
    * If the timeout expires it will return null
    *
    * @param timeout Time to wait in milliseconds for an event
    * @return The popped event or null if the timeout expired
    * @throws nSessionNotConnectedException Client is not currently
    *                                          connected to the server
    * @throws nSecurityException If your not authorized to perform the operation on the queue
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */
    DLL nConsumeEvent* pop(longlong timeout);

    /**
    * This method places the client on the queue and will block until an event
    * is placed onto the queue or the specified timeout expires.
    *
    * If the timeout expires it will return null
    *
    * @param timeout Time to wait in milliseconds for an event
    * @param selector the selection string used to filter events being popped
    * @return The popped event or null if the timeout expired
    * @throws nSessionNotConnectedException Client is not currently
    *                                          connected to the server
    * @throws nSecurityException If your not authorized to perform the operation on the queue
    * @throws nSessionPausedException The session is currently paused
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */
    DLL nConsumeEvent* pop(longlong timeout, std::string selector);

	/**
	* This method places the client on the queue and will block until an event
	* is placed onto the queue.
	*
	* @param prefetchSize the number of events being popped
	* @return a list<nConsumeEvent*> with popped events
	* @throws nSessionNotConnectedException Client is not currently
	*                                          connected to the server
	* @throws nSecurityException If your not authorized to perform the operation on the queue
	* @throws nSessionPausedException The session is currently paused
	* @throws nIllegalStateException The operation could not complete because of a session/connection error
	*/
	DLL std::list<nConsumeEvent*>* popEvents(int prefetchSize);

	/**
	* This method places the client on the queue and will block until an event
	* is placed onto the queue or the specified timeout expires.
	*
	* If the timeout expires it will return null
	*
	* @param prefetchSize the number of events being popped
	* @param timeout Time to wait in milliseconds for an event
	* @return a list<nConsumeEvent*> with popped events or null if the timeout expired
	* @throws nSessionNotConnectedException Client is not currently
	*                                          connected to the server
	* @throws nSecurityException If your not authorized to perform the operation on the queue
	* @throws nSessionPausedException The session is currently paused
	* @throws nIllegalStateException The operation could not complete because of a session/connection error
	*/
	DLL std::list<nConsumeEvent*>* popEvents(int prefetchSize, longlong timeout);

	/**
	* This method places the client on the queue and will block until an event
	* is placed onto the queue or the specified timeout expires.
	*
	* If the timeout expires it will return null
	*
	* @param prefetchSize the number of events being popped
	* @param timeout Time to wait in milliseconds for an event
	* @param selector the selection string used to filter events being popped
	* @return a list<nConsumeEvent*> with popped events or null if the timeout expired
	* @throws nSessionNotConnectedException Client is not currently
	*                                          connected to the server
	* @throws nSecurityException If your not authorized to perform the operation on the queue
	* @throws nSessionPausedException The session is currently paused
	* @throws nIllegalStateException The operation could not complete because of a session/connection error
	*/
	DLL std::list<nConsumeEvent*>* popEvents(int prefetchSize, longlong timeout, std::string selector);

  protected:
    DLL nQueueSyncReader(nQueue *pQueue, nQueueReaderContext *pContext);
    
    //lower timeout value for reader close event, this is necessary because we also support sending this event during session pause
    //in which case the event processing thread will be suspended and we will not receive the response
    static const long sReaderCloseTimeout = 10000;
    bool m_bIsAutoAck = true;

    friend class nQueue;

};

}
}
}
}
