/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FNULLDIGEST_H
#define FNULLDIGEST_H

#include "fDigest.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {
class fNullDigest : public fDigest {

  public:

    fNullDigest(unsigned char* password, int pwdLen) {}
    virtual ~fNullDigest() {}

    int getLength() {
        return 0;
    }

    void update(unsigned char* data, int dataLen) {}

    void update(unsigned char* data, int dataLen, int offset, int len) {}

    void reset() {}

    unsigned char* digest() {
        return NULL;
    }

};
}
}
}
}
}
}

#endif

