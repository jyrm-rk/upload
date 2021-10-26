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

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {

class fSubject;

class fDefaultLoginContext :
    public fClientLoginContext {
  public:
    virtual ~fDefaultLoginContext(void);

    virtual fLoginResponse* login(fDriver *pDriver);
    virtual fLoginResponse* login(fDriver *pDriver, fEventInputStream *pIstream, fEventOutputStream *pOstream);
    virtual void logout(fDriver *pDriver);
    void setResource(std::string& resourceID, std::string *pValues);
    virtual int getType();

    fDefaultLoginContext(fSubject *subject);
    fDefaultLoginContext(std::string username);
    fDefaultLoginContext();

  private:
    std::string m_IPAddress;
    std::string m_username;
    std::string m_defaultUsername;
    int IPUpdateCount;

    friend class fClientLoginContext;
};

}
}
}
}
