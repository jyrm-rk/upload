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
 * This exception is thrown if a user tries calls queue specific functionality on a channel object
 * or channel specific functionality on a queue object.
 *  @see nSession
 */
class nIllegalChannelModeException :
    public nBaseClientException {
  public:
    nIllegalChannelModeException(void);
    nIllegalChannelModeException(const std::string& message);

    virtual int getType();
};

}
}
}
}
