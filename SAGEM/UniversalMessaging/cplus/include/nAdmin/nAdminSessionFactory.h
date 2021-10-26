/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSessionFactory.h"

#include "Poco/Mutex.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nSessionAttributes;
class nReconnectHandler;
}
namespace nAdmin {


class nAdminSession;

using namespace com::pcbsys::nirvana::client;

class nAdminSessionFactory :
    public nSessionFactory {
  public:
    static nAdminSession* createAdmin(nSessionAttributes *pAttr, nReconnectHandler *pHandler, const std::string& username);
    static nAdminSession* createAdmin(nSessionAttributes* attr, const std::string& username);

  private:
};

}
}
}
}
