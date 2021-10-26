/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ContextBuilder.h"
#include "ServerTransportContext.h"
#include "Poco/URI.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// This is an abstract builder object that is used to create ServerTransports
/// </summary>
/// <seealso cref= ServerSocketTransportContext::Builder </seealso>
/// <seealso cref= ServerSSLTransportContext::Builder </seealso>
/// <seealso cref= ServerRDMATransportContext::Builder </seealso>
/// <seealso cref= ServerSHMTransportContext::Builder </seealso>
class UMTRANSPORTDLL ServerContextBuilder : public ContextBuilder {
  private:
    class Impl;
    std::unique_ptr<Impl> m_Impl;

    virtual int getDefaultTimeout();
    virtual int getDefaultBufferSize();

  protected:
    ServerContextBuilder();
    ServerContextBuilder(Poco::URI *url);

    static const std::string PORT;
    static const std::string TIMEOUT;
    static const std::string ADAPTER;
    static const std::string READBUFFERSIZE;
    static const std::string WRITEBUFFERSIZE;
    static const std::string KEYSTORE;
    static const std::string KEYSTOREPASSWORD;
    static const std::string TRUSTSTORE;
    static const std::string ENABLEDCIPHERS;

    static const std::string FILEPATH;
    static const std::string BUFFERSIZE;
	static const std::string SPINCOUNT;
	static const std::string LOCKWAIT;

    virtual ServerTransportContext *buildTransport() = 0;

  public:
    virtual ~ServerContextBuilder();

  protected:
    /// <summary>
    /// Sets the server port that the ServerTransport should bind to
    /// </summary>
    /// <param name="port"> the port that will be bound to by the ServerTranport </param>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withPort(int port);

    /// <summary>
    /// Returns the current value that has been set for the port </summary>
    /// <returns> the port that this Builder will set for the ServerTransportContext </returns>
    int getPort();

    /// <summary>
    /// Sets the server timeout that any ServerSocket's created from this Builder will adhere to, or
    /// sets the time in ms that the SHM Transport should wait for information before timing out a
    /// connection
    /// </summary>
    /// <param name="timeout"> the timeout that will be bound to by the ServerTransport in milliseconds </param>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withTimeout(int timeout);

    /// <summary>
    /// Returns the current value that has been set for the socket timeout, or gets the current value
    /// for the time in ms that the SHM Transport should wait for information before timing out a
    /// connection
    /// </summary>
    /// <returns> the timeout that this Builder will set for the ServerTransportContext </returns>
    int getTimeout();

    /// <summary>
    /// Set the value for the adapter on this machine that SocketTransport will bind to, or
    /// sets the value for the adapter on this machine that the Infiniband RDMA driver will bind to.
    /// Connections will only be accepted on this adapter. "0.0.0.0" means all adapters on the machine.
    /// </summary>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withAdapter(const std::string &s);

    /// <summary>
    /// Get the value that is currently set for the adapter on this machine that Socket Transport will bind to, or
    /// gets the value that is currently set for the adapter on this machine that RDMA Transport will bind to.
    /// Connections will only be accepted on this adapter. "0.0.0.0" means all adapters on the machine.
    /// </summary>
    /// <returns> String the adapter that the ServerTransport will use </returns>
    std::string getAdapter();

    /// <summary>
    /// Set the size in bytes of the read buffer that the ServerTransport should use </summary>
    /// <param name="readBufferSize"> size of the buffer in bytes </param>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withReadBufferSize(int readBufferSize);

    /// <summary>
    /// Get the current value that has been set for the read buffer size </summary>
    /// <returns> the read buffer size in bytes </returns>
    int getReadBufferSize();

    /// <summary>
    /// Get the current value that has been set for the write buffer size </summary>
    /// <returns> the write buffer size in bytes </returns>
    int getWriteBufferSize();

    /// <summary>
    /// Set the size in bytes of the write buffer that the ServerTransport should use </summary>
    /// <param name="writeBufferSize"> size of the buffer in bytes </param>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withWriteBufferSize(int writeBufferSize);

    /// <summary>
    /// Used to determine whether or not the client is required to present a certificate.
    /// Currently client certificate validation is not supported. </summary>
    /// <returns> false </returns>
    bool isClientCertificateValidationRequired();

    /// <summary>
    /// Set the location of the key store where the server certificate is stored </summary>
    /// <param name="keyStore"> the location of the key store </param>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withKeyStore(const std::string &keyStore);

    /// <summary>
    /// Get the location of the key store where the server certificate is stored </summary>
    /// <returns> the path to the key store </returns>
    std::string getKeyStore();

    /// <summary>
    /// Set the password that should be used to access the key store
    /// @oaram keyStorePassword the key store password </summary>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withKeyStorePassword(const std::string &keyStorePassword);

    /// <summary>
    /// Get the password that should be used to access the key store on the local machine </summary>
    /// <returns> the password of the key store </returns>
    std::string getKeyStorePassword();

    /// <summary>
    /// Set the location of the trust store where certificates will be validated </summary>
    /// <param name="trustStore"> the location of the trust store </param>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withTrustStore(const std::string &trustStore);

    /// <summary>
    /// Get the location set of the trust store on the local machine </summary>
    /// <returns> the location of the trust store </returns>
    std::string getTrustStore();

    /// <summary>
    /// Set the ciphers that should be enabled (if supported) on the ServerTransport </summary>
    /// <param name="enabledCiphers"> openSSL formatted string of ciphers to use </param>
    /// <returns> this Builder object so that method calls can be chained </returns>
    ServerContextBuilder *withEnabledCiphers(const std::string &enabledCiphers);

    /// <summary>
    /// Get the ciphers that should be enabled (if supported) on the ServerTransport </summary>
    /// <returns> the enabled ciphers </returns>
    std::string getEnabledCiphers();

    /// <summary>
    /// Set the path to the directory which will be used to store the memory mapped files used
    /// by the SHM Transport. </summary>
    /// <param name="path"> of the directory used for communication </param>
    /// <returns> this Builder object to allow methods to be chained </returns>
    ServerContextBuilder *withFilePath(const std::string &path);

    /// <summary>
    /// Get the file path that is currently set.  The path will be used to store the memory mapped files
    /// required by the SHM Transport. </summary>
    /// <returns> the file path that will be used by the Transport </returns>
    std::string getFilePath();

    /// <summary>
    /// Set the buffer size in bytes that will be used by the SHM  ServerTransports </summary>
    /// <returns> this Builder object so that methods can be chained </returns>
    ServerContextBuilder *withBufferSize(int bufferSize);

    /// <summary>
    /// Get the buffer size in bytes that will be used by the ServerTransports </summary>
    /// <returns> the size that has been set for the buffer </returns>
    int getBufferSize();

	/// <summary>
	/// Sets the spin count for reading data from an SHM input stream.  Advanced configuration
	/// option, use judiciously. </summary>
	/// <param name="count"> the number of times to spin waiting for data to arrive </param>
	/// <returns> this Builder object to allow methods to be chained </returns>
	ServerContextBuilder *withSpinCount(const longlong count);

	/// <summary>
	/// Sets the waiting time (in nanoseconds) for yielding a spin lock.  Advanced configuration
	/// option, use judiciously. </summary>
	/// <param name="count"> the time (in nanoseconds) to yield a spin lock </param>
	/// <returns> this Builder object to allow methods to be chained </returns>
	ServerContextBuilder *withLockWait(const int count);

	/// <summary>
	/// Gets the current active spin count.  Advanced option for SHM transports only.  </summary>
	/// <returns> the spin count used by the SHM Transport.  Returns 0 if the value is not set, or could
	/// not be converted/translated.  </returns>
	longlong getSpinCount();

	/// <summary>
	/// Get the current wait time for yielding a spin lock.  Advanced option for SHM transports only.  </summary>
	/// <returns> the wait time (in nanoseconds) used by the SHM Transport.  Returns 0 if the value is not
	/// set, or could not be converted/translated.  </returns>
	int getLockWait();
};
}
}
}