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
#include "Poco/SynchronizedObject.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace Net {

class DLL Stream : public Poco::SynchronizedObject {
  public:
    virtual ~Stream(void);

    virtual void write (unsigned char *pBuffer, int offset, int length) = 0;
    virtual int read (unsigned char *pBuffer, int offset, int length) = 0;
	virtual int readNB(unsigned char *pBuffer, int offset, int length) = 0;
    virtual int read (unsigned char *pBuffer, int length) = 0;
    virtual void flush () = 0;
    virtual int length () = 0;
    virtual int position () = 0;
    virtual int readByte () = 0;
    virtual void setPosition (int position) = 0;
    virtual void close () = 0;

  protected:
    Stream();

};

}
}
}
}

