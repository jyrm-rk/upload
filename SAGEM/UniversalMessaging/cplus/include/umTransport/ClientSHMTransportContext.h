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
/// Constructed using the ClientSHMTransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.connect. Communication on the transport is transmitted using Shared Memory.
/// </summary>
class UMTRANSPORTDLL ClientSHMTransportContext : public ClientTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ClientSHMTransportContext.  The ClientSHMTransportContext
    /// is configured using the builder so that once build() is called, the ClientSHMTransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ClientSHMTransportContext::Builder()
    ///            .withFilePath("/path/to/directory")
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
        virtual ClientSHMTransportContext *buildTransport();

      public:
        /// <summary>
        /// Builds the ClientSHMTransportContext based on the configuration that has been set on the Builder. </summary>
        /// <exception cref="IllegalStateException"> if the Builder has not be configured with the required/correct
        /// information to construct the ClientTransportContext; </exception>
        /// <returns> ClientSHMTransportContext used by the TransportFactory.connect method to construct Transports </returns>
        std::unique_ptr<ClientTransportContext> build();

		/// <summary>
		/// Set the path to the directory which will be used to store the memory mapped files used
		/// by the SHM Transport. </summary>
		/// <param name="path"> of the directory used for communication </param>
		/// <returns> this Builder object to allow methods to be chained </returns>
        Builder &withFilePath(const std::string &path);

		/// <summary>
		/// Used to disable/enable low latency mode (on by default).  If low latency mode is true then the
		/// application will be very CPU intensive and ideally consume an core of the machine.  This
		/// allows the Transport to respond as fast as possible when new data arrives.  If this mode is
		/// set to false then the Transport will be less CPU intensive but latency will be increased slightly
		/// as a consequence. </summary>
		/// <param name="flag"> true if you want to enable low latency mode </param>
		/// <returns> this Builder object so that method calls can be chained. </returns>
        Builder &withLowLatency(bool flag);

		/// <summary>
		/// Sets the spin count for reading data from an SHM input stream.  Advanced configuration
		/// option, use judiciously. </summary>
		/// <param name="count"> the number of times to spin waiting for data to arrive </param>
		/// <returns> this Builder object to allow methods to be chained </returns>
		Builder &withSpinCount(const longlong count);

		/// <summary>
		/// Sets the waiting time (in nanoseconds) for yielding a spin lock.  Advanced configuration
		/// option, use judiciously. </summary>
		/// <param name="count"> the time (in nanoseconds) to yield a spin lock </param>
		/// <returns> this Builder object to allow methods to be chained </returns>
		Builder &withLockWait(const int count);

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

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);
    };

  protected:
    std::string m_filepath;
    bool m_enableLowLatency;

    ClientSHMTransportContext(Builder *builder);
    friend std::unique_ptr<ClientTransportContext> ClientTransportContextFactory::build(const std::string &url);

  public:
    /// <summary>
    /// This ClientTransportContext does not currently support Async which means that an exception
    /// will be thrown if you try to create an AsynchronousTransport using the TransportFactory.connect
    /// variant which takes callback objects. </summary>
    /// <returns> false </returns>
    virtual bool supportsAsync();

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

  protected:
    virtual std::string getConnectionDetail();
    virtual void validate();

  private:
    ClientSHMTransportContext(const ClientSHMTransportContext &copy);
    const ClientSHMTransportContext &operator=(const ClientSHMTransportContext &assign);
	void checkPath() const;
};
}
}
}