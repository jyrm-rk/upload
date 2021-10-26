/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nBaseClientException;

/**
 * This interface should be implemented by classes wishing to register to receive asynchronous errors from the nirvana server
 */
class nAsyncExceptionListener {
  public:
    DLL nAsyncExceptionListener(void);
    virtual DLL ~nAsyncExceptionListener(void);

    /**
    * This method is called by the nirvana API to notify a registered asynchronous exception listener that an error
    * has occurred outside the scope of the calling thread.
    *
    * @param *pEx an nBaseClientException object containing the error that has occurred
    */
    virtual DLL void handleException(nBaseClientException *pEx) = 0;
};

}
}
}
}
