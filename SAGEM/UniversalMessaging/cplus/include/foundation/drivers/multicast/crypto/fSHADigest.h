/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FSHADIGEST_H
#define FSHADIGEST_H

#include "fDigestEngine.h"
#include <Poco/DigestEngine.h>



namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {

class fSHADigest : public fDigestEngine {

  private:
  public:

    fSHADigest(unsigned char* password, unsigned int pwdLen);
    virtual ~fSHADigest();

    virtual void reset();
};
}
}
}
}
}
}

#endif
