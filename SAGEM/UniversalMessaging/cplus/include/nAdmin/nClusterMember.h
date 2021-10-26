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
#include "Poco/Mutex.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nAdmin {

using namespace foundation::fbase;
using namespace foundation::io;

class nClusterMember :
    public fBaseTransportObject {
  public:
    nClusterMember(void);
    nClusterMember(std::string name, bool canMaster, unsigned char uniqueRealmId);
    virtual ~nClusterMember(void);

    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);

    const std::string& getName();
    const std::string& getSiteName();
    bool canBeMaster();
    bool isPrimeSite();

    signed char getUniqueRealmId();
    void setUniqueRealmId(signed char _myUniqueRealmId);

  private:
    std::string m_realmName;
    std::string m_siteName;
    bool m_bCanBeMaster;
    bool m_bPrimeSite;
    Poco::Mutex m_writeMutex;
    signed char myUniqueRealmId;
};

}
}
}
}
