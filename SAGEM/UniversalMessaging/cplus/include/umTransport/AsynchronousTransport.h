/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Transport.h"
#include "fDriver.h"
#include "fAsyncReadListener.h"
#include "DataHandler.h"
#include "CloseHandler.h"
#include "TcpStream.h"
#include <stdexcept>
#include "Exception.h"

using namespace com::pcbsys::foundation::drivers;



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// This is a client side Transport object.  It is constructed on the client side by creating
/// a ClientTransportContext which is then passed to TransportFactory.bind with the required
/// callback objects (DataHandler, CloseHandler).  On the server side, an AsynchronousServerTransport
/// will accept connections and handle them as AsynchronousTransports.
/// </summary>
class AsynchronousTransport : public Transport {
  private:
    class AsyncCallbackProxy : public fAsyncReadListener, public fWriteReadyCallback {	// TODO
      private:
        AsynchronousTransport *const m_outerInstance;

      public:
        AsyncCallbackProxy(AsynchronousTransport *outerInstance);
        void dataReady();
        void close();
        void writeReady();
    };

  private:
    fDriver *const m_driver;
    DataHandler *const m_dataHandler;
    com::softwareag::umtransport::CloseHandler *const m_closeHandler;
    AsyncCallbackProxy *const m_callbackProxy;
    TcpStream *const m_is;
    TcpStream *const m_os;

  protected:
    AsynchronousTransport(fDriver *drv, DataHandler *dHandler, CloseHandler *cHandler);

    virtual void registerForRead();
    friend class TransportFactory;

  public:
	  virtual ~AsynchronousTransport();

    /// <summary>
    /// Write (and flush) the data stored in the ByteBuffer to the network/file depending on the protocol used
    /// in the TransportContext.
    /// </summary>
    /// <param name="buffer"> contains the binary data to write to the Transport
    /// @return </param>
    void write(ByteBuffer *buffer);		// TODO

    /// <summary>
    /// Used to check if the Transport has been closed </summary>
    /// <returns> true in the Transport has been closed </returns>
    virtual bool isClosed();

    /// <summary>
    /// Close the Transport so that data can no longer be read/written.
    /// </summary>
    virtual void close();
};
}
}
}