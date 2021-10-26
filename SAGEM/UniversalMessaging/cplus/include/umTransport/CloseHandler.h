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
class AsynchronousTransport;
/// <summary>
/// The CloseHandler interface is passed to the TransportFactory.bind method when you want to
/// create and AsynchronousServerTransport or to the TransportFactory.connect method when you
/// want to create client side AsynchronousTransports.  The object which implements this
/// interface will be notified when Transports are closed.
/// </summary>
class CloseHandler {
    /// <summary>
    /// This method will be called when an AsynchronousTransport is closed.
    /// </summary>
    /// <param name="transport"> The Transport that has been closed </param>
  public:
    virtual void onClose(AsynchronousTransport *transport) = 0;
};
}
}
}