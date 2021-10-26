/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBUFFERSTREAMHANDLER_H
#define FBUFFERSTREAMHANDLER_H

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
class fBuffer;
namespace client {
class fBufferStreamHandler {

  public:
    void virtual bufferOverRun() = 0;

    void virtual push(fBuffer* buf) = 0;

    int virtual getBufferSize() = 0;
};

}
}
}
}
}
}
#endif
