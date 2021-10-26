/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef MEMORYMAPPEDOUTPUTSTREAM_H
#define MEMORYMAPPEDOUTPUTSTREAM_H

#include <string>
#include "Stream.h"

namespace com {
namespace pcbsys {
namespace foundation {
class ByteBuffer;
namespace drivers {
namespace shm {
class fSHMDriver;
class MemoryMappedPipeWriter;
class MapManager;
using namespace com::pcbsys::foundation::Net;

class MemoryMappedOutputStream : public Stream {
  private:
    MemoryMappedPipeWriter* myMemoryMap;
    bool isClosed;

    void sendData();
  public:
    DLL MemoryMappedOutputStream(std::string mapName, int size);
	DLL ~MemoryMappedOutputStream();

    DLL void close();

    DLL void write(int i);

    DLL void write(unsigned char* buffer, int len);

    DLL void write(unsigned char* buffer, int offset, int len);

    DLL void flush();

    DLL void waitForReader(longlong timeout);

    virtual int read(unsigned char *pBuffer, int length) {
        return -999;
    }

    int read(unsigned char *pBuffer, int offset, int length) {
        return -999;
    };

	int readNB(unsigned char *pBuffer, int offset, int length) {
		return -999;
	};

    int length() {
        return -999;
    };

    int position() {
        return -999;
    }
    int readByte() {
        return -999;
    }

    void setPosition(int position) {
    }
};
}
}
}
}
}

#endif
