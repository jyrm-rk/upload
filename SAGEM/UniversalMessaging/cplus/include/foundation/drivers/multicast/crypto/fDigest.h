/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FDIGEST_H
#define FDIGEST_H

#include <string>
#include <stdio.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {
using namespace com::pcbsys::foundation::drivers::multicast::crypto;
using namespace com::pcbsys::foundation::drivers::multicast;

class fDigest {

  public:

    virtual int getLength() = 0;
    virtual void update( unsigned char* data, int dataLen )=0;
    virtual void update( unsigned char* data, int dataLen , int offset, int len)=0;
    virtual void reset()=0;
    virtual unsigned char* digest()=0;//normally would return length as param but there is a getLength function

    //throws IOException
    bool test(unsigned char* crc, int crcLen);

    std::string byteArrayToString(unsigned char* data, int len);
};
}
}
}
}
}
}

#endif
