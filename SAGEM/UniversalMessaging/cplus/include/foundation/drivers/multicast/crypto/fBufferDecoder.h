/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBUFFERDECODER_H
#define FBUFFERDECODER_H

#include "fBase.h"
#include "fCryptoHelper.h"
namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {
class fBufferDecoder : public fCryptoHelper {

    // throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException
  public:
    virtual void changeKey(unsigned char* newkey, int keyLen, unsigned char* cookie, int cookieLen) = 0;

    // throws IllegalBlockSizeException, BadPaddingException
    virtual int decode(longlong bufNo, unsigned char** buffer, int len) = 0;

};
}
}
}
}
}
}

#endif
