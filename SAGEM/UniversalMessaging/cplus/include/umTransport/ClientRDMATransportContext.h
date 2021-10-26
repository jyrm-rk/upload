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
#include <string>
#include "Poco/URI.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Constructed using the ClientRDMATransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.connect. Communication on the transport is transmitted using Remote Direct Memory Access.
/// </summary>
class UMTRANSPORTDLL ClientRDMATransportContext : public ClientTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ClientRDMATransportContext.  The ClientRDMATransportContext
    /// is configured using the builder so that once build() is called, the ClientRDMATransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ClientRDMATransportContext::Builder()
    ///            .withHost("localhost")
    ///            .withPort(9000)
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
        virtual ClientRDMATransportContext *buildTransport();

      public:
        /// <summary>
        /// Builds the ClientRDMATransportContext based on the configuration that has been set on the Builder. </summary>
        /// <exception cref="IllegalStateException"> if the Builder has not be configured with the required/correct
        /// information to construct the ClientTransportContext; </exception>
        /// <returns> ClientRDMATransportContext used by the TransportFactory.connect method to construct Transports </returns>
        std::unique_ptr<ClientTransportContext> build();

        Builder &withHost(const std::string &host);
        Builder &withPort(int port);
        Builder &withLowLatency(bool flag);
        std::string getHost();
        int getPort();
        bool isLowLatency();

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);
    };

  protected:
    std::string m_host;
    int m_port;
    bool m_enableLowLatency;

    ClientRDMATransportContext(Builder *builder);
    friend std::unique_ptr<ClientTransportContext> ClientTransportContextFactory::build(const std::string &url);

  public:
    /// <summary>
    /// This ClientTransportContext does not currently support Async which means that an exception
    /// will be thrown if you try to create an AsynchronousTransport using the TransportFactory.connect
    /// variant which takes callback objects. </summary>
    /// <returns> false </returns>
    virtual bool supportsAsync();

    std::string getHost();
    int getPort();
    bool isLowLatency();

  protected:
    virtual std::string getConnectionDetail();
    virtual void validate();

  private:
    ClientRDMATransportContext(const ClientRDMATransportContext &copy);
    const ClientRDMATransportContext &operator=(const ClientRDMATransportContext &assign);
};
}
}
}