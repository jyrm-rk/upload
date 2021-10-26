/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef DIRECTBUFFERACCESS_H
#define DIRECTBUFFERACCESS_H

#include "ByteBuffer.h"
#include "nBaseConstants.h"
#include "ConcurrentConstants.h"
#include "SHMConstants.h"

#ifdef WIN32
#include <intrin.h>
#endif

#ifndef WIN32
#include <unistd.h>
#endif

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace shm {
using namespace com::pcbsys::foundation;
using namespace com::pcbsys::foundation::concurrent;
using namespace com::pcbsys::nirvana::nbase;
class DirectBufferAccess {

  private:
    ByteBuffer* buffer;
    volatile bool closed;


  public:
    DirectBufferAccess(ByteBuffer* _buffer) {
        buffer = _buffer;
        closed = false;
    }

    void close() {
        closed = true;
    }

    void get(int index, unsigned char* ret, int offset, int length) {
        buffer->setRPointer(index);
        buffer->readBytes(ret+offset,length);
        //unsafe.copyMemory(null, address + index, buffer, BYTE_ARRAY_OFFSET + offset, length);
    }

    void put(int index, unsigned char* _buffer, int offset, int length) {
        buffer->setWPointer(index);
        buffer->insertBytes(_buffer+offset,length);
        //unsafe.copyMemory(buffer, BYTE_ARRAY_OFFSET + offset, null, address + index, length);
    }

    longlong getLongVolatile(int index) {
        return buffer->readLongLong(index);
        //return unsafe.getLongVolatile(null, address + index);
    }

    void putLongVolatile(int index, longlong value) {
        buffer->insertLongLong(index,value);
        //unsafe.putLongVolatile(null, address + index, value);
    }

    void putOrderedLong(int index, longlong value) {
        buffer->insertLongLong(index,value);
        //unsafe.putOrderedLong(null, address + index, value);
    }

    bool compareAndSetLong(int index, longlong expected, longlong update) {
        longlong current = buffer->readLongLong(index);
        buffer->insertLongLong(index,update);
        return current==expected;
        //return unsafe.compareAndSwapLong(null, address + index, expected, update);
    }

    longlong spinWhileEqual(int index, longlong value, longlong spinCount) {
        longlong spins = 0;
        longlong val = getLongVolatile(index);
        longlong spinIdx = ConcurrentConstants::sEnabled ? 0 : 2;
        while(val == value && !closed) {
            if(spins++ > spinCount) {
                spinIdx++;
                spins = 0;
                if(SHMConstants::sDebug) {
                    if(spinIdx == 1) {
                        fDriver::debugLog("SHM> Yielding");
                    } else if(spinIdx == 2) {
                        fDriver::debugLog("SHM> Parking");
                    }
                }
            }
            if(spinIdx == 1) {
#ifdef WIN32
                _mm_pause(); // http://software.intel.com/en-us/articles/performance-degradation-due-to-spin-wait-loops-on-hyper-threading-technology-enabled-systems/
                Sleep(0);  // Should yield to any thread requiring scheduling, else will continue to loop, just being a nice core citizen
#else
#ifndef _iphone
#ifndef __arm__       // Arm does not support this
                __asm__ __volatile__ ("pause");
#endif
                sleep(0);
#endif
#endif

            } else if(spinIdx >= 2) {
                nBaseConstants::parkNanos(ConcurrentConstants::LOCK_WAIT);
            }
            val = getLongVolatile(index);
        }
        return val;
    }
};
}
}
}
}
}

#endif
