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
#include "fBaseTransportObject.h"
#include "fPrincipal.h"

#include <list>
#include <vector>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventOutputStream;
class fEventInputStream;
}

using namespace fbase;
using namespace io;

namespace security {
class fCredential;

using namespace com::pcbsys::foundation::security;
class fSubject :
    public fBaseTransportObject, public Countable {
  public:
    fSubject();
    fSubject(const std::string subject);
    fSubject(const std::string username, const std::string host);
    fSubject(std::vector<fPrincipal*>& principals, std::list<fCredential*>& pubCredentials,
             std::list<fCredential*>& privCredentials);
    virtual ~fSubject(void);

    void writeExternal (fEventOutputStream *pOstream);
    void writeExternalfSubject (fEventOutputStream *pOstream);
    std::vector<fPrincipal*>& getPrincipals();
    std::list<fCredential*>& getPublicCredentials();
    std::list<fCredential*>& getPrivateCredentials();
    int readType(fEventInputStream *eis);
    longlong readMask(fEventInputStream *eis);
    virtual void readExternal(fEventInputStream *pIstream);
    void readExternalfSubject( fEventInputStream *pIstream, int iprLength );

    std::string getUser();
    std::string getKey();
    std::string toString();
    std::string getHost();
    virtual bool isGroup();
    std::string getName();

    static const int Subject = 0;
    static const int Group = 2;

    static fSubject* parseFromExternal(fEventInputStream *pIstream);
  protected:
    longlong mask;
    bool _isGroup;
    std::string m_key;
  private:
    std::vector<fPrincipal*> m_principals;
    std::list<fCredential*> m_pubCredentials;
    std::list<fCredential*> m_privCredentials;
    std::string m_user;
    std::string m_host;

    friend class fAclGroup;

};

}
}
}
}
