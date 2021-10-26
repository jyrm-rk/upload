/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef CHANGEKEYINFO_H
#define CHANGEKEYINFO_H

#include "fBase.h"
namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
class changeKeyInfo {
  private:
    longlong myChangekeyAt;
    unsigned char* myKey;
    unsigned char* myCookie;
    int myKeyLen;
    int myCookieLen;

  public:
    changeKeyInfo(longlong changeKeyAt, unsigned char* key, int keyLen, unsigned char* cookie, int cookieLen);

    longlong getChangekeyAt();

    unsigned char* getCookie();
    unsigned char* getKey();
    int getCookieLen();
    int getKeyLen();
};
}
}
}
}
}
#endif


