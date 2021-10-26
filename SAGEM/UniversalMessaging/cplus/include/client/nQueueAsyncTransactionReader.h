/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nQueueAsyncReader.h"
#include "nQueueTransactionReader.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nQueue;
class nQueueReaderContext;

/**
 * This Reader enables the client to receive all events asynchronously. The callback method was passed as part of the
 * nQueueReaderContext. This class provides no <code>pop</code> methods, since it is all asynchronous delivery.
 */
class nQueueAsyncTransactionReader :
    public nQueueAsyncReader, public nQueueTransactionReader {
  public:
    virtual ~nQueueAsyncTransactionReader(void);

    /**
    * Commits all received events so far.
    *
    * @throws nSessionNotConnectedException
    * @throws nRequestTimedOutException
    * @throws nIllegalStateException
    */
    virtual void commit();

    /**
    * Commits all events up to the event id specified. This means you can partially commit received events.
    *
    * @param eventId Event ID to commit to, inclusive
    * @throws nSessionNotConnectedException
    * @throws nRequestTimedOutException
    * @throws nIllegalStateException
    */
    virtual void commit(longlong eventId);

    /**
    * Rolls back all received events that have not been committed or rolled back previously. These events are then pushed back onto
    * the queue for redelivery.
    *
    * @throws nSessionNotConnectedException
    * @throws nRequestTimedOutException
    * @throws nIllegalStateException
    */
    virtual void rollback();

    /**
    * Rolls back all events up to the specified event id that have not been committed or rolled back previously. These events are then pushed back onto
    * the queue for redelivery.
    *
    * @param eventId Event Id to rollback to, inclusive
    * @throws nSessionNotConnectedException
    * @throws nRequestTimedOutException
    * @throws nIllegalStateException
    */
    virtual void rollback(longlong eventId);

  protected:
    DLL nQueueAsyncTransactionReader(nQueue *pQueue, nQueueReaderContext *pContext);

    friend class nQueue;

};

}
}
}
}
