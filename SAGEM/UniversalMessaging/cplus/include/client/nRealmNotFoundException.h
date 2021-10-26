/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nBaseClientException.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

/**
 * The specified realm was not found on the server. This could mean that the
 * realm was either deleted on the server or has not been added.
 *
 * @see nChannel
 * @see nSession
 */
class nRealmNotFoundException :
    public nBaseClientException {
  public:
    nRealmNotFoundException(void);
    nRealmNotFoundException(const std::string& msg);

    virtual int getType();

};

}
}
}
}
