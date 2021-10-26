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

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fDriver;
}

namespace io {
class fEventInputStream;
class fEventOutputStream;
}

using namespace drivers;
using namespace io;

namespace security {

class fLoginResponse;
class fSubject;

class fLoginContext : public fbase::Countable{
  public:
    fLoginContext(void);
    fLoginContext(fSubject *subject);
    virtual ~fLoginContext(void);

    virtual fLoginResponse* login(fDriver *pDriver) = 0;
    virtual fLoginResponse* login(fDriver *pDriver, fEventInputStream *pIStream,
                                  fEventOutputStream *pOStream) = 0;
    virtual void logout(fDriver *pDriver) = 0;
    virtual int getType() = 0;

    void setSubject (fSubject *pSubject);
    fSubject* getSubject();

    static const int DEFAULTLOGINCONTEXT = 1000;
    static const int SSLLOGINCONTEXT = 1001;

  private:
    fSubject *m_pSubject;
};

}
}
}
}
