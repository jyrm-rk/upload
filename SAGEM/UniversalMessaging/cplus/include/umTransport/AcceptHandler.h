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

/// <summary>
/// Universal Messaging Transport API Package
/// </summary>



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// This interface is passed to TransportFactory.bind when you want to create an AsynchronousServerTransport.
/// The onAccept method will be invoked whenever a client connected to the ServerTransport.
/// </summary>
class AcceptHandler {
  public:
    /// <summary>
    /// This is invoked when a client connects to the AsynchronousServerTransport
    /// </summary>
    /// <param name="transport"> the client Transport that has just connected </param>
    virtual void onAccept(AsynchronousTransport *transport) = 0;
};
}
}
}