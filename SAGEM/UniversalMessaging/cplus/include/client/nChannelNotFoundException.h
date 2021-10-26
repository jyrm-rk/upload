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
 * The specified channel could not be located on the server. Check the name
 * of the channel or the realm you are connected to.
 *
 * @see nSession
 * @see nChannel
 * @see nTransaction
 */
class nChannelNotFoundException :
    public nBaseClientException {
  public:
    nChannelNotFoundException(void);
    nChannelNotFoundException(const std::string& msg);

    virtual int getType();
};

}
}
}
}
