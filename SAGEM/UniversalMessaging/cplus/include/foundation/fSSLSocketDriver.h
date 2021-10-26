/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fSocketDriver.h"
#include "Poco/Net/SecureStreamSocket.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {

class fSSLSocketDriver :
    public fSocketDriver {
  public:
    fSSLSocketDriver(std::string host, int port, fLoginContext *pContext);
    fSSLSocketDriver(std::string host, int port, fLoginContext *pContext, Poco::Net::StreamSocket *pProxy);
    virtual ~fSSLSocketDriver(void);

    bool supportAsyncReading();
    bool supportAsyncWriting();
    virtual void updateResource(std::string resourceID, std::string *pValues);
    virtual void close();

  protected:
    virtual void createSocket();
    virtual void setupSocket();
    fSSLSocketDriver(const Poco::Net::SecureStreamSocket& socket, fLoginContext *pContext);
        
    friend class fSSLServerSocketDriver;
        
};

}
}
}
}
