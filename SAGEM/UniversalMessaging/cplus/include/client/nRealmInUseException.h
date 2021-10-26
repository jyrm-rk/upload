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
 * This exception is thrown when an attempt is made to remove a realm from another
 * realm when the realm is part of a cluster or has channels that are joined in the requesting realm
 *
 * @see nRealm
 * @see nSession
 */
class nRealmInUseException :
    public nBaseClientException {
  public:
    nRealmInUseException(void);
    nRealmInUseException(const std::string& msg);

    virtual int getType();

};

}
}
}
}
