/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fLoginContext.h"
#include "fBase.h"
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {

class fClientLoginContext :
    public fLoginContext {
  public:
    virtual ~fClientLoginContext(void);
    fClientLoginContext(fSubject *subject);

    static fLoginContext* getInstance(std::string protocolID, std::string& username);
    static fLoginContext* getInstance(std::string protocolID);
    static DLL void reset();
    void setVirtualHostName(std::string name);
    int getType();

  protected:
    fClientLoginContext(void);
    std::string myVirtualHostName;
    void createSubject(std::string ipAddress, std::string username);

  private:
    static bool m_bUseContext;
};

}
}
}
}
