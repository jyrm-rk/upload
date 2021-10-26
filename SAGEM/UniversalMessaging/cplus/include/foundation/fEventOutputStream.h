/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"

#include <string>

#include "Poco/SynchronizedObject.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace Net {

class Stream;

}

namespace io {

using namespace Net;

class fBaseEventFactory;
class fBaseEvent;

class fEventOutputStream : public Poco::SynchronizedObject {
  public:
    fEventOutputStream(Stream *pStream);
    fEventOutputStream(Stream *pOStream, bool compressBinary);
    fEventOutputStream(Stream *pOStream, fBaseEventFactory *pFactory, bool compressBinary);

    virtual ~fEventOutputStream(void);

    void writeShort(short x);
    void writeDouble(double aFloat);
    void writeFloat(float aFloat);
    void write(int x);
    void writeEvent(fBaseEvent *pEvent);
    void writeByte(unsigned char aByte);
    void writeInt(int x);
    void writeBoolean(bool aBool);
    void writeByteArray(unsigned char *pBuffer, int length);
    void write(unsigned char *pBuffer, int length);
    void flush();
    void writeString(const std::string& aString);
    void writeLong(longlong x);
    fBaseEventFactory* getFactory();

    longlong getByteCount();

    static bool m_sBufferingOutput;

    void close();

  private:
    void writeBinary(longlong val);
    void writeNative(longlong val, int size);
    void clearBuffer();

    bool m_bCanCompressBinary;
    unsigned char *m_pTempBuf;
    int m_bufPos;
    int m_bufSize;
    longlong m_byteCount;
    fBaseEventFactory *m_pFactory;

    Stream *m_pOstream;

    const static int m_defaultBufferSize = 10240;
};

}
}
}
}

