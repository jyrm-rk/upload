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
 * This class defines the error that can be thrown by passing an illegal argument to any
 * method of any class in the nirvana client API.
 */
class nIllegalArgumentException :
    public nBaseClientException {
  public:
    nIllegalArgumentException(std::string msg);

    virtual int getType();
};

}
}
}
}

