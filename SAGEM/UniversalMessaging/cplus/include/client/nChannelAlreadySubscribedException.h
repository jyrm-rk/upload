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
 * The user has tried to subscribe to the channel more than once. To rectify this problem
 * the user must remove the current subscription by calling nChannel.removeSubscriber
 *
 * @see nChannel
 */
class nChannelAlreadySubscribedException :
    public nBaseClientException {
  public:
    nChannelAlreadySubscribedException(void);
    nChannelAlreadySubscribedException(const std::string& msg);

    virtual int getType();
};

}
}
}
}
