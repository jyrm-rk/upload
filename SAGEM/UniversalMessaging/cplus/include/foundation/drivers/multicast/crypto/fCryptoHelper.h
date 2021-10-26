/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FCRYPTOHELPER_H
#define FCRYPTOHELPER_H

#include <Poco/Random.h>
#include <Poco/Crypto/CipherKey.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace crypto {
class fBufferDecoder;
class fDigest;


class fCryptoHelper {
  protected:

  public:

    virtual ~fCryptoHelper() {}


    // throws InvalidKeyException, NoSuchAlgorithmException, NoSuchPaddingException, InvalidAlgorithmParameterException
    static fBufferDecoder* getDecoder(int type, unsigned char* key, int keyLen, unsigned char* cookie, int cookieLen);

    //throws NoSuchAlgorithmException
    static fDigest* getDigest(std::string name, unsigned char* passphrase, int passphraseLen);
};
}
}
}
}
}
}

#endif
