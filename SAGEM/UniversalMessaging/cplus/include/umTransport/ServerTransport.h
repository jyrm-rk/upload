/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Interface that defines methods common to all ServerTransports </summary>
/// <seealso cref= com::softwareag::umtransport::SynchronousServerTransport </seealso>
/// <seealso cref= com::softwareag::umtransport::AsynchronousServerTransport </seealso>
class ServerTransport {
  public:
    /// <summary>
    /// Close this ServerTransport so that it will no longer accept connections
    /// </summary>
    virtual void close() = 0;
};
}
}
}