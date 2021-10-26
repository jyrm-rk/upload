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

class DLL nMessageValidator {
  public:
    nMessageValidator(void);
    virtual ~nMessageValidator(void);

    /**
     * This method adds the byte[] to the signature being built up to validate against
     *
     * @param *pData byte[] to add to the signature
     * @exception Exception Specific to the actual signing implementation
     */

    virtual void update(unsigned char *pData) = 0;

    /**
     * Compares the signature passed as a byte[] with the signature constructed with
     * the update methods. This method must throw an exception if the signatures do not
     * match and must not just return null. As a null is still a valid return object.
     *
     * @param *pOriginal Signature byte[]
     * @return Object specific to the validating class that can be used for further validation
     * @exception Exception Must be thrown if the signature do not match
     */

    virtual void* check(unsigned char *pOriginal) = 0;

    /**
     * This method is called on the validating class prior to any calls being made. It is not
     * mandatory that the implementing class do anything with the function.
     *
     * @param *pSignature The signature to be validated
     */

    virtual void start(unsigned char *pSignature) = 0;

    /**
     * This method is called when the validation is completed.
     */

    virtual void stop() = 0;
};

}
}
}
}
