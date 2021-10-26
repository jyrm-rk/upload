/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBaseTransportObject.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
namespace security {

class fSubject;

using namespace fbase;
using namespace io;

class fAclEntry :
    public fBaseTransportObject, public CountableObject {
  public:
    fAclEntry();
    fAclEntry(fSubject *pSubject, longlong priv);
    virtual ~fAclEntry(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);
    virtual fSubject* getSubject();
    longlong getPriv();
    virtual void setPriv(longlong priv);
    virtual int getType ();

  private:
    fSubject *m_pSubject;
    longlong m_priv;
};

}
}
}
}
