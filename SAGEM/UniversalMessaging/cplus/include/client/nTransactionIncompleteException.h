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
 * This exception will be thrown if abort or commit is called on a transaction that has not sent any events to the server.
 * For example, create a transaction, and call commit, without publishing any events to the transaction
 *
 * @see nTransaction
 */

class nTransactionIncompleteException :
    public nTransactionException {
  public:
    nTransactionIncompleteException(void);
    nTransactionIncompleteException(const std::string& msg);
};

}
}
}
}
