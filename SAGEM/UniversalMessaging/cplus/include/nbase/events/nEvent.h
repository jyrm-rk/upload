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
#include "fBaseEvent.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fEventDictionary;
}
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nbase {
class nRequestCallback;

namespace events {

using namespace foundation::io;

class nEvent :
    public fBaseEvent {
  public:
    nEvent();
    nEvent(int id);
    virtual ~nEvent(void);

    virtual bool isSynchronous();
    nRequestCallback* getCallback();
    bool isMarked();
    void setMarked ();
    void setCallback(nRequestCallback *pCallback);
    virtual void readExternal(fEventInputStream *pIstream);
    virtual void writeExternal(fEventOutputStream *pOstream);
    virtual void performRead(fEventInputStream *pIstream) = 0;
    virtual void performWrite(fEventOutputStream *pOstream) = 0;
    virtual nEvent* createInstance() = 0;
    int getId();
    void setId(int id);
    virtual bool isTypeSynchronous();
    void releaseCache();
    virtual unsigned int getPriority();

  protected:
    fEventDictionary* m_pDictionary;
    int m_id;

  private:
    nRequestCallback *m_pCallback;
    bool m_bMarked;
    unsigned char *m_pCache;
    int m_cacheLen;
    int m_cacheCount;

    static int m_sTraceCount;
    static int m_sEventCount;
};

}
}
}
}
}

