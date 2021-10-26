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
namespace nirvana {
namespace nbase {

class nBaseRealm;

namespace events {

class nGetRealm :
    public nSynchronous {
  public:
    nGetRealm(void);
    nGetRealm(const std::string& name);
    nGetRealm(bool all);
    virtual ~nGetRealm(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    std::string getName();
    nBaseRealm* getRealm();
    nBaseRealm** getRealms(int& numRealm);
    virtual void setIsAdmin(bool admin);
    bool isAdmin();

  private:
    std::string m_realmName;
    nBaseRealm *m_pRealm;
    std::list<nBaseRealm*> m_realms;
    bool m_bGetAll;
    bool m_isAdmin;
};

}
}
}
}
}
