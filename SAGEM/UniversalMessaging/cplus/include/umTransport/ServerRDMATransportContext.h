/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ServerTransportContext.h"
#include "ServerContextBuilder.h"
#include "ServerTransportContextFactory.h"
#include <string>
#include "Poco/URI.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Constructed using the ServerRDMATransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.bind. Communication on the transport is transmitted using Remote Direct Memory Access.
/// </summary>
class UMTRANSPORTDLL ServerRDMATransportContext : public ServerTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ServerRDMATransportContext.  The ServerRDMATransportContext
    /// is configured using the builder so that once build() is called, the ServerRDMATransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ServerRDMATransportContext::Builder()
    ///            .withAdapter("0.0.0.0")
    ///            .withPort("9000")
    ///            .build();
    /// \endcode
    /// </summary>
    class UMTRANSPORTDLL Builder : public ServerContextBuilder {
      protected:
        Builder(Poco::URI *url);
        friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);
        virtual ServerRDMATransportContext *buildTransport();

      public:
        /// <summary>
        /// Construct a new instance of this Builder object.
        /// </summary>
        Builder();

        /// <summary>
        /// Builds the ServerRDMATransportContext based on the configuration that has been set on the Builder. </summary>
        /// <exception cref="IllegalStateException"> if the Builder has not be configured with the required/correct
        /// information to construct the ServerTransportContext; </exception>
        /// <returns> ServerRDMATransportContext used by the TransportFactory.bind method to construct Transports </returns>
        std::unique_ptr<ServerTransportContext> build();

        Builder &withPort(int port);
        Builder &withAdapter(const std::string &s);
        std::string getAdapter();
        int getPort();

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);
    };

  private:
    fRDMAConfig *const m_config;		// TODO: fRDMAConfig doesn't exist yet in the Nirvana C++ API

    ServerRDMATransportContext(Builder *builder);
    friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);
  public:
    /// <summary>
    /// Get the value for the adapter on this machine that RDMA Transport will bind to.
    /// Connections will only be accepted on this adapter. "0.0.0.0" means all adapters on the machine.
    /// </summary>
    /// <returns> String the adapter that the ServerTransport will use </returns>
    std::string getAdapter();

    /// <summary>
    /// Returns the port that will be used in ServerTransports created using this context </summary>
    /// <returns> the port that will be used in ServerTransports created using this context </returns>
    int getPort();

  protected:
    virtual fDriverConfig *getConfig();

  public:
    /// <summary>
    /// This ServerTransportContext does not currently support Async which means that an exception
    /// will be thrown if you try to create an AsynchronousServerTransport using the TransportFactory.bind
    /// variant which takes callback objects. </summary>
    /// <returns> false </returns>
    virtual bool supportsAsync();

  protected:
    virtual void validate();

  private:
    ServerRDMATransportContext(const ServerRDMATransportContext &copy);
    const ServerRDMATransportContext &operator=(const ServerRDMATransportContext &assign);
};
}
}
}