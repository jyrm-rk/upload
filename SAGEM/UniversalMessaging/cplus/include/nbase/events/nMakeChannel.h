/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nBaseUser.h"
#include "nBaseStorePermission.h"
#include <vector>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;

namespace events {

class nMakeChannel :
    public nBaseUser {
  public:
    nMakeChannel(void);
    nMakeChannel(nBaseChannelAttributes *pAttrib, longlong startEID = -1, longlong mask = -1, std::vector<nBaseStorePermission>* m_permissions = NULL);
    nMakeChannel(nBaseChannelAttributes *pAttrib, std::vector<nBaseStorePermission>* m_permissions);
    virtual ~nMakeChannel(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

  protected:
    longlong m_startEID;
    longlong m_mask;
    std::vector<nBaseStorePermission>* m_permissions;
};

}
}
}
}
}
