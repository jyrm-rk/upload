/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ServerTransport.h"
#include "SynchronousTransport.h"
#include "fServerDriver.h"
#include "BlockingQueue.h"
#include <memory>



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// This ServerTransport is used synchronously accept client transports.  The accept() call is a blocking call
/// which will return a SynchronousTransport as soon as it connects.
/// </summary>
/// <seealso cref= com::softwareag::umtransport::AsynchronousServerTransport </seealso>
class UMTRANSPORTDLL SynchronousServerTransport : public ServerTransport {
  private:
    fServerDriver *const m_driver;
    BlockingQueue<fDriver*> *const m_acceptQueue;

    bool m_isClosed;
    void InitializeInstanceFields();

  protected:
    SynchronousServerTransport(fServerDriver *drv, BlockingQueue<fDriver*> *queue);

  public:
    /// <summary>
    /// Close this ServerTransport so that is can no longer be used to accept connections
    /// </summary>
    virtual void close();

    /// <summary>
    /// Blocking call which will return a synchronous client transport when a client connects </summary>
    /// <returns> SynchronousTransport the client transport for a new connection </returns>
    /// <exception cref="IOException"> thrown if the server transport is closed </exception>
    std::unique_ptr<SynchronousTransport> accept();

    virtual ~SynchronousServerTransport();

    friend class TransportFactory;
};
}
}
}
