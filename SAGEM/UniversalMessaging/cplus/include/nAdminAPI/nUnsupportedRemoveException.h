/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nBaseAdminException.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

/**
 * represents the exception class that is thrown when
 * a remove operation is attempted but cannot be completed
 */
class nUnsupportedRemoveException :
    public nBaseAdminException {
  public:

    /**
     * Constructor for nUnsupportedRemoveException.
     */
    nUnsupportedRemoveException(void);

    /**
     * Constructor for nUnsupportedRemoveException.
     * @param message optional message string to be appended to the error
     */
    nUnsupportedRemoveException(const std::string& message);
};

}
}
}
}
