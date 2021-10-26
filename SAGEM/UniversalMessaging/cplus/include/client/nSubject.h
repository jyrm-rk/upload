/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSubject;
class fPrincipal;
class fAclGroup;
}
}
namespace nirvana {
namespace nAdminAPI {
class nACLEntry;
class nSecurityGroup;
}
namespace client {

using namespace foundation::security;

/**
 * This class contains information about the user identification used by Nirvana
 */
class nSubject {
  public:
    /**
     * Create a new nSubject using an AclGroup instance
     *
     * @param grp acl group instance
     */
    DLL nSubject(fAclGroup* grp);

    /**
     * Create a new nSubject using a string
     *
     * @param sub user@host string
     */
    DLL nSubject(std::string sub);
    DLL virtual ~nSubject(void);

    /**
    * The username being used by this subject
    *
    * @return String username
    */
    DLL std::string getUser();

    /**
    * Converts this object into a string
    *
    * @return string representation of this subject
    */
    DLL std::string toString();

    /**
    * The host name for this subject. This can mean the host of the local machine
    *
    * @return String hostname
    */

    DLL std::string getHost();

    /**
     * The Name being used by this subject
     * @return String name
     */
    DLL std::string getName();

    /**
     * The fSubject instance being used by this object
     * @return fSubject instance
     */
    DLL fSubject* getSubject();

    DLL bool isGroup();

  protected:
    nSubject(fSubject *pSub);
    nSubject();


  private:
    nSubject(fPrincipal *pSub);
    fSubject *m_pMapper;

    friend class nSession;
    friend class com::pcbsys::nirvana::nAdminAPI::nACLEntry;
    friend class com::pcbsys::nirvana::nAdminAPI::nSecurityGroup;

};

}
}
}
}
