/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>
#include "Poco/Timespan.h"
#include "Poco/Net/SocketAddress.h"
#include "fConnectionDetails.h"
#include "fVendorDriver.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fLoginContext;
class fSubject;
}
namespace Net {
class Stream;
}
namespace drivers {

class fConnectionDetails;

using namespace security;
using namespace Net;

class fDriver : public com::pcbsys::foundation::fbase::Countable {
  public:
    virtual ~fDriver(void);

    virtual void open();
    virtual Stream* getOutputStream() = 0;
    virtual Stream* getInputStream() = 0;
    virtual const std::string getId() = 0;
    virtual const std::string getLocalId() = 0;
    virtual fConnectionDetails* getConnectionDetails() = 0;
    virtual void setTimeout(Poco::Timespan value) = 0;
    virtual int getTimeout() = 0;
    virtual void close();
    virtual bool getIsClosed();
    virtual void updateResource(std::string resourceID, std::string *pValues);
    virtual void setSubject(fSubject *pSub);
    virtual fSubject* getSubject();
    virtual Poco::Net::IPAddress* getLocalAddress();
    virtual bool isIPC();
    virtual bool supportAsyncReading()=0;
    virtual bool supportAsyncWriting()=0;
    void start();
    static void debugLog(std::string msg);
    std::string getType();
    void setDriver(fVendorDriver* driver);

  protected:
    fDriver(fLoginContext *pAuthHandler);
    void setID(std::string id);

    fLoginContext *m_pAuthHandler;
    std::string m_type;
    std::string m_protocolId;
    int m_weight;
    std::string m_id;
    std::string m_localID;
    fSubject *m_pSubject;
    fConnectionDetails *m_pConnDet;
    fVendorDriver *m_server;
    bool isClosed;
};

}
}
}
}
