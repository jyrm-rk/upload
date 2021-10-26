/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ServerSocketTransportContext.h"
#include "fSSLExtendedConfig.h"
#include <string>
#include "Poco/URI.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Constructed using the ServerSSLTransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.connect. Communication on the transport SSL encrypted and transmitted using Sockets.
/// </summary>
class UMTRANSPORTDLL ServerSSLTransportContext : public ServerSocketTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ServerSSLTransportContext.  The ServerSSLTransportContext
    /// is configured using the builder so that once build() is called, the ServerSSLTransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ServerSSLTransportContext::Builder()
    ///            .withHost("localhost")
    ///            .withPort("9443")
    ///            .build();
    /// \endcode
    /// </summary>
    class UMTRANSPORTDLL Builder : public ServerSocketTransportContext::Builder {
      protected:
        Builder(Poco::URI *url);
        friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);
        virtual ServerSSLTransportContext *buildTransport();

      public:
        /// <summary>
        /// Construct a new instance of this Builder object.
        /// </summary>
        Builder();

        /// <summary>
        /// Builds the ServerSSLTransportContext based on the configuration that has been set on the Builder. </summary>
        /// <exception cref="IllegalStateException"> if the Builder has not be configured with the required/correct
        /// information to construct the ServerTransportContext; </exception>
        /// <returns> ServerSSLTransportContext used by the TransportFactory.bind method to construct Transports </returns>
        std::unique_ptr<ServerTransportContext> build();

        Builder &withPort(int port);
        Builder &withTimeout(int timeout);
        Builder &withAdapter(const std::string &s);
        Builder &withReadBufferSize(int readBufferSize);
        Builder &withWriteBufferSize(int writeBufferSize);

        Builder &withKeyStore(const std::string &keyStore);
        Builder &withKeyStorePassword(const std::string &keyStorePassword);
        Builder &withTrustStore(const std::string &trustStore);
        Builder &withEnabledCiphers(const std::string &enabledCiphers);

        bool isClientCertificateValidationRequired();
        std::string getKeyStore();
        std::string getKeyStorePassword();
        std::string getTrustStore();
        std::string getEnabledCiphers();

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);
    };

  private:
    fSSLExtendedConfig *const m_sslconfig;
    ServerSSLTransportContext(Builder *builder);
    friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);

  public:
    /// <summary>
    /// Used to determine whether or not the client is required to present a certificate </summary>
    /// <returns> true if the client needs to present a certificate to the server </returns>
    bool isClientCertificateValidationRequired();

    /// <summary>
    /// Get the location of the key store where the server certificate is stored, this the private key and certificate in PKCS#12 format for OpenSSL </summary>
    /// <returns> the path to the key store </returns>
    std::string getKeyStore();

    /// <summary>
    /// Get the password that is used to access the key store, this is the private key in OpenSSL </summary>
    /// <returns> the password of the key store </returns>
    std::string getKeyStorePassword();

    /// <summary>
    /// Get the location of the trust store that is used to validate certificates, this is the certificate in OpenSSL </summary>
    /// <returns> the location of the trust store </returns>
    std::string getTrustStore();

    /// <summary>
    /// Get the ciphers that will be enabled if supported by the SSL ServerTransport </summary>
    /// <returns> a string representing enabled ciphers </returns>
    std::string getEnabledCiphers();
    
  private:
    ServerSSLTransportContext(const ServerSSLTransportContext &copy);
    const ServerSSLTransportContext &operator=(const ServerSSLTransportContext &assign);
};
}
}
}