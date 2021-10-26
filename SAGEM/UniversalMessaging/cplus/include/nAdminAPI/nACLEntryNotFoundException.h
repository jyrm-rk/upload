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
#include "nBaseAdminException.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
/**
 * represents the exception class that is thrown when
 * an acl entry is not found when an operation is attempted on it
 */
class nACLEntryNotFoundException :
    public nBaseAdminException {
  public:
    /**
     * Creates the Exception with the default constructor
     */
    nACLEntryNotFoundException(void);
    /**
     * Creates the Exception with the given message
     * @param message Message
     */
    nACLEntryNotFoundException(const std::string& message);
};

}
}
}
}
