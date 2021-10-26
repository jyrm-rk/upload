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
 * The supplied message filter string failed to be parsed. The attached message
 * contains the actual parser error.
 *
 * @see nChannel
 */
class nSelectorParserException :
    public nBaseClientException {
  public:
    nSelectorParserException(void);
    nSelectorParserException(const std::string& msg);

    virtual int getType();

};

}
}
}
}
