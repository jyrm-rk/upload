/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Poco/Timer.h"
#include "Poco/Mutex.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fScheduledTask {
  public:
    fScheduledTask(void);
    virtual ~fScheduledTask(void);

    void setup(long time);
    virtual void execute() = 0;
    virtual long reSchedule() = 0;
    virtual void cancel();

  private:
	void CheckStatus(Poco::Timer& timer);
    Poco::Timer *m_pTimer;
	Poco::Mutex m_SyncMutex;
    long m_time;
};

}
}
}
}
