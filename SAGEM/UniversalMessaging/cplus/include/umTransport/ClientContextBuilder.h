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
#include "ClientTransportContext.h"
#include "Poco/URI.h"
#include "fBase.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// This is an abstract Builder object which is used to create client side Transports.
/// </summary>
/// <seealso cref= ClientSocketTransportContext::Builder </seealso>
/// <seealso cref= ClientSSLTransportContext::Builder </seealso>
/// <seealso cref= ClientRDMATransportContext::Builder </seealso>
/// <seealso cref= ClientSHMTransportContext::Builder </seealso>
class UMTRANSPORTDLL ClientContextBuilder : public ContextBuilder {
  private:
    class Impl;
    std::unique_ptr<Impl> m_Impl;

  protected:
    ClientContextBuilder();
    ClientContextBuilder(Poco::URI *url);

    static const std::string HOST;
    static const std::string PORT;
    static const std::string TRUSTSTORE;
    static const std::string CIPHERS;
    static const std::string FILEPATH;
	static const std::string SPINCOUNT;
	static const std::string LOCKWAIT;
    static const std::string LOWLATENCY;

  public:
    virtual ~ClientContextBuilder();

  protected:
    /// <summary>
    /// Sets the host of the server that you want to connect to e.g. um.terracotta.org </summary>
    /// <param name="host"> the host of the server that you want to connect to </param>
    /// <returns> this Builder object so that method calls can be chained. </returns>
    ClientContextBuilder *withHost(const std::string &host);

    /// <summary>
    /// Sets the port of the server that you want to connect to e.g. 9000 </summary>
    /// <param name="port"> the port of the server that you want to connect to </param>
    /// <returns> this Builder object so that method calls can be chained. </returns>
    ClientContextBuilder *withPort(int port);

    /// <summary>
    /// Returns the current value that has been set for the host name </summary>
    /// <returns> the host name that this Builder will set for the ClientTransportContext </returns>
    std::string getHost();

    /// <summary>
    /// Returns the current value that has been set for the port </summary>
    /// <returns> the port that this Builder will set for the ClientTransportContext </returns>
    int getPort();

    /// <summary>
    /// Set the path the the trust store that will be used to validate the server provided certificate </summary>
    /// <param name="trustStore"> the location of the trust store on the local machine
    /// @return </param>
    ClientContextBuilder *withTrustStore(const std::string &trustStore);
    
    /// <summary>
    /// Get the value that is currently set for the path to the trust store on the local machine </summary>
    /// <returns> path to the trust store </returns>
    std::string getTrustStore();

    /// <summary>
    /// Set the cipher list to use for SSL, the format of the string is OpenSSL formatted cipher string </summary>
    /// <param name="ciphers"> the OpenSSL cipher list formatted string
    /// @return </param>
    ClientContextBuilder *withCiphers(const std::string &ciphers);
    
    /// <summary>
    /// Get the value that is currently set for the OpenSSL formatted cipher string list </summary>
    /// <returns> OpenSSL formatted string of ciphers </returns>
    std::string getCiphers();

    /// <summary>
    /// Set the path to the directory which will be used to store the memory mapped files used
    /// by the SHM Transport. </summary>
    /// <param name="path"> of the directory used for communication </param>
    /// <returns> this Builder object to allow methods to be chained </returns>
    ClientContextBuilder *withFilePath(const std::string &path);

	/// <summary>
	/// Sets the spin count for reading data from an SHM input stream.  Advanced configuration
	/// option, use judiciously. </summary>
	/// <param name="count"> the number of times to spin waiting for data to arrive </param>
	/// <returns> this Builder object to allow methods to be chained </returns>
	ClientContextBuilder *withSpinCount(const longlong count);

	/// <summary>
	/// Sets the waiting time (in nanoseconds) for yielding a spin lock.  Advanced configuration
	/// option, use judiciously. </summary>
	/// <param name="count"> the time (in nanoseconds) to yield a spin lock </param>
	/// <returns> this Builder object to allow methods to be chained </returns>
	ClientContextBuilder *withLockWait(const int count);

    /// <summary>
    /// Used to disable/enable low latency mode (on by default).  If low latency mode is true then the
    /// application will be very CPU intensive and ideally consume an core of the machine.  This
    /// allows the Transport to respond as fast as possible when new data arrives.  If this mode is
    /// set to false then the Transport will be less CPU intensive but latency will be increased slightly
    /// as a consequence. </summary>
    /// <param name="flag"> true if you want to enable low latency mode </param>
    /// <returns> this Builder object so that method calls can be chained. </returns>
    ClientContextBuilder *withLowLatency(bool flag);

    /// <summary>
    /// Get the file path that is currently set.  The path will be used to store the memory mapped files
    /// required by the SHM Transport. </summary>
    /// <returns> the file path that will be used by the Transport </returns>
    std::string getFilePath();

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

    /// <summary>
    /// Determines whether low latency mode is enabled.
    /// </summary>
    /// <returns> true if low latency is enabled for this Builder; false otherwise </returns>
    bool isLowLatency();

    virtual ClientTransportContext *buildTransport() = 0;
};
}
}
}