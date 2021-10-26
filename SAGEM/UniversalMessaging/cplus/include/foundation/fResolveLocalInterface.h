/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fDriver.h"
#include "Poco/Net/IPAddress.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace util {
using namespace com::pcbsys::foundation::drivers;

class fResolveLocalInterface {
  public:
    static Poco::Net::IPAddress* resolveLocalInterface(fDriver* driver, bool isIPV6);
    static Poco::Net::IPAddress* resolveLocalInterface(std::string ipaddress, bool isIPV6);
  private:
    static Poco::Net::IPAddress* checkValidInterface(Poco::Net::IPAddress* inter, bool isIPV6);
    static Poco::Net::IPAddress* findPossibleValidInterface(bool isIPV6);
};

}
}
}
}
