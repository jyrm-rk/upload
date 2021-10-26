/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FCRCDIGEST_H
#define FCRCDIGEST_H

#include "fDigest.h"
#include <Poco/Checksum.h>



namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {

class fCRCDigest : public fDigest {

  private:
    Poco::Checksum* myChecksum;
    const char* myPassword;
    int myPasswordLen;
    unsigned char* myCrc;

  public:

    fCRCDigest(unsigned char* password, unsigned int pwdLen);
    virtual ~fCRCDigest();

    int getLength() {
        return 8;
    }
    void update(unsigned char* data, int dataLen);
    void update(unsigned char* data, int dataLen, int offset, int len);
    void reset();
    unsigned char* digest();
};
}
}
}
}
}
}

#endif
