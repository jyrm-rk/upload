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
 * This exception is thrown when an attempt is made by the client to make a request to the server, while the session is paused.
 *
 * the nSession object can be paused and resumed at any point by using the pause() and resume() methods of the nSession.
 *
 * @see nSession
 *
 */
class nSessionPausedException :
    public nBaseClientException {
  public:
    nSessionPausedException(std::string msg);

    virtual int getType();
};

}
}
}
}
