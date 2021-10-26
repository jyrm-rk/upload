/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <string>
#include "ByteBuffer.h"
#include "Poco/SharedMemory.h"
/*
Please not we do not use force() as this will actually flush the memory to disk, which is not what
we are trying to achieve with this implementation.

We do call load() to see if we can get the entire buffer into RAM for faster access once we are up

 */

using Poco::SharedMemory;

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace shm {

class MemoryMap {
  private:
    SharedMemory* myMap;
    bool isClosed;

  public:
    MemoryMap(std::string mapName, int bufferSize);
	~MemoryMap();

    size_t getMapSize();

    void close();

    void flush();

    com::pcbsys::foundation::ByteBuffer* getMap();
};
}
}
}
}
}

#endif
