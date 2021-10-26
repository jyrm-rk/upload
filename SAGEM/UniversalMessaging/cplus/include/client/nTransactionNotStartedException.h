/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nTransactionException.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

/**
 * The transaction has not been started as such the transaction is not yet established
 *
 * @see nTransaction
 */
class nTransactionNotStartedException :
    public nTransactionException {
  public:
    nTransactionNotStartedException(void);
    nTransactionNotStartedException(const std::string& msg);
};

}
}
}
}
