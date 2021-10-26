/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"
#include "fBaseObject.h"
#include "fDriver.h"
#include "fConnectionDetails.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Thread.h"
#include "Poco/Net/StreamSocket.h"
#include "TcpStream.h"

#include <list>

namespace Poco {
namespace Net {
class StreamSocket;
}
}

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {

using namespace fbase;

class fDriverFactory :
    public fBaseObject {
  public:
    fDriverFactory();
    DLL fDriverFactory(std::string username);
	DLL fDriverFactory(bool isUMTransport);
    virtual DLL ~fDriverFactory(void);
    DLL fDriver* connect(int retryCount);
    DLL void addConnection(std::string URL);
    DLL void addConnection(fConnectionDetails* details);
    DLL Poco::Net::StreamSocket* getProxySocket(Poco::URI *proxy, Poco::URI *site);
    std::list<fConnectionDetails*>& getConnectionList();

	bool incrementConnectionList();

  private:
    fDriver* doConnect(std::list<fConnectionDetails*>& connectionList, std::string& username);

  protected:
    fDriver* attemptConnection(fConnectionDetails *pCd, std::string& username, Poco::Net::StreamSocket *pProxy);
    std::list<fConnectionDetails*> m_connectionList;
    std::string m_username;
	bool m_isUMTransport;

    friend class nSession;
};

}
}
}
}

