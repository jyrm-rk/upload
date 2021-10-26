/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fConnectionFlushWriteHandler.h"
#include "fBaseEvent.h"
#include "Poco/Thread.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {

class fConnection;

class fConnectionPeakWriteHandler :
    public fConnectionFlushWriteHandler {
  public:
    fConnectionPeakWriteHandler(fConnection *pConnection);
    virtual ~fConnectionPeakWriteHandler(void);

    virtual void processObject(CountableObject *pObject, long queueSize, bool allowClose);
    virtual bool directWriteEnabled();

    long m_writeCount;
    long m_lastCheck;
    long m_peakEnd;

    static long s_peakWriteTrailDelay;
    static long s_peakDetectSize;
    static long s_peakCountSize;
    static long s_maxNoEventsBeforeFlush;

    void run();

  protected:
    static long s_peakDetectSizeMs;

  private:
    bool isInPeak(fBaseEvent *pEvt);

    static long s_totalWrites;
    bool m_bInPeak;
};

}
}
}
}
