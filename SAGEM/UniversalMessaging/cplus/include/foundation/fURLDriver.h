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

namespace Poco {
class URI;
class Timespan;

namespace Net {
class HTTPClientSession;
}

}

namespace com {
namespace pcbsys {
namespace foundation {
namespace Net {
class fURLStream;
}
namespace drivers {


class fConnectionDetails;

class fURLDriver :
    public fDriver {
  public:
    virtual ~fURLDriver(void);

    virtual Stream* getOutputStream();
    virtual Stream* getInputStream();
    virtual const std::string getId();
    virtual const std::string getLocalId();
    virtual fConnectionDetails* getConnectionDetails();
    virtual void updateResource(std::string resourceID, std::string *pValues);
    virtual void setTimeout(Poco::Timespan value);
    virtual int getTimeout();
    virtual bool supportAsyncReading();
    virtual bool supportAsyncWriting();

    virtual void close();

    void makeConnection();

    void send (unsigned char *pBuffer, int length);

    static int sReadTimeout;

  private:
    static std::string sMyServlet;
	static std::string sMyConnectionTypeKey;
	static std::string sMyInitialConnectionType;
    static std::string sMyConnectionType;
    static std::string sMyContentType;
	static std::string sClientHTTPCookieKey;
	static std::string sServerHTTPCookieKey;
	static std::string sServerSessionCookieKey;

    std::string myHTTPCookie;

    fURLDriver(std::string host, int port, std::string file, fLoginContext *pContext, bool ssl);
	void initSSL();

    bool m_bSSL;
    std::string m_host;
    int m_port;
    fURLStream *m_pIn;
    fURLStream *m_pOs;
    std::string m_file;
    std::string m_cookie;
    Poco::URI *m_pRequest;
    Poco::Net::HTTPClientSession *m_pHttpPrimarySession;
    std::istream *m_pInStream;
    Poco::Net::HTTPClientSession *m_pHttpSendSession;
	std::string HTTPVersion;

    friend class fDriverFactory;

};

}
}
}
}
