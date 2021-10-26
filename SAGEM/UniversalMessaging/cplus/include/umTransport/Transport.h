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



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Interface that defines methods common to all client Transports
/// </summary>
/// <seealso cref= com::softwareag::umtransport::SynchronousTransport </seealso>
/// <seealso cref= com::softwareag::umtransport::AsynchronousTransport </seealso>
class Transport {
  public:
    /// <summary>
    /// Close the Transport so it can no longer be used for communication
    /// </summary>
    virtual void close() = 0;

    /// <summary>
    /// Check to see whether this Transport has been closed already </summary>
    /// <returns> return true if the Transport is closed </returns>
    virtual bool isClosed() = 0;
};
}
}
}