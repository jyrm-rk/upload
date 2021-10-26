/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEvent.h"
#include "nEventFactory.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nRequestCallback;

namespace events {

using namespace foundation::io;

class nServerExtensionEvent :
    public nEvent {
  public:
    nServerExtensionEvent():nEvent(nEventFactory::SERVER_EXTENSION), uniqueId(0), data(NULL), data_len(0) {
    }
    nServerExtensionEvent(longlong id, unsigned char* dt, int len, fEventDictionary* props): nEvent(nEventFactory::SERVER_EXTENSION), uniqueId(id), data(dt), data_len(len) {
        m_pDictionary = props;
    }

    virtual ~nServerExtensionEvent(void) {}


    virtual int getType () {
        return fBase::SERVEREXTENSION;
    }
    const std::string getTypeString() {
        return "nStreamStatusUpdate";
    }

    virtual nEvent* createInstance() {
        return new nServerExtensionEvent();
    }

    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    longlong getUniqueId() {
        return uniqueId;
    }
    void setUniqueId(longlong id) {
        uniqueId = id;
    }

    unsigned char* getData() {
        return data;
    }
    int getDataLength() {
        return data_len;
    }
    void setData(unsigned char* dt, int len) {
        data = dt;
        data_len=len;
    }

    fEventDictionary* getDictionary() {
        return m_pDictionary;
    }
    void setDictionary (fEventDictionary *dic) {
        m_pDictionary = dic;
    }

  private:
    longlong uniqueId;
    unsigned char* data;
    unsigned int data_len;
};

}
}
}
}
}

