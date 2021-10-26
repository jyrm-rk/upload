/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Exception.h"

#include <string>


namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
/**
 * represents the base class for all admin API exceptions
 */
class nBaseAdminException :
    public com::pcbsys::foundation::fbase::Exception {
  public:
    /**
     * Creates the Exception with the given message
     * @param msg Message
     */
    nBaseAdminException(const std::string& msg);
};

}
}
}
}
