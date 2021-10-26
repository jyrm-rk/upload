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
#include "fSocketConfig.h"
#include "Poco/URI.h"

using namespace com::pcbsys::foundation::drivers::configuration;



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Constructed using the ServerSocketTransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.connect. Communication on the transport is transmitted using TCP Sockets.
/// </summary>
class UMTRANSPORTDLL ServerSocketTransportContext : public ServerTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ServerSocketTransportContext.  The ServerSocketTransportContext
    /// is configured using the builder so that once build() is called, the ServerSocketTransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ServerSocketTransportContext::Builder()
    ///            .withAdapter("0.0.0.0")
    ///            .withPort("9000")
    ///            .build();
    /// \endcode
    /// </summary>
    class UMTRANSPORTDLL Builder : public ServerContextBuilder {
      protected:
        Builder(Poco::URI *url);
        friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);
        virtual ServerSocketTransportContext *buildTransport();

      public:
        /// <summary>
        /// Construct a new instance of this Builder object.
        /// </summary>
        Builder();

        Builder &withPort(int port);
        Builder &withTimeout(int timeout);
        Builder &withAdapter(const std::string &s);
        Builder &withReadBufferSize(int readBufferSize);
        Builder &withWriteBufferSize(int writeBufferSize);

        int getPort();
        int getTimeout();
        std::string getAdapter();
        int getReadBufferSize();
        int getWriteBufferSize();

        /// <summary>
        /// Builds the ServerSocketTransportContext based on the configuration that has been set on the Builder. </summary>
        /// <exception cref="IllegalStateException"> if the Builder has not be configured with the required/correct
        /// information to construct the ServerTransportContext; </exception>
        /// <returns> ServerSocketTransportContext used by the TransportFactory.bind method to construct Transports </returns>
        std::unique_ptr<ServerTransportContext> build();

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);
    };

  protected:
    fSocketConfig *m_config;

  private:
    ServerSocketTransportContext(Builder *builder);
    friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);

  protected:
    ServerSocketTransportContext(Builder *builder, fSocketConfig *_config);
    void init(Builder *builder, fSocketConfig *_config);

  public:
    /// <summary>
    /// Returns the adapter that will be bound to by ServerTransports created using this ServerContext </summary>
    /// <returns> the adapter that ServerTransports will bind to e.g. "0.0.0.0" </returns>
    std::string getAdapter();

    /// <summary>
    /// Returns the port that will be used by ServerTransports created using this ServerContext </summary>
    /// <returns> the port that ServerTransports will bind to e.g. 8080 </returns>
    int getPort();

    /// <summary>
    /// Get the read buffer size in bytes that will be used by ServerTransports created using this ServerContext </summary>
    /// <returns> the read buffer size in bytes </returns>
    int getReadBufferSize();

    /// <summary>
    /// Get the write buffer size in bytes that will be used by ServerTransports created using this ServerContext </summary>
    /// <returns> the write buffer size in bytes </returns>
    int getWriteBufferSize();

    virtual ~ServerSocketTransportContext();

  protected:
    virtual void enableAsync();
    virtual void validate();

  public:
    /// <summary>
    /// This ServerTransportContext supports Async which means that it can be used to create AsynchronousServerTransports
    /// using the TransportFactory.bind variant which takes callback objects. </summary>
    /// <returns> true </returns>
    virtual bool supportsAsync();

  protected:
    virtual fDriverConfig *getConfig();

  private:
    ServerSocketTransportContext(const ServerSocketTransportContext &copy);
    const ServerSocketTransportContext &operator=(const ServerSocketTransportContext &assign);
};
}
}
}