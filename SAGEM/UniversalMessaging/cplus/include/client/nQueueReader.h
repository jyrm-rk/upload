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
#include "nPublished.h"

#include <atomic>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nQueue;
class nQueueReaderContext;
class nQueuePeekContext;
class nConsumeEvent;

/**
 * This class is the base class for all Queue Readers and provides a generic reader interface.
 *
 */
class nQueueReader {
  public:
    virtual ~nQueueReader(void);

    /**
     * Close the subscription, and notify the server
     */
    virtual void close() = 0;

    /**
     * Close the subscription, but do not notify the server
     */
    virtual void closeLocally() = 0;

    /**
    * Method to see whether the reader has consumed any events. For transactional readers,
    * this is reset every time commit or rollback is called.
    *
    * @return true if any events have been consumed by the reader
    */

    DLL bool hasConsumedEvents();

    /**
    * When a reader is closed, the physical subscription is closed at the server.
    * For Transactional readers, a close will rollback to the last committed event.
    *
    * @return true if the reader has been closed
    */

    DLL bool isClosed();

    /**
    * A reader can be closed, but the physical subscription queue is not closed at the server.
    * For Transactional readers, a local close will not rollback to the last committed event.
    *
    * @return true if the reader has been closed locally but not at the server
    */

    DLL bool isClosedLocally();

    /**
    * Performs a non destructive read
    *
    * @param *pContext Peek Context to use.  Used when multiple calls required to
    *                traverse a queue
    * @param nEvent the length of the array
    * @return An Array of events
    * @throws nSecurityException If the client is not authorized to perform
    *                               this request
    * @throws nChannelNotFoundException The queue was not found
    * @throws nSessionNotConnectedException Client is not currently
    *                                          connected to the server
    * @throws nRequestTimedOutException The server did not respond within
    *                                      the timeout
    * @throws nUnexpectedResponseException The server responded with an
    *                                         unexpected response
    * @throws nIllegalArgumentException Invalid parameters passed
    * @throws nSessionPausedException The session is currently paused, please resume
    * @throws nIllegalStateException The operation could not complete because of a session/connection error
    */

    DLL nConsumeEvent** peek(nQueuePeekContext *pContext, int& nEvent);

    /**
    * Creates a Queue Peek Context, which is used to traverse the queue.
    *
    * @param windowSize The size of the window over the queue to uses
    * @param selector A message selector to be applied on the events received
    * @return A new nQueuePeekContext
    */

    static DLL nQueuePeekContext* createContext(int windowSize = 0, const std::string& selector = "");

	/**
	* This call will release any outstanding resources on the server and close the reader. Any future calls to this
	* object will result in an nIllegalStateException being raised.
	*
	* @throws nUnexpectedResponseException if the server returns a response that was not expected
	* @throws nSessionNotConnectedException if the session is currently not connected to the server
	* @throws nRequestTimedOutException if the request did not receive a response within the timeout period
	* @throws nSessionPausedException The session is currently paused
	*/
	DLL void destroyReader();

	/**
	* This call will close local reader resources but remain subscribed at the server Any future calls to this
	* object will work unless destroyReader() is called
	*
	* @throws nUnexpectedResponseException if the server returns a response that was not expected
	* @throws nSessionNotConnectedException if the session is currently not connected to the server
	* @throws nRequestTimedOutException if the request did not receive a response within the timeout period
	*/

	DLL void destroyReaderLocally();

  protected:
    /// <summary>
    /// Creates a reader for the specified queue using the given reader context.
    /// The reader will have its reader unique ID assigned implicitly.
    /// </summary>
    /// <param name="pQueue">The queue to create reader for. Must not be null.</param>
    /// <param name="pContext">The reader context to use</param>
    DLL nQueueReader(nQueue *pQueue, nQueueReaderContext *pContext);

    /// <summary>
    /// Creates a reader for the specified queue using the given reader context and reader unique identifier.
    /// Note: This constructor must only be used for asynchronous readers, which require special reader ID assignment, for
    /// all other cases use the constructor which implicitly assigns the reader unique identifier.
    /// </summary>
    /// <param name="pQueue">The queue to create reader for.</param>
    /// <param name="pContext">The reader context to use.</param>
    /// <param name="readerUniqueId">The reader unique identifier to use for this reader.</param>
    DLL nQueueReader(nQueue *pQueue, nQueueReaderContext *pContext, longlong readerUniqueId);

    bool m_bIsClosed;
    bool m_bIsClosedLocal;
    bool m_bEventsConsumed;
    void testClosed ();
    nQueue *m_pQueue;
    nQueueReaderContext *m_pContext;
    com::pcbsys::nirvana::nbase::events::nPublished** m_pBatch;
    int m_pBatchSize;
    int batchIdx;
    static std::atomic<longlong> sCounter;

    /// <summary>
    /// An identifier that uniquely identifies the reader which performs this queue operation within the session.
    /// This will be paired with the connection id to uniquely identify the reader within the Universal Messaging server.
    /// Note: This should be considered final, it must be set during reader creation and not modified afterwards.
    /// </summary>
    longlong m_readerUniqueId;

    friend class eventConsumerWrapper;
    friend class nQueue;

};

}
}
}
}
