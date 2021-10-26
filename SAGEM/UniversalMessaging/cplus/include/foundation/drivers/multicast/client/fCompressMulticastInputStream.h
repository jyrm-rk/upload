/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FCOMPRESSMULTICASTINPUTSTREAM_H
#define FCOMPRESSMULTICASTINPUTSTREAM_H

#include <fMulticastInputStream.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fByteArrayInputStream;
}
namespace drivers {
class fAsyncReadListener;
namespace multicast {
class fBuffer;
namespace crypto {
class fBufferDecoder;
}
namespace client {
class fMulticastReceiverManager;
using namespace com::pcbsys::foundation::drivers::multicast::client;

class fCompressMulticastInputStream : fMulticastInputStream {

  private:
    com::pcbsys::foundation::io::fByteArrayInputStream* bais;
    unsigned char* myTempBuffer;
    int myTempBufferLen;

    //throws IOException
    fCompressMulticastInputStream(fMulticastReceiverManager* manager, com::pcbsys::foundation::drivers::multicast::crypto::fBufferDecoder* decoder, com::pcbsys::foundation::drivers::fAsyncReadListener* myListener);

    void handleCompleteMessage(fBuffer* buffer);
};
}
}
}
}
}
}

#endif
