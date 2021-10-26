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
 * The transaction has not been committed so the status of the event can not
 * be returned, such as getStartEID or getEndEID.
 *
 * @see nTransaction
 */
class nTransactionNotCommittedException :
    public nTransactionException {
  public:
    nTransactionNotCommittedException(void);
    nTransactionNotCommittedException(const std::string& msg);
};

}
}
}
}
