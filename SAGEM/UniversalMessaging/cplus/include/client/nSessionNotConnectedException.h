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
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

/**
 * The current nSession is not currently connected. This could be caused by the
 * network being down or the server.
 *
 * @see nSession
 * @see nChannel
 * @see nTransaction
 */
class nSessionNotConnectedException :
    public nBaseClientException {
  public:
    nSessionNotConnectedException();
    nSessionNotConnectedException(std::string msg);

    virtual int getType();
};

}
}
}
}
