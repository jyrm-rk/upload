/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef MEMORYMAPPEDPIPEWRITER_H
#define MEMORYMAPPEDPIPEWRITER_H

#include <string>
#include "fBase.h"
#include "MemoryMap.h"


namespace com {
namespace pcbsys {
namespace foundation {
class ByteBuffer;
namespace drivers {
namespace shm {
class MemoryMap;
class MapManager;
class DirectBufferAccess;

class MemoryMappedPipeWriter {
  private:
    static const int SPIN_TRIES = 1000;

    static const int CACHE_LINE_SIZE = 64;
    static const int TRAILER_SIZE = CACHE_LINE_SIZE * 4;

    ByteBuffer* m_mappedBuffer;
    MemoryMap* m_mappedRegion;
    DirectBufferAccess* m_directBufferAccess;

    bool m_isClosed;

    long bufferSize, mask, readerConnectedIndex, writeSequenceIndex, readSequenceIndex;

    longlong A0, A1, A2, A3, A4, A5, A6, writeSequence;
    longlong B0, B1, B2, B3, B4, B5, B6,readSequenceCache;

    void clearCompilerWarnings() {
        (void)A0;
        (void)A1;
        (void)A2;
        (void)A3;
        (void)A4;
        (void)A5;
        (void)A6;
        (void)B0;
        (void)B1;
        (void)B2;
        (void)B3;
        (void)B4;
        (void)B5;
        (void)B6;
    }

    longlong waitForReader();

  public:

    DLL ~MemoryMappedPipeWriter();

    DLL MemoryMappedPipeWriter(const std::string filename, const int bufferSize);

    DLL void waitForReaderToConnect(longlong timeout);

    DLL void close();

    DLL void write(unsigned char* buffer, const int bufLen);

    DLL void write(unsigned char* buffer, const int offset, const int length);

};
}
}
}
}
}

#endif


