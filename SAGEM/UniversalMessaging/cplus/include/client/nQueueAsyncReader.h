/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nQueueReader.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class eventConsumerWrapper;

/**
 * This Reader enables the client to receive all events asynchronously. The callback method was passed as part of the
 * nQueueReaderContext. This class provides no <code>pop</code> methods, since it is all asynchronous delivery.
 */
class nQueueAsyncReader :
    public nQueueReader {
  public:
    virtual ~nQueueAsyncReader(void);

    /**
     * Close the subscription, and notify the server
     */
    virtual void close();

    /**
     * Close the subscription, but don't notify the server
     */
    virtual void closeLocally();

    /**
    * Pause the subscription of the nQueueAsyncReader. This means that no new events will be received
    * from the server until the subscription is resumed. All events that have already been received will be
    * processed normally.
    *
    * @throws nSessionPausedException The session is currently paused, please resume
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nUnexpectedResponseException Received a response from the server which we can not deal with, see
    * the message for further information
    */
    DLL void pauseReader();

    /**
    * Resumes the subscription of the nQueueAsyncReader.
    * @see {@link nQueueAsyncReader#pauseReader()}
    *
    * @param pReader the nQueueAsyncReader registered as a subscriber
    * @throws nSessionPausedException The session is currently paused, please resume
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nUnexpectedResponseException Received a response from the server which we can not deal with, see
    * the message for further information
    */
    DLL void resumeReader();

    /**
    * Returns true if the subscription of the reader is currently paused. False otherwise.
    */
    DLL bool isPaused();

  protected:
    DLL nQueueAsyncReader(nQueue *pQueue, nQueueReaderContext *pContext);

    /// <summary>
    /// Unique identifier for asynchronous readers.
    /// Use a constant value for all asynchronous readers, since there will be at most one such reader in a session
    /// and the server will need to distinguish that from any synchronous readers in the same session.
    /// </summary>
    static const longlong ASYNC_READER_UNIQUE_ID = -1;

  private:
    eventConsumerWrapper *m_pConWrapper;

    friend class nQueue;

};

}
}
}
}

