/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "forwarddeclare.h"
#include "Poco/Exception.h"
#include <string>



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Abstract class that defines methods common to all TransportContexts </summary>
/// <seealso cref= com::softwareag::umtransport::ServerTransportContext </seealso>
/// <seealso cref= com::softwareag::umtransport::ClientTransportContext </seealso>
class TransportContext {
  protected:
    static const std::string URL_PARSE_ERROR;
    static const std::string URL_USAGE;
    static void checkPort(int port);
    static void checkHost(const std::string &host);

  public:
    virtual ~TransportContext() {}

    /// <summary>
    /// Check whether or not this TransportContext will create Tranports which support\
    /// asynchronous callbacks </summary>
    /// <returns> true if the Transport supports asynchronous callbacks </returns>
    virtual bool supportsAsync() = 0;

  protected:
    virtual void validate() = 0;
};
}
}
}