/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ClientSocketTransportContext.h"
#include "ClientTransportContextFactory.h"
#include <string>
#include "Poco/URI.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Constructed using the ClientSSLTransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.connect. Communication on the transport is encrypted using SSL and transmitted using Sockets.
/// </summary>
class UMTRANSPORTDLL ClientSSLTransportContext : public ClientSocketTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ClientSSLTransportContext.  The ClientSSLTransportContext
    /// is configured using the builder so that once build() is called, the ClientSocketTransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ClientSSLTransportContext::Builder()
    ///            .withHost("localhost")
    ///            .withPort(8080)
    ///            .build();
    /// \endcode
    /// </summary>
    class UMTRANSPORTDLL Builder : public ClientSocketTransportContext::Builder {
      public:
        /// <summary>
        /// Construct a new instance of this Builder object.
        /// </summary>
        Builder();

      protected:
        Builder(Poco::URI *url);
        friend std::unique_ptr<ClientTransportContext> ClientTransportContextFactory::build(const std::string &url);
        virtual ClientSSLTransportContext *buildTransport();

      public:
        /// <summary>
        /// This Builder object is used to build a ClientSocketTransportContext.  The ClientSocketTransportContext
        /// is configured using the builder so that once build() is called, the ClientSocketTransportContext is
        /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
        /// \code
        ///  context = ClientSSLTransportContext.Builder()
        ///            .withHost("localhost")
        ///            .withPort(8080)
        ///            .withTrustStore("/path/truststore")
        ///            .build();
        /// \endcode
        /// </summary>
        virtual std::unique_ptr<ClientTransportContext> build();

        Builder &withHost(const std::string &host);
        Builder &withPort(int port);
        std::string getHost();
        int getPort();

        Builder &withTrustStore(const std::string &trustStore);
        std::string getTrustStore();
        
        Builder &withCiphers(const std::string &trustStore);
        std::string getCiphers();

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);
    };

  protected:
    std::string m_trustStore;
    std::string m_ciphers;

    ClientSSLTransportContext(ClientSSLTransportContext::Builder *builder);
    friend std::unique_ptr<ClientTransportContext> ClientTransportContextFactory::build(const std::string &url);

  public:
    /// <summary>
    /// This ClientTransportContext does not currently support Async which means that an exception
    /// will be thrown if you try to create an AsynchronousTransport using the TransportFactory.connect
    /// variant which takes callback objects. </summary>
    /// <returns> false </returns>
    virtual bool supportsAsync();

    std::string getTrustStore();
    std::string getCiphers();

  protected:
    virtual std::string getConnectionDetail();

  private:
    ClientSSLTransportContext(const ClientSSLTransportContext &copy);
    const ClientSSLTransportContext &operator=(const ClientSSLTransportContext &assign);
};
}
}
}