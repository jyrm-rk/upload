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
#include "nAbstractChannel.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nChannelImpl;
class nQueueDetails;
class nQueueSyncTransactionReader;
class nQueueReaderContext;
class nQueueSyncReader;
class nQueueReader;
class nQueueAsyncTransactionReader;
class nQueueAsyncReader;
class nConsumeEvent;
class nChannelConnectionListener;
class nChannelAttributes;

using namespace foundation::fbase;

/**
  This class provides a Queue mechanism.
  It allows for multiple users to pop events from the queue and multiple
  users to push events on to the queue.

  However, a queue differs from a channel in that an event can only be popped
  by one user.  This means that an event is only delivered to one client.  While
  a channel it is delivered to all users who are subscribed.

  The queue also offers a peek method.  This method uses a window over the
  queue so that the entire queue does not need to be sent in one hit.

 <p>Four different Queue reading models are supported, these are
<table width="90%" border="1">
  <tr>
    <td>
      <b>Synchronous</b>
    </td>
    <td>
      Here the client will call <code>pop()</code> whenever the client wants to retrieve an event from the server. The
      server will automatically acknowledge that the client has received this event.
    </td>
  </tr>
  <tr>
    <td>
      <b>Synchronous Transactional</b>
    </td>
    <td>
      This is similar in operation to the Synchronous model, except the server does not auto acknowledge the events, this enables
      the client to perform <code>commit()</code> or <code>rollback()</code> operations.
    </td>
  </tr>
  <tr>
    <td>
      <b>Asynchronous</b>
    </td>
    <td>
      In this model the server will record that the client is interested in events from this queue and will maintain an outstanding
      <code>pop()</code> and as events are received on the queue they are automatically delivered to the client via a callback. The events
      are auto acknowledged on the server once they have been delivered to the client.
    </td>
  </tr>
  <tr>
    <td>
      <b>Asynchronous Transactional</b>
    </td>
    <td>
      This is similar in operation to the Asynchronous model, except the server does not auto acknowledge the events, this enables
      the client to perform <code>commit()</code> or <code>rollback()</code> operations. The server will stop delivering events to this client
      once the <code>WindowSize</code> has been reached, the client will need to call either <code>commit()</code> or <code>rollback()</code>
      before events are delivered again.
      <p>
    </td>
  </tr>
</table>
<p>
In both transactional models, when a <code>rollback()</code> is called any events sent since the last <code>commit()</code> or <code>rollback()</code>
will be redelivered to <b>all</b> registered clients. This means the client may not receive these events again, but rather, they are redistributed
amongst the current clients.
 */
class nQueue :
    public nAbstractChannel {
  public:
    virtual ~nQueue(void);

    /**
     * This method returns the current queue details.
     *
     * @return nQueueDetails to be examined
     * @throws nSecurityException Client is not authorized to perform the
     *                               request
     * @throws nChannelNotFoundException The Queue does not exist
     * @throws nSessionNotConnectedException Client is not currently
     *                                          connected to the server
     * @throws nRequestTimedOutException The server did not respond within
     *                                      the client timeout
     * @throws nUnexpectedResponseException The server responded with an
     *                                         unknown response
     * @throws nSessionPausedException The session is currently paused
     */
    DLL nQueueDetails* getDetails();

    /**
     * Creates a Synchronous Transaction queue reader.
     *  <p>
     * This is similar in operation to the Synchronous model, except the server does not auto acknowledge the events, this enables
     * the client to perform <code>commit()</code> or <code>rollback()</code> operations.
     *
     * @param *pContext contains the readers context to be used during construction of the reader
     * @return nQueueSyncTransactionReader
     * @throws nIllegalArgumentException if the context is null
     */
    DLL nQueueSyncTransactionReader* createTransactionalReader(nQueueReaderContext *pContext);

    /**
     * Creates a Synchronous queue reader.
     * <p>
     * Here the client will call <code>pop()</code> whenever the client wants to retrieve an event from the server. The
     * server will automatically acknowledge that the client has received this event.
     *
     * @param *pContext contains the readers context to be used during construction of the reader
     * @return nQueueSyncReader
     * @throws nIllegalArgumentException if the context is null
     */
    DLL nQueueSyncReader* createReader(nQueueReaderContext *pContext);

    /**
     * Creates an Asynchronous Transactional queue reader.
     * <p>
     * This is similar in operation to the Asynchronous model, except the server does not auto acknowledge the events, this enables
     * the client to perform <code>commit()</code> or <code>rollback()</code> operations. The server will stop delivering events to this client
     * once the <code>WindowSize</code> has been reached, the client will need to call either <code>commit()</code> or <code>rollback()</code>
     *  before events are delivered again.
     * @param *pContext contains the readers context to be used during construction of the reader
     * @return nQueueAsyncTransactionReader
     * @throws nIllegalArgumentException if the context is null or some non specified error is found
     * @throws nSecurityException if the subject does not have the correct permissions
     */
    DLL nQueueAsyncTransactionReader* createAsyncTransactionalReader(nQueueReaderContext *pContext);

    /**
     * Creates an Asynchronous queue reader.
     * <p>
     * In this model the server will record that the client is interested in events from this queue and will maintain an outstanding
     * <code>pop()</code> and as events are received on the queue they are automatically delivered to the client via a callback. The events
     * are auto acknowledged on the server once they have been delivered to the client.
     *
     * @param *pContext contains the readers context to be used during construction of the reader
     * @return nQueueAsyncReader
     * @throws nIllegalArgumentException if the context is null or some non specified error is found
     * @throws nSecurityException if the subject does not have the correct permissions
     */
    DLL nQueueAsyncReader* createAsyncReader(nQueueReaderContext *pContext);

    /**
     * This call will release any outstanding resources on the server and close the reader. Any future calls to this
     * object will result in an nIllegalStateException being raised.
     *
     * @param *pReader  The reader to close
     * @throws nUnexpectedResponseException if the server returns a response that was not expected
     * @throws nSessionNotConnectedException if the session is currently not connected to the server
     * @throws nRequestTimedOutException if the request did not receive a response within the timeout period
     * @throws nSessionPausedException The session is currently paused
     */
    static UM_DEPRECATED DLL void destroyReader(nQueueReader *pReader);

    /**
      * Pushes an event on to the queue.
      *
      * @param *pEvent nConsumeEvent to push
      * @return an unique ID for the event on the queue
      * @throws nIllegalArgumentException If the event is null
      * @throws nSecurityException If your not authorized to publish to the
      *                               queue
      * @throws nRequestTimedOutException If the server failed to respond
      * @throws nSessionNotConnectedException Client is not currently
      *                                          connected to the server
      * @throws nSessionPausedException The session is currently paused
      */
    DLL long push(nConsumeEvent *pEvent);

    /**
      * Deletes all undelivered events from the queue.
      * @param selector Purges all events which match this filter
      *
      * @throws nSecurityException The client is not authorized to perform
      *                               this task
      * @throws nChannelNotFoundException The Queue could not be found
      * @throws nSessionNotConnectedException Client is not currently
      *                                          connected to the server
      * @throws nRequestTimedOutException The server did not respond within
      *                                      the timeout
      * @throws nUnexpectedResponseException The server responded with an
      *                                         unknown response
     * @throws nSessionPausedException The session is currently paused
      */
    DLL void purge(std::string& selector);

    /**
     * Removes the connection listener to this queue
     *
     * @param *pListener remove the listener
     *
     * @throws nRequestTimedOutException if the request exceeded the timeout value
     * @throws nSessionNotConnectedException The session is not currently connected to the server
     * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
     * @throws nSessionPausedException The session is currently paused, please resume
     */
    DLL void removeConnectionListener(nChannelConnectionListener *pListener);

    /**
      * Deletes all undelivered events from the queue.
      *
      * @throws nSecurityException The client is not authorized to perform
      *                               this task
      * @throws nChannelNotFoundException The Queue could not be found
      * @throws nSessionNotConnectedException Client is not currently
      *                                          connected to the server
      * @throws nRequestTimedOutException The server did not respond within
      *                                      the timeout
      * @throws nUnexpectedResponseException The server responded with an
      *                                         unknown response
     * @throws nSessionPausedException The session is currently paused
      */
    DLL void purge();

    /**
     * Adds a nChannelConnectionListener to this queue so that when new connections are made to this queue the
     * listener is notified
     *
     * @param *pListener to add
     *
     * @throws nRequestTimedOutException if the request exceeded the timeout value
     * @throws nSessionNotConnectedException The session is not currently connected to the server
     * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
     * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits, or has already been set.
     * @throws nSessionPausedException The session is currently paused, please resume
     */
    DLL void addConnectionListener(nChannelConnectionListener *pListener);

    /**
     * Gets the name of this queue.
     *
     * @return a string specifying the name of this channel
     */
    DLL std::string getName();

    /**
    * Returns the number of events waiting in the queue.
    *
    * @return int size of the queue
    */

    DLL int size();

    /**
    * This call will close local reader resources but remain subscribed at the server Any future calls to this
    * object will work unless destroyReader() is called
    *
    * @param *pReader  The reader to close
    * @throws nUnexpectedResponseException if the server returns a response that was not expected
    * @throws nSessionNotConnectedException if the session is currently not connected to the server
    * @throws nRequestTimedOutException if the request did not receive a response within the timeout period
    */

	UM_DEPRECATED DLL static void destroyReaderLocally(nQueueReader *pReader);

    /**
    * This method will return the nChannelAttributes associated with the nQueue object
    *
    * @return the nChannelAttributes for the nQueue object
    */

    DLL nChannelAttributes* getQueueAttributes();


  protected:
    virtual nChannelAttributes* getClientChannelAttributes();

  private:
    nQueue(nChannelImpl *pChannel);

    friend class nQueueReader;
    friend class nSession;
    friend class nChannel;

};

}
}
}
}
