/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <iostream>
#include "fBase.h"
#include "Poco/Exception.h"
#include <string.h>

using namespace std;
using namespace com::pcbsys::foundation;

namespace com {
namespace pcbsys {
namespace foundation {
class ByteBuffer {

  private:
    unsigned char* myBuffer;
    unsigned int myBufferSize;
    unsigned int r_pointer;
    unsigned int w_pointer;

    template <typename TYPE> TYPE readNext() {
        mem_barrier();
        TYPE bytes = readAt<TYPE>(r_pointer);
        r_pointer += sizeof(TYPE);
        return bytes;
    }

    template <typename TYPE> TYPE readAt(unsigned int idx) const {
        mem_barrier();
        return *((TYPE*)&myBuffer[idx]);
    }

    template <typename TYPE> void app(TYPE bytes) {
        mem_barrier();
        unsigned int s = sizeof(bytes);
        *((TYPE*)&myBuffer[w_pointer]) = bytes;
        w_pointer += s;
    }

    template <typename TYPE> void ins(TYPE bytes, unsigned int idx) {
        mem_barrier();
        *((TYPE*)&myBuffer[idx]) = bytes;
        w_pointer = idx+sizeof(bytes);
    }

  public:
    ByteBuffer();
    ByteBuffer(unsigned int buffersize);
    ByteBuffer(unsigned char* arr, unsigned int arr_size);
    ~ByteBuffer() {};

    unsigned char read();
    unsigned char read(unsigned int idx);
    void readBytes(unsigned char* _buffer, unsigned int len);
    longlong readLongLong();
    longlong readLongLong(unsigned int idx);
    int readInt();
    int readInt(unsigned int idx);


    void insert(unsigned char byte);
    void insert(unsigned int idx, unsigned char byte);
    void insertBytes(unsigned char* bytes, unsigned int length);
    void insertLongLong(longlong val);
    void insertLongLong(unsigned int idx, longlong val);

    void setRPointer(unsigned int rp);

    int getRPointer();

    void setWPointer(unsigned int wp);

    int getWPointer();

};
}
}
}

#endif
