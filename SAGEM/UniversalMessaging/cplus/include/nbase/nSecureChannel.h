/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fExternalable.h"
#include "fSortedList.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclEntry;
class fAclList;
}
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nbase {

class nBaseChannelAttributes;

using namespace foundation::fbase;
using namespace foundation::collections;
using namespace foundation::security;

class nSecureChannel :
    public fExternalable, public CountableObject {
  public:
    nSecureChannel(nBaseChannelAttributes* att, fAclList* acls);
    nSecureChannel(void);
    virtual ~nSecureChannel(void);

    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);

    virtual nBaseChannelAttributes* getAttributes();
    virtual fAclList* getACL();
    virtual std::string getName();
    virtual int getType ();

  private:
    nBaseChannelAttributes *m_pAttributes;
    fAclList* m_ACL;
};

}
}
}
}
