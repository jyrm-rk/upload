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
 * a join operation is attempted but cannot be completed
 */
class nUnsupportedJoinException :
    public nBaseAdminException {
  public:
    /**
     * Constructor for nUnsupportedJoinException.
     */
    nUnsupportedJoinException(void);

    /**
     * Constructor for nUnsupportedJoinException.
     * @param message optional message string to be appended to the error
     */
    nUnsupportedJoinException(const std::string& message);
};

}
}
}
}
