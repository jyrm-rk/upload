/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBUFFERSYNCHRONISATION_H
#define FBUFFERSYNCHRONISATION_H

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace multicast {
namespace client {
class fBufferSynchronisation {
  public:
    virtual void buffersInSync()=0;

    virtual void buffersOutOfSync()=0;

    virtual void reset()=0;
};
}
}
}
}
}
}

#endif
