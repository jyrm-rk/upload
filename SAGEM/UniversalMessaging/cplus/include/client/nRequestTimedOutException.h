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
 *
 * When the maximum time the client API will wait for a response to a specific
 * request from the Nirvana realm is reached, this exception is thrown. The default value
 * is 60 secs and typically if you get this exception the cause would be:
 *
 * <p>
 * 1. There is a protocol mismatch between the client library in use and server
 * you are connected to.
 * </p>
 * <p>
 * 2. The realm is really so busy that has not managed to respond to your request
 * within the specified maximum interval.
 * </p>
 *
 * @see nSession
 * @see nChannel
 * @see nTransaction
 */
class nRequestTimedOutException :
    public nBaseClientException {
  public:
    nRequestTimedOutException(std::string msg);

    virtual int getType();
};

}
}
}
}
