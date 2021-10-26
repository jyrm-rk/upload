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
#include <string>
#include <memory>



namespace com {
namespace softwareag {
namespace umtransport {

/// <summary>
/// This factory allows you to construct ClientTransportContexts by passing a String URL.  This way you can
/// compile an application which is Transport agnostic and simply change the URL passed to the application to
/// switch from SHM to Sockets etc.
/// A URL is of the form protocol://host:port?Property=value&Property2=value2
/// The relevant ClientContextBuilder will be constructed based on the protocol and then the properties
/// will be set internally.  So on a ClientSHMTransportContext there is a property called "LowLatency"
/// that you could set to true using a URL like this:
///   \code
///     std::string url = "shm://localhost:/path/to/file?LowLatency=true";
///     ClientTransportContext *context = ClientTransportContextFactory::build(url);
///  \endcode
/// </summary>

class UMTRANSPORTDLL ClientTransportContextFactory {
  public:
    /// <summary>
    /// Creates a ClientContextBuilder based on the protocol in the url and sets the host/port (the port is a
    /// file path in SHM) as well as any other parameters which are passed in the url query string.
    /// For example you can construct a ClientSocketTransportContext like this:
    /// \code
    /// ClientTransportContext *context = ClientTransportContextFactory::build("tcp://locahost:9000"); </summary>
    /// <param name="ur"> protocol://host:port?property1=value provides the required information to construct a ClientContextBuilder
    /// @return </param>
    static std::unique_ptr<ClientTransportContext> build(const std::string &url);
};
}
}
}
