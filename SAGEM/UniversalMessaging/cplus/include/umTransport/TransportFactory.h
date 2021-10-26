/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "AcceptHandler.h"
#include "DataHandler.h"
#include "CloseHandler.h"
#include "AsynchronousServerTransport.h"
#include "SynchronousServerTransport.h"
#include "ServerTransportContext.h"
#include "AsynchronousTransport.h"
#include "ClientTransportContext.h"
#include "ConnectHandler.h"
#include "SynchronousTransport.h"
#include "forwarddeclare.h"
#include "fDriver.h"
#include <string>
#include <stdexcept>
#include "Poco/Exception.h"
#include "BlockingQueue.h"
#include "LinkedBlockingQueue.h"
#include <memory>

using namespace com::pcbsys::foundation::drivers;



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// The TransportFactory is used to to create ServerTransports or client Transports.  To bind a server Transport you
/// need to first create a ServerTransportContext or to connect to an existing server you need to create a
/// ClientTransportContext.
/// </summary>
/// <seealso cref= com.softwareag.um.io.ClientTransportContext </seealso>
/// <seealso cref= com.softwareag.um.io.ServerTransportContext </seealso>
class TransportFactory {
  private:
    class AsyncAcceptHandler : public com::pcbsys::foundation::drivers::handlers::fAcceptHandler {
      private:
        AcceptHandler *const acceptHandler;
        DataHandler *const dataHandler;
        CloseHandler *const closeHandler;

      public:
        AsyncAcceptHandler(AcceptHandler *aHandler, DataHandler *dHandler, CloseHandler *cHandler);
        virtual ~AsyncAcceptHandler();
        void accept(fDriver *drv, fServerDriver *com);
    };

  private:
    class SyncAcceptHandler : public com::pcbsys::foundation::drivers::handlers::fAcceptHandler {
      private:
        com::pcbsys::foundation::collections::BlockingQueue<fDriver*> *const AcceptQueue;

      public:
        SyncAcceptHandler();
        virtual ~SyncAcceptHandler();
        com::pcbsys::foundation::collections::BlockingQueue<fDriver*> *getQueue();
        void accept(fDriver *fdriver, fServerDriver *fserverdriver);
    };

  public:
    DLL static const std::string SOCKET;
    DLL static const std::string SECURE_SOCKET;
    DLL static const std::string SHM;
    DLL static const std::string RDMA;

	DLL static const std::string SocketType();
	DLL static const std::string SecureSocketType();
	DLL static const std::string SHMType();
	DLL static const std::string RDMAType();

    /// <summary>
    /// This function tests to see if the requested transport is supported on the current hardware. Transports like RDMA require specialised Infiniband cards and drivers to be present.
    /// </summary>
    /// <param name="transportName"> to test </param>
    /// <returns> true or false, depending if the transport is supported </returns>

    DLL static bool TransportSupported(const std::string &transportName);

    /// <summary>
    /// Bind a new ServerTransport as defined by the context.  This method takes several callback objects which will be
    /// notified asynchronously when certain events occur.
    /// </summary>
    /// <param name="context"> The ServerTransportContext which defines what type of ServerTransport to create </param>
    /// <param name="ahandler"> The AcceptHandler that will be notified when new client Transports connect </param>
    /// <param name="dHandler"> The DataHandler that will be notified when data is available to be read from an AsynchronousTranport </param>
    /// <param name="cHandler"> The CloseHandler that will be notified when a client Transport is closed </param>
    /// <returns> AsynchronousServerTransport that will asynchronously accept client connections </returns>
    /// <exception cref="IOException"> if the ServerTransport cannot be bound using the configuration in the context </exception>
    static std::unique_ptr<AsynchronousServerTransport> bind(std::unique_ptr<ServerTransportContext> context, AcceptHandler *ahandler, DataHandler *dHandler, CloseHandler *cHandler);

    /// <summary>
    /// Connect to a ServerTransport using the configuration defined in the ClientTransportContext </summary>
    /// <param name="context"> contains the configuration required to connect to the ServerTransport </param>
    /// <param name="connectHandler"> notified when the AsynchronousTransport is connected </param>
    /// <param name="dataHandler"> notified when data is available to be read from the AsynchronousTransport </param>
    /// <param name="closeHandler"> notified when the AsynchronousTransport is closed </param>
    /// <returns> AsynchronousTransport that can be written to and will fire callbacks when data is available to be read </returns>
    /// <exception cref="IOException"> if there is a problem connecting to the ServerTransport </exception>
    static std::unique_ptr<AsynchronousTransport> connect(std::unique_ptr<ClientTransportContext> context, ConnectHandler *connectHandler, DataHandler *dataHandler, CloseHandler *closeHandler);

  protected:
    static std::unique_ptr<AsynchronousTransport> connect(const std::string &url, ConnectHandler *connectHandler, DataHandler *dataHandler, CloseHandler *closeHandler);

  public:
    /// <summary>
    /// Create a new SynchronousServerTransport using the configuration stored in the ServerTransportContext.
    /// This ServerTransport can be used to accept connections. </summary>
    /// <param name="context"> the configuration to use to create the ServerTransport </param>
    /// <returns> the SynchronousServerTransport that can be used to accept new client connections </returns>
    /// <exception cref="IOException"> if the ServerTransport as defined in the context cannot be bound to </exception>
    DLL static std::unique_ptr<SynchronousServerTransport> bind(std::unique_ptr<ServerTransportContext> context);

    /// <summary>
    /// Connect a new SynchronousTransport as defined in the context to a server. </summary>
    /// <param name="context"> defines the configuration fo the SynchronousTransport </param>
    /// <returns> SynchronousTransport that can be used to read/write data to the server </returns>
    /// <exception cref="IOException"> if the SynchronousTransport as defined in the context cannot connect to the server </exception>
    DLL static std::unique_ptr<SynchronousTransport> connect(std::unique_ptr<ClientTransportContext> context);

  protected:
    static std::unique_ptr<SynchronousTransport> connect(const std::string &url);

  private:
    static fDriver *performConnect(const std::string &url, bool async);

    //========================================================================================================================
    //                                               HELPER PROXY CLASSES
    //========================================================================================================================

    /// <summary>
    /// Provides a simple proxy between the drivers fAcceptHandler and the onAccept() callback
    /// </summary>

    /// <summary>
    /// Provides a simple mapping between the async nature of the fDrivers to the sync nature of this driver
    /// </summary>
};
}
}
}
