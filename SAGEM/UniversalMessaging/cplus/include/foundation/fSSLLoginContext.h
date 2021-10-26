/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fClientLoginContext.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {

class fSSLLoginContext :
    public fClientLoginContext {
  public:
    virtual ~fSSLLoginContext(void);

    virtual fLoginResponse* login(fDriver *pDriver);
    virtual fLoginResponse* login(fDriver *pDriver, fEventInputStream *pIStream,
                                  fEventOutputStream *pOStream);
    virtual void logout(fDriver *pDriver);
    virtual int getType();

    void setResource(std::string resourceID, std::string *pPrms);

  protected:
    void init2();

  private:
    fSSLLoginContext(void);
    fSSLLoginContext(std::string& username);

    int IPUpdateCount;
    std::string m_IPAddress;
    std::string m_username;

    friend class fClientLoginContext;

};

}
}
}
}
