/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ServerTransport.h"
#include "fServerDriver.h"



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// By establishing an AsynchronousServerTransport, new client connections will automatically be accepted
/// and notifications of new connections will be passed to the user implementation of AcceptHandler.
/// To create an AsynchronousServerTransport you must first create a ServerTransportContext and then
/// pass this to the TransportFactory.bind method with the required callback objects (AcceptHandler, DataHandler,
/// CloseHandler).
/// </summary>
class AsynchronousServerTransport : public ServerTransport {
  private:
    com::pcbsys::foundation::drivers::fServerDriver *const m_driver;

  protected:
    AsynchronousServerTransport(com::pcbsys::foundation::drivers::fServerDriver *drv);

  public:
	  virtual ~AsynchronousServerTransport();
    /// <summary>
    /// Call this to close the ServerTransport. This will stop further connections from being accepted.
    /// </summary>
    virtual void close();
    friend class TransportFactory;
};
}
}
}