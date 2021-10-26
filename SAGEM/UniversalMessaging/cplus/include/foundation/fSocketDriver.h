/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fDriver.h"
#include "Stream.h"

#include <string>

namespace Poco {
class Timespan;
namespace Net {
class StreamSocket;
}
}

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {

using namespace Net;

class fSocketDriver :
    public fDriver {
  public:
    virtual ~fSocketDriver(void);

    virtual Stream* getOutputStream();
    virtual Stream* getInputStream();
    virtual void updateResource(std::string resourceID, std::string *pValues);
    virtual fConnectionDetails* getConnectionDetails();
    virtual const std::string getLocalId();
    virtual void close();
    virtual void setTimeout(Poco::Timespan value);
    virtual int getTimeout();
    virtual Poco::Net::IPAddress* getLocalAddress();
    virtual bool supportAsyncReading();
    virtual bool supportAsyncWriting();

  protected:
    DLL fSocketDriver(std::string host, int port, fLoginContext *pContext);
    DLL fSocketDriver(fLoginContext *pContext);				// KLUDGE to get around inheritance issue
    fSocketDriver(const Poco::Net::StreamSocket& socket, fLoginContext *pContext);
    virtual void createSocket(std::string host, int port);
    virtual void socketSetup();
    virtual const std::string getId();

    Poco::Net::StreamSocket *m_pSocket;
    Stream *m_pOstream;
    Stream *m_pIstream;
    std::string m_host;
    int m_port;

    friend class fDriverFactory;
    friend class fServerSocketDriver;
};

}
}
}
}

