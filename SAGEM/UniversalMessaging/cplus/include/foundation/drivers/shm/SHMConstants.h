/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef SHMCONSTANTS_H
#define SHMCONSTANTS_H

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace shm {
class SHMConstants {

  public:
    static const unsigned char idle   = 0;
    static const unsigned char active = 1;
    static const unsigned char confirm =2;

    static const bool sDebug = true;

    static const int sAcceptFileSize = 8192;

    static const int sCommandPos = 0;
    static const int sRandomId   = 9;
    static const int sNameLenPos = 17;
    static const int sNamePos    = 25;

    static const long sTimeOutPoll = 10000;

};

}
}
}
}
}

#endif
