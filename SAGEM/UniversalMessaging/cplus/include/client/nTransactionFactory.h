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

class nTransaction;
class nTransactionAttributes;

/**
 * This class is used with a nTransactionAttributes object to create a Nirvana transaction.
 */
class nTransactionFactory {
  public:

    virtual ~nTransactionFactory(void);

    /**
    * Creates an nTransaction object (Nirvana transaction) based on the nTransactionAttributes object supplied
    *
    * @param *pAttr The nTransactionAttributes object containing the parameters for the transaction to be created
    * @return the newly created nTransaction object
    */
    static DLL nTransaction* create(nTransactionAttributes *pAttr);

    /**
    * Creates an nTransaction object (Nirvana transaction) based on the nTransactionAttributes object supplied
    *
    * @param *pAttr The nTransactionAttributes object containing the parameters for the transaction to be created
    * @param oldTXId can be used when reconstructing a transaction object from a previously known ID. If value less than 0 is supplied a new TXId will be allocated.
    *
    * @return the newly created nTransaction object
    */

    static DLL nTransaction* create(nTransactionAttributes *pAttr, longlong oldTXId);

    /**
    * Gets the size of the publish transaction buffer
    *
    * @return An int specifying the size of the publish transaction buffer
    */

    static DLL int getPublishBufferSize();

    /**
    * Sets the size of the publish transaction buffer
    *
    * @param size An int specifying the size of the publish transaction buffer
    */

    static DLL void setPublishBufferSize(int size);

  private:
    /**
    * Default constructor for serialisation support. Use the static methods to
    * create nTransaction objects.
    */
    nTransactionFactory(void);
    static int sPubBuffer;
};

}
}
}
}
