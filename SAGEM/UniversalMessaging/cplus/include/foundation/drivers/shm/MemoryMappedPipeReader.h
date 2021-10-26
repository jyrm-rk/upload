/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef MEMORYMAPPEDPIPEREADER_H
#define MEMORYMAPPEDPIPEREADER_H

#include <string>
#include "MemoryMap.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
class ByteBuffer;
namespace drivers {
namespace shm {
class MapManager;
class MemoryMap;
class DirectBufferAccess;
class MemoryMappedPipeReader {
  private:
    static const int CACHE_LINE_SIZE = 64;
    static const int TRAILER_SIZE = CACHE_LINE_SIZE * 4;

    bool m_isClosed;

    ByteBuffer* m_mappedBuffer;
    DirectBufferAccess* m_directBufferAccess;
    MemoryMap* m_mappedRegion;

    int mask, bufferSize, readSequenceIndex, writeSequenceIndex;
    longlong timeoutStart;

    longlong A0, A1, A2, A3, A4, A5, A6, readSequence;
    longlong B0, B1, B2, B3, B4, B5, B6, timeOutSequence;
    longlong C0, C1, C2, C3, C4, C5, C6, C7;

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
        (void)C0;
        (void)C1;
        (void)C2;
        (void)C3;
        (void)C4;
        (void)C5;
        (void)C6;
        (void)C7;
    }

  public:
    DLL ~MemoryMappedPipeReader();

    DLL MemoryMappedPipeReader(const std::string filename, const int bufferSize, longlong timeout);

    DLL void close();

    DLL bool hasTimedOut();

    DLL int available();

    DLL int read(unsigned char* buffer, int bufLen);

    DLL int read(unsigned char* buffer, const int offset, const int length);
};
}
}
}
}
}

#endif
