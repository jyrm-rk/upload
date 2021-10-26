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
 * The supplied transaction ID could not be located on server. This could be that
 * the transaction has expired.
 *
 * @see nTransaction
 */
class nTransactionNoSuchTXIDException :
    public nTransactionException {
  public:
    nTransactionNoSuchTXIDException(void);
    nTransactionNoSuchTXIDException(const std::string& msg);

    virtual int getType();
};

}
}
}
}
