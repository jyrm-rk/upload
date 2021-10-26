/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FAESENCODER_H
#define FAESENCODER_H

#include "fBufferEncoder.h"
#include <Poco/Crypto/Cipher.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {
class fAESEncoder : public fBufferEncoder {
  private:
    //Cipher* myCipher;

    //throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException, InvalidAlgorithmParameterException
  public:
    fAESEncoder(std::vector<unsigned char>* newkey, int keySize);

    //throws NoSuchAlgorithmException, NoSuchPaddingException, InvalidKeyException
    void changeKey(std::vector<unsigned char>* newkey, int keySize);

    //throws IllegalBlockSizeException, BadPaddingException
    unsigned char* encode(long bufNo, unsigned char* buffer, int offset, int len);

    //throws IllegalBlockSizeException, BadPaddingException
    unsigned char* encode(long bufNo, unsigned char* buffer);

    virtual void changeKey(std::vector<unsigned char>* newkey)=0;
};
}
}
}
}
}
}

#endif
