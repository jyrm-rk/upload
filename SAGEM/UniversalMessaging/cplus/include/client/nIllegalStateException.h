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
 * This exception is thrown if a Channel or Queue is in an illegal state for specific
 * functionality to be offered. For example if a queue has a listener set and you attempt
 * to set another listener, it will throw an instance of nIllegalStateException.
 *  @see nQueue
 */
class nIllegalStateException :
    public nBaseClientException {
  public:
    nIllegalStateException(void);
    nIllegalStateException(const std::string& message);
};

}
}
}
}
