/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FDIGESTENGINE_H
#define FDIGESTENGINE_H

#include "fDigest.h"
#include <Poco/DigestEngine.h>



namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {

class fDigestEngine : public fDigest {

  protected:
    const unsigned char* myPassword;
    unsigned char* myDigest;

    Poco::DigestEngine* myDigestEngine;
    int myPasswordLen;

  public:

    fDigestEngine(unsigned char* password, unsigned int pwdLen);
    virtual ~fDigestEngine();

    int getLength();
    void update(unsigned char* data, int dataLen);
    void update(unsigned char* data, int dataLen, int offset, int len);
    unsigned char* digest();
    void reset() {}
};
}
}
}
}
}
}

#endif
