/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fDriverConfig.h"
#include "fServerSocketDriver.h"
#include "fSHMServerDriver.h"
#include "fSSLServerSocketDriver.h"
#include <sstream>

using namespace com::pcbsys::foundation::drivers::configuration;
using namespace com::pcbsys::foundation::drivers::shm;

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fServerDriverFactory {

  public:
    static fServerDriver* getServerDriver(fDriverConfig* config, com::pcbsys::foundation::drivers::handlers::fAcceptHandler* aHandler, std::string alias);
};
}
}
}
}