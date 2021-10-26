/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FAESDECODER_H
#define FAESDECODER_H

#include "fBufferDecoder.h"
#include <Poco/Crypto/Cipher.h>
#include <Poco/Crypto/CryptoTransform.h>
#include <Poco/Crypto/CipherFactory.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {

class fAESDecoder : public fBufferDecoder {
  private:
    int myCypherType;
    Poco::Crypto::CipherFactory* myFactory;
    Poco::Crypto::CipherKey* myKey;
    Poco::Crypto::Cipher*    myCipher;
    unsigned char* myWorkingBuffer;

    //throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, InvalidAlgorithmParameterException
  public:
    fAESDecoder(unsigned char* newkey, int keyLen, unsigned char* cookie, int cookieLen, int cipherType);

    virtual ~fAESDecoder();

    //throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException
    void changeKey(unsigned char* newkey, int keyLen, unsigned char* cookie, int cookieLen);

    //throws IllegalBlockSizeException, BadPaddingException
    int decode(longlong bufNo, unsigned char** buffer, int len);

};
}
}
}
}
}
}
#endif
