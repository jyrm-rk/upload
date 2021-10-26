/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Stream.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace Net {

class MemoryStream :
    public Stream {
  public:
    MemoryStream(int initialSize = INCREMENT);
    MemoryStream(unsigned char *pBuffer, int length);
    virtual ~MemoryStream(void);

    virtual void write (unsigned char *pBuffer, int offset, int length);
    virtual int read (unsigned char *pBuffer, int offset, int length);
	virtual int readNB(unsigned char *pBuffer, int offset, int length);
    virtual int read (unsigned char *pBuffer, int length);
    virtual void flush ();
    virtual int length ();
    virtual int position ();
    virtual int readByte ();
    virtual void setPosition (int position);
    virtual void close ();

    unsigned char* toArray (int& length);
    void setLength (int length);

  private:
    unsigned char *m_pBuffer;
    int m_length;
    int m_position;
    int m_capacity;

    static const int INCREMENT = 1024;
};

}
}
}
}
