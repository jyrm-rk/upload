/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSessionPausedException.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

/**
 * The currently connected server has been paused,
 * and is not accepting publish requests.
 *  @see nSession
 */
class nPublishPausedException :
	public nSessionPausedException {
  public:
    nPublishPausedException(const std::string& msg);

    virtual int getType();

};

}
}
}
}
