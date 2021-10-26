/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "AsynchronousTransport.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// This interface is passed to TransportFactory.connect when you want to create an
/// AsynchronousTransport.  The onConnect method will be called when the Transport connects.
/// </summary>
class ConnectHandler {
  public:
    /// <summary>
    /// Called when the AsynchronousTransport has connected to the server
    /// </summary>
    /// <param name="transport"> the Transport which is no connected
    /// @return </param>
    virtual void onConnect(AsynchronousTransport *transport) = 0;
};
}
}
}