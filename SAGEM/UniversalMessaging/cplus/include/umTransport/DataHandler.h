/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ByteBuffer.h"



namespace com {
namespace softwareag {
namespace umtransport {
class AsynchronousTransport;
/// <summary>
/// This interface is passed to the TransportFactory.connect method when you want to create an
/// AsynchronousTransport.  It is also passed to the TransportFactory.bind method when you want an
/// AsynchronousServerTransport.  The onRead method will be called when data has been read from
/// the AsynchronousTransport.
/// </summary>
class DataHandler {
  public:
    /// <summary>
    /// Called when data has been read from transport. The data is passed to the user in a ByteBuffer. </summary>
    /// <param name="buffer"> ByteBuffer containing the data read from the Transport </param>
    /// <param name="transport"> The Transport that data has been read from </param>
    virtual void onRead(ByteBuffer *buffer, AsynchronousTransport *transport) = 0;	// TODO
};
}
}
}