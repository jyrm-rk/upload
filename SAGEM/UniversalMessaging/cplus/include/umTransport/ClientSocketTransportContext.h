/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ClientTransportContext.h"
#include "ClientContextBuilder.h"
#include "ClientTransportContextFactory.h"
#include "Poco/URI.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Constructed using the ClientSocketTransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.connect. Communication on the transport is transmitted using TCP Sockets.
/// </summary>
class UMTRANSPORTDLL ClientSocketTransportContext : public ClientTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ClientSocketTransportContext.  The ClientSocketTransportContext
    /// is configured using the builder so that once build() is called, the ClientSocketTransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ClientSocketTransportContext::Builder()
    ///            .withHost("localhost")
    ///            .withPort(8080)
    ///            .build();
    /// \endcode
    /// </summary>
    class UMTRANSPORTDLL Builder : public ClientContextBuilder {
      public:
        /// <summary>
        /// Construct a new instance of this Builder object.
        /// </summary>
        Builder();

      protected:
        Builder(Poco::URI *url);
        friend std::unique_ptr<ClientTransportContext> ClientTransportContextFactory::build(const std::string &url);
        virtual ClientSocketTransportContext *buildTransport();

      public:
        /// <summary>
        /// Builds the ClientSocketTransportContext based on the configuration that has been set on the Builder. </summary>
        /// <exception cref="IllegalStateException"> if the Builder has not be configured with the required/correct
        /// information to construct the ClientTransportContext; </exception>
        /// <returns> ClientSocketTransportContext used by the TransportFactory.connect method to construct Transports </returns>
        std::unique_ptr<ClientTransportContext> build();

        Builder &withHost(const std::string &host);
        Builder &withPort(int port);
        std::string getHost();
        int getPort();

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);
    };

  protected:
    const std::string m_serverHost;
    const int m_serverPort;

    ClientSocketTransportContext(Builder *builder);
    friend std::unique_ptr<ClientTransportContext> ClientTransportContextFactory::build(const std::string &url);

  public:
    /// <summary>
    /// Returns the current value that has been set for the host name </summary>
    /// <returns> the host name that this Builder will set for the ClientTransportContext </returns>
    std::string getHost();

    /// <summary>
    /// Returns the current value that has been set for the port </summary>
    /// <returns> the port that this Builder will set for the ClientTransportContext </returns>
    int getPort();

    /// <summary>
    /// This ClientTransportContext supports Async which means that it can be used to create AsynchronousTransports
    /// using the TransportFactory.connect variant which takes callback objects. </summary>
    /// <returns> true </returns>
    virtual bool supportsAsync();

    virtual std::string getConnectionDetail();

  protected:
    virtual void validate();

  private:
    ClientSocketTransportContext(const ClientSocketTransportContext &copy);
    const ClientSocketTransportContext &operator=(const ClientSocketTransportContext &assign);
};
}
}
}