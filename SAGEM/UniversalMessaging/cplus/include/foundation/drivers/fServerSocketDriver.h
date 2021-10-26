/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fMonitorable.h"
#include "fDriverConfig.h"
#include "fAcceptHandler.h"
#include "fServerDriver.h"
#include "fServerLoginContext.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"


namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {

class fServerSocketDriver : public fServerDriver, public virtual fVendorDriver, public virtual com::pcbsys::foundation::base::fMonitorable {
  public:
    fServerSocketDriver(com::pcbsys::foundation::drivers::configuration::fDriverConfig* config, com::pcbsys::foundation::drivers::handlers::fAcceptHandler* aHandler, const std::string& alias);
    virtual ~fServerSocketDriver();
    virtual void initialise();

    fDriver* performAccept();
    virtual bool validate(fDriver* driver);
    void close();

  protected:
    virtual void createServerSocket(configuration::fDriverConfig* config);
    virtual fDriver* createDriver(const Poco::Net::StreamSocket& socket);
    std::string m_protocolID;
    fServerLoginContext* m_context;
    int m_recvBufferSize;
    int m_sendBufferSize;
    int m_timeout;
    fConnectionDetails *m_connDetails;
    Poco::Net::ServerSocket m_serversocket;
};

}
}
}
}

