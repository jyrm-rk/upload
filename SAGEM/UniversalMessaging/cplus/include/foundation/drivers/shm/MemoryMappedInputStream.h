/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef MEMORYMAPPEDINPUTSTREAM_H
#define MEMORYMAPPEDINPUTSTREAM_H

#include "ByteBuffer.h"
#include "Stream.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace shm {
class fSHMDriver;
class MapManager;
class MemoryMap;
class MemoryMappedPipeReader;
using namespace com::pcbsys::foundation;
using namespace com::pcbsys::foundation::Net;
class MemoryMappedInputStream :public Stream {

  private:
    MemoryMappedPipeReader* myReader;
    unsigned char* m_buf;

  public:
    DLL MemoryMappedInputStream(std::string mapName, int size, longlong timeout);
	DLL ~MemoryMappedInputStream();

    DLL int available();

    DLL void close();

    DLL int read();

    DLL int read(unsigned char* buffer, int len);

    DLL int read(unsigned char* buffer, int offset, int len);

	DLL int readNB(unsigned char* buffer, int offset, int len);

    DLL bool hasTimedOut();

    void write (unsigned char *pBuffer, int offset, int length) {};
    void flush () {};
    int length () {
        return -999;
    }
    int position () {
        return -999;
    }
    int readByte () {
        return -999;
    }
    void setPosition (int position) {};
};
}
}
}
}
}
#endif
