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
#include "fExternalable.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fConnectionDetails;
}
}
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;
using namespace foundation::drivers;

class nBaseRealm : public fExternalable, public CountableObject {
  public:
    nBaseRealm(void);
    nBaseRealm(nBaseRealm *pRealm);
    nBaseRealm(std::string& name, std::string *pConnections, int nConnection);
    nBaseRealm(std::string& name, std::list<fConnectionDetails*> connections);
    virtual ~nBaseRealm(void);

    void readExternal (fEventInputStream *pIstream);
    void writeExternal (fEventOutputStream *pOstream);

    void setName(std::string& name);
    std::string getName();

    void setMountPoint(const std::string& mountPoint);
    const std::string getMountPoint();

    std::list<fConnectionDetails*>& getConnections();
    void setConnections(std::string *pConnections, int nConnection);

    unsigned char* getPublicKey(int& keyLength);
    void setPublicKey(unsigned char *pKey, int keyLength);

  protected:
    std::string m_name;
    std::string m_mountPoint;
    std::list<fConnectionDetails*> m_connections;
    unsigned char *m_pPublicKey;
    unsigned int m_publicKeyLength;
};

}
}
}
}
