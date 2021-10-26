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
#include "Stream.h"
#include "nTimeOutUpdate.h"
#include "fDefaultLoginContext.h"
#include "fSSLLoginContext.h"
#include "nMulticastReceiver.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {

using namespace Net;

class fBaseEventFactory;
class fBaseEvent;

class fEventInputStream : public Poco::SynchronizedObject {
  public:
    fEventInputStream(Stream *pIstream);
    fEventInputStream(Stream *pIstream, fBaseEventFactory *pFactory, int bufferSize=10000, bool compressBinary=false);
    fEventInputStream(Stream *pIstream, int bufferSize, bool compressBinary);

    virtual ~fEventInputStream(void);

    void close();

    bool readBoolean();
    unsigned char readByte();
    int readInt();
    longlong readNative(int size);
    std::string readString();
    unsigned char* readByteArray(unsigned int& size);
    longlong readLong();
    int read();
    short readShort();
    double readDouble();
    float readFloat();
    int read(unsigned char *buffer, int length);

    fBaseEvent* readEvent();

    long available();

    Stream* getInputStream();

    longlong getByteCount();

    void setMaxBufferSize(int size);
    bool isCanCompressBinary();
    void setCanCompressBinary(bool canCompressBinary);

  protected:
    void readComplete(unsigned char *pBuffer, int size);

  private:

    ulonglong readBinary();

    Stream *m_pIstream;
    bool m_bCanCompressBinary;

    unsigned char* m_tmpBinary;
    unsigned char* m_tempBuf;
    long m_maxBufferSize;
    int m_rollbackByte;
    int m_tempBufIdx;
    int m_tempBufEnd;
    longlong m_byteCount;
    fBaseEventFactory *m_pFactory;

    friend class fConnection;
    friend class fConnectionFactory;
    friend class fDefaultConnectionFactory;
    friend class security::fDefaultLoginContext;
    friend class security::fSSLLoginContext;
};

}
}
}
}

