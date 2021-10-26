/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fLoginContext.h"
#include "fDriver.h"
#include "fEventInputStream.h"
#include "fEventOutputStream.h"
namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fServerLoginContext : public fLoginContext {
  public:
    fServerLoginContext();
    virtual ~fServerLoginContext();

    virtual fLoginResponse* login(fDriver *pDriver);
    virtual fLoginResponse* login(fDriver *pDriver, fEventInputStream *pIStream, fEventOutputStream *pOStream);
    virtual void logout(fDriver *pDriver);
    virtual int getType();
    virtual fServerLoginContext* newInstance()=0;
    virtual std::string getRemoteAddress(drivers::fDriver* adriver);
};
}
}
}
}

