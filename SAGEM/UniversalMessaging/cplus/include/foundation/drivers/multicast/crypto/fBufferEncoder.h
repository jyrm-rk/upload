/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBUFFERENCODER_H
#define FBUFFERENCODER_H

#include "fCryptoHelper.h"
namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {
class fBufferEncoder : public fCryptoHelper {

  public:
    //throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException
    virtual void changeKey(std::vector<unsigned char>* newkey)=0;

    //throws IllegalBlockSizeException, BadPaddingException
    virtual unsigned char* encode(long bufNo, unsigned char* buffer, int offset, int len)=0;

    //throws IllegalBlockSizeException, BadPaddingException
    virtual unsigned char* encode(long bufNo, unsigned char* buffer)=0;

};
}
}
}
}
}
}

#endif
