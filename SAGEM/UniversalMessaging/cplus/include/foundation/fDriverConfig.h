/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fDefaultSecureObject.h"
#include "fExternalable.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
namespace drivers {
namespace configuration {

using namespace fbase;
using namespace security;
using namespace io;

class fDriverConfig :
    public fDefaultSecureObject, public CountableObject {
  public:
    fDriverConfig(void);
    fDriverConfig(const std::string& name, const std::string& protocol, const std::string& adapter, int port, bool autoStart = true);
    virtual ~fDriverConfig(void);

    virtual int getType();
    virtual const std::string& getName();
    virtual const std::string& getProtocol();
    virtual const std::string& getAdapter();
    virtual int getPort();
    virtual int getThreadCount();
    virtual int getBacklog();
    virtual int getAuthTimeOut();
    virtual bool canAdvertise();
    virtual bool getAutoStart();
    virtual const std::string& getAlias();
    virtual int getReadBufferSize();
    virtual int getWriteBufferSize();
    virtual bool isAllowInterRealm();
    virtual bool isAllowClientConnections();
    virtual bool isAllowNIO();
    virtual int getSelectorPoolSize();
    virtual void setName(const std::string& name);
    virtual void setBacklog(int backlog);
    virtual void setAdapter(const std::string& adapter);
    virtual void setAuthTimeOut(int authTimeOut);
    virtual void setPort(int port);
    virtual void setThreadCount(int threadCount);
    virtual void setAdvertise(bool bAdvertise);
    virtual void setAutoStart(bool bAutoStart);
    virtual void setAlias(const std::string& alias);
    virtual void setWriteBufferSize(int writeBufferSize);
    virtual void setReadBufferSize(int readBufferSize);
    virtual void setAllowInterRealm(bool bAllowInterRealm);
    virtual void setAllowClientConnections(bool bAllowClientConnections);
    virtual void setAllowNIO(bool bAllowNIO);
    virtual void setSelectorPoolSize(int selectorPoolSize);

    std::string* getACLNames(int &nName);
    std::string* getACLDescriptions(int &nDescription);

    virtual void readOrigExternal(fEventInputStream *pEis);
    virtual void readOldExternal(fEventInputStream *pEis);
    virtual void readExternal(fEventInputStream *pEis);
    virtual void writeExternal(fEventOutputStream *pEis);

    std::string getURL();

    static const int DEFAULT_READ_BUFFER_SIZE;
    static const int DEFAULT_WRITE_BUFFER_SIZE;

  protected:
    std::string m_name;
    std::string m_protocol;
    std::string m_adapter;
    int m_port;
    int m_poolSize;
    int m_backlog;
    int m_authTimeOut;
    bool m_bAdvertise;
    bool m_bAutoStart;
    std::string m_alias;
    int m_readBufferSize;
    int m_writeBufferSize;
    bool m_bAllowInterRealm;
    bool m_bAllowClientConnections;
    bool m_bAllowNIO;
    int m_selectorPoolSize;
    bool m_bEnablePolicyServer;

    bool EnableHttp11;
    bool enableWebSockets;
    bool hasExtraConfig;
    bool nativeCometAllowed;
    bool enableGZIP;
    bool hasCORSConfig;
};

}
}
}
}
}
