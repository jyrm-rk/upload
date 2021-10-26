/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSynchronous.h"

#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nbase {
class nSecureRealm;
}
namespace nAdmin {
namespace events {

using namespace nbase;
using namespace nbase::events;
using namespace foundation::io;

class nRealmMap :
    public nSynchronous {
  public:
    nRealmMap(void);
    virtual ~nRealmMap(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);

    virtual std::list<nSecureRealm*>& getRealms();

  private:
    std::list<nSecureRealm*> m_realmList;
};

}
}
}
}
}
