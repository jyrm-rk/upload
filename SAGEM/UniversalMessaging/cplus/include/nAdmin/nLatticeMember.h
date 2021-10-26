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
#include "nClusterIdFactory.h"
#include "fSortedList.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {

class nClusterMember;
class nLatticeEntry;
class nClusterEngineStateMonitor;
class nClusterIdFactory;

using namespace foundation::fbase;
using namespace foundation::collections;

class nLatticeMember :
    public fExternalable, public nClusterIdFactory, public CountableObject {
  public:
    nLatticeMember(void);
    virtual ~nLatticeMember(void);

    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);
    virtual longlong getClusterRequestId();

    virtual const std::string& getName();
    virtual const std::string& getSiteName();
    virtual bool isPrimeSite();
    virtual fSortedList<std::string, nLatticeEntry*>& getEntries();
    virtual const std::string& getMaster();
    virtual bool canBeMaster();
    virtual int getState();

  private:
    nClusterMember *m_pMember;
    fSortedList<std::string, nLatticeEntry*> m_entries;
    std::string m_master;
    nClusterEngineStateMonitor *m_pEngine;
    bool m_bLocal;
    int m_state;
    longlong m_lastClusterRequestId;
    nClusterIdFactory *m_pFactory;
};

}
}
}
}
