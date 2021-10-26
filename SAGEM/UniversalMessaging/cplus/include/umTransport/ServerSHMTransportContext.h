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
#include "fSharedMemoryConfig.h"
#include <string>
#include "Poco/URI.h"

using namespace com::pcbsys::foundation::drivers::configuration;



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Constructed using the ServerSHMTransportContext.Builder.  All information must be set on the Builder
/// so that when this object is built, it is validated.  It is used to create Transport objects using
/// TransportFactory.connect. Communication on the transport is transmitted using Shared Memory.
/// </summary>
class UMTRANSPORTDLL ServerSHMTransportContext : public ServerTransportContext {
  public:
    /// <summary>
    /// This Builder object is used to build a ServerSHMTransportContext.  The ServerSHMTransportContext
    /// is configured using the builder so that once build() is called, the ServerSHMTransportContext is
    /// only returned if it is valid.  You can use the Builder to create simple readable code like this:
    /// \code
    ///  context = ServerSHMTransportContext::Builder()
    ///            .withFilePath("/path/to/directory")
    ///            .build();
    /// \endcode
    /// </summary>
    class UMTRANSPORTDLL Builder : public ServerContextBuilder {
      protected:
        Builder(Poco::URI *url);
        friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);
        virtual ServerSHMTransportContext *buildTransport();

      public:
        /// <summary>
        /// Construct a new instance of this Builder object.
        /// </summary>
        Builder();

        /// <summary>
        /// Builds the ServerSHMTransportContext based on the configuration that has been set on the Builder. </summary>
        /// <exception cref="IllegalStateException"> if the Builder has not be configured with the required/correct
        /// information to construct the ServerTransportContext; </exception>
        /// <returns> ServerSHMTransportContext used by the TransportFactory.bind method to construct ServerTransports </returns>
        std::unique_ptr<ServerTransportContext> build();

		/// <summary>
		/// Set the path to the directory which will be used to store the memory mapped files used
		/// by the SHM Transport. </summary>
		/// <param name="path"> of the directory used for communication </param>
		/// <returns> this Builder object to allow methods to be chained </returns>
        Builder &withFilePath(const std::string &path);

		/// <summary>
		/// Sets the time in ms that the SHM Transport should wait for information before timing out a
		/// connection
		/// </summary>
		/// <param name="timeout"> the timeout that will be bound to by the ServerTransport in milliseconds </param>
		/// <returns> this Builder object so that method calls can be chained </returns>
        Builder &withTimeout(int timeout);

		/// <summary>
		/// Set the buffer size in bytes that will be used by the SHM  ServerTransports </summary>
		/// <returns> this Builder object so that methods can be chained </returns>
        Builder &withBufferSize(int bufferSize);

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
		/// Returns the current time in ms that the SHM Transport should wait for  information before 
		/// timing out a connection
		/// </summary>
		/// <returns> the timeout that this Builder will set for the ServerTransportContext </returns>
        int getTimeout();

		/// <summary>
		/// Get the file path that is currently set.  The path will be used to store the memory mapped files
		/// required by the SHM Transport. </summary>
		/// <returns> the file path that will be used by the Transport </returns>
        std::string getFilePath();

		/// <summary>
		/// Get the buffer size in bytes that will be used by the ServerTransports </summary>
		/// <returns> the size that has been set for the buffer </returns>
        int getBufferSize();

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

      private:
        Builder(const Builder &copy);
        const Builder &operator=(const Builder &assign);

        virtual int getDefaultBufferSize();
        virtual int getDefaultTimeout();
    };

  private:
    fSharedMemoryConfig *const m_config;

  private:
    ServerSHMTransportContext(Builder *builder);
    friend std::unique_ptr<ServerTransportContext> ServerTransportContextFactory::build(const std::string &url);

	static const int DEFAULT_READBUFFER_SIZE = 1024000;
	static const int DEFAULT_TIMEOUT = 20000;

  public:
     /// <summary>
     /// Class destructor
     /// </summary>
    ~ServerSHMTransportContext();

    /// <summary>
    /// Get the path that will be used by ServerTransports created using this context.  The path
    /// is used to store the memory mapped files required for shared memory communication. </summary>
    /// <returns> String file path set for this ServerContext </returns>
    std::string getFilePath();

    /// <summary>
    /// Get the buffer size in bytes that will be used by ServerTransports created using this ServerTransportContext 
	/// </summary>
    /// <returns> the size that has been set for the buffer.  Returns a default value if the value is not set, or
	/// could not be converted/translated.  </returns>
    int getBufferSize();

    /// <summary>
    /// The time in ms that the SHM Transport will wait for information before timing out a connection </summary>
    /// <returns> time in ms before an idle connection is closed.  Returns a default value if the value is not set,
	/// or could not be converted/translated.  </returns>
    int getTimeout();

	/// <summary>
	/// Gets the current active spin count.  Advanced option for SHM transports only.  </summary>
	/// <returns> the spin count used by the SHM Transport.  Returns a default value if the value is not set, 
	/// or could not be converted/translated.  </returns>
	longlong getSpinCount();

	/// <summary>
	/// Get the current wait time for yielding a spin lock.  Advanced option for SHM transports only.  </summary>
	/// <returns> the wait time (in nanoseconds) used by the SHM Transport.  Returns a default value if the value is 
	/// not set, or could not be converted/translated.  </returns>
	int getLockWait();

    /// <summary>
    /// This ServerTransportContext does not currently support Async which means that an exception
    /// will be thrown if you try to create an AsynchronousServerTransport using the TransportFactory.bind
    /// variant which takes callback objects. </summary>
    /// <returns> false </returns>
    virtual bool supportsAsync();

  protected:
    virtual fDriverConfig *getConfig();
    virtual void validate();

  private:
    void checkBufferSize() const;
    void checkTimeout() const;
    void checkPath() const;

    ServerSHMTransportContext(const ServerSHMTransportContext &copy);
    const ServerSHMTransportContext &operator=(const ServerSHMTransportContext &assign);
};
}
}
}