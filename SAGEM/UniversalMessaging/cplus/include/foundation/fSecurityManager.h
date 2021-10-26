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
#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSubject;
}
}
}
}

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSecurityManager {
  public:
    fSecurityManager();
    ~fSecurityManager();
    static fSecurityManager* getInstance();
    fSubject* getDefaultSuperUser();
    virtual fSubject* getEveryoneUser();
    virtual fSubject* getEveryoneGroup();
    std::list<fSubject*> getAdmins();

  private:
    static const std::string sDefaultUsername;
    static fSecurityManager* myInstance;

    std::list<fSubject*> msAdmins;
    fSubject* msEveryoneUser;
    fSubject* msDefaultSuperUser;
    fSubject* everyoneGroup;
};
}
}
}
}
