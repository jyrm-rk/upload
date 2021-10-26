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
 * This class defines the errors that can be thrown by using the nirvana transactional publish API
 */
class nTransactionException :
    public nBaseClientException {
  public:

    /**
    * Constructs a new nTransactionException with the specified message
    *
    * @param msg a string message to specify the nature of the transaction error
    */
    nTransactionException(const std::string& msg);

    /**
    * Constructs a new nTransactionException with the specified message and transaction TTL value.
    *
    * @param msg a string message to specify the nature of the transaction error
    * @param ttl a long specifying the transaction Time To Live (TTL) value as defined by the server
    */
    nTransactionException(const std::string& msg, longlong ttl);

    /**
    * Gets the transaction TTL value as defined by the server
    *
    * @return a longlong value specifying the transaction TTL value as defined by the server
    */

    longlong getServerTTL();

  private:
    longlong m_serverTTL;
};

}
}
}
}
