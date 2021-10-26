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

class nAbstractChannel;
class nChannel;

/**
 * This class is a container for the attributes necessary to create a Nirvana transaction
 */

class nTransactionAttributes {
  public:

    /**
    * Constructs an nTransactionAttributes object associated with the channel specified.
    * Transactions created with this object will have the Time To Live (TTL) specified.
    *
    * @param *pChannel The nirvana channel associated with the transaction
    * @param timeToLive The Time To Live (TTL) value that the transaction will have
    *
    * @exception nTransactionException If there is an error during the construction, check the message for more information
    */
    DLL nTransactionAttributes(nAbstractChannel *pChannel, longlong timeToLive = -2);

    /**
    * Default Constructor
    */

    DLL nTransactionAttributes();

    DLL virtual ~nTransactionAttributes(void);

    /**
    * Gets the nirvana channel that will be associated with transactions created from this object
    *
    * @return the nChannel object that will be associated with the transactions created from this object
    */
    DLL nAbstractChannel* getChannel();

    /**
    * Gets the TTL value that transactions created from this object will have
    *
    * @return a long value specifying the TTL value that transactions created from this object will have
    */
    DLL longlong getTTL();

    /**
    * Sets the TTL value that transactions created from this object will have
    *
    * @param timeToLive a long value specifying the TTL value that transactions created from this object will have
    */
    DLL void setTTL(longlong timeToLive);

    /**
    * Sets the nirvana channel that will be associated with transactions created from this object
    *
    * @param *pChannel the nChannel object that will be associated with the transactions created from this object
    */

    DLL void setChannel(nChannel *pChannel);

  private:
    nAbstractChannel *m_pChannel;
    longlong m_TTL;
};

}
}
}
}
