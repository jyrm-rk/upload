/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FBYTEARRAYQUEUEINPUTSTREAM_H
#define FBYTEARRAYQUEUEINPUTSTREAM_H

#include <Stream.h>
#include <iostream>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
using namespace com::pcbsys::foundation::Net;
class fByteArrayQueueInputStream : public Stream {

  private:

    class BufferHolder {
      public:
        unsigned char* buffer;
        int bufferLen;

        BufferHolder(unsigned char* _buffer, int _bufferLen) {
            buffer=_buffer;
            bufferLen=_bufferLen;
        }
    };

    std::list<BufferHolder*>* myInputQueue;
    unsigned char* myWorkingBuffer;
    int myWorkingBufferLen;
    int pos;
    bool _isClosed;

    // throws IOException
    void setupBuffer(bool block);

  public:
    fByteArrayQueueInputStream();

    int getQueueSize();

    // throws IOException
    void close();

    // throws IOException
    int read();

    //throws IOException
    int read(unsigned char* buf, int bufLen);

    //throws IOException
    int read(unsigned char* buf, int off, int length);
	int readNB(unsigned char* buf, int off, int length);

    bool markSupported();
    void mark(int readAheadLimit);
    void reset();

    //throws IOException
    long skip(long n);

    //throws IOException
    int available();

    void push(unsigned char* buffer,int bufferLen);

    bool isClosed();

    virtual void flush ();
    virtual int length ();
    virtual int position ();
    virtual int readByte ();
    virtual void setPosition (int position);

    virtual void write (unsigned char *pBuffer, int offset, int length);
    //virtual int read (unsigned char *pBuffer, int offset, int length);



};
}
}
}
}
#endif
