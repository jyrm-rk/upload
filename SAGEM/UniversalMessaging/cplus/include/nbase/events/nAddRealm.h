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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

class nBaseRealm;

namespace events {

class nAddRealm :
    public nSynchronous {
  public:
    nAddRealm(void);
    nAddRealm(nBaseRealm *pNewRealm);
    virtual ~nAddRealm(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    void setSourceRealm(std::string source);

    nBaseRealm* getRealm();

  private:
    nBaseRealm *m_pRealm;
    std::string m_srcRealm;
};

}
}
}
}
}
