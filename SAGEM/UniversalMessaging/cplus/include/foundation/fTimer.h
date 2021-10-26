/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <list>

#include "fBase.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {


class fInternalTimer;
class fMinuteListener;

class fTimer {
  public:
    fTimer(void);
    virtual ~fTimer(void);

    static longlong getTicks();
    static longlong currentTimeMillis();
    static void shutdown();

  private:
    static fTimer *m_pTimer;
    static fInternalTimer *m_pActualTimer;
    static bool m_bIsRunning;
    static longlong m_tickSize;
    static std::list<fMinuteListener*> m_minuteListeners;
    static void initTimer();

    longlong m_adjustment;
    longlong m_lastMilliseconds;
    longlong m_lastCheck;

    friend class fInternalTimer;
};

class fInternalTimer : Poco::Runnable {
  public:
    fInternalTimer(fTimer* parent);
    virtual ~fInternalTimer(void);

    virtual void run ();
    void shutdown();
    longlong getTickCount();

    longlong m_ticks;
    static fInternalTimer *m_pInternalTimer;
    Poco::Thread *m_pThread;

  private:
    bool m_runFlag;
};

}
}
}
}
