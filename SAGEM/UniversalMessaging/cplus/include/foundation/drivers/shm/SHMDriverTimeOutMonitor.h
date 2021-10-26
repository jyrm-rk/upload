/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FSHMDRIVERTIMEOUTMONITOR_H
#define FSHMDRIVERTIMEOUTMONITOR_H

#include "fScheduledTask.h"
#include "fSHMDriver.h"
#include <vector>


namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace shm {

class SHMDriverTimeOutMonitor : public fScheduledTask {

  private:

    static SHMDriverTimeOutMonitor* sMyInstance;

    std::vector<fSHMDriver*> *map;
    Poco::Mutex m_lock;


    SHMDriverTimeOutMonitor();

  public:
    static SHMDriverTimeOutMonitor* getInstance();


    virtual ~SHMDriverTimeOutMonitor() {
        delete map;
    }

    void add(fSHMDriver* driver);
    void remove(fSHMDriver* driver);
    long reSchedule();
    void execute();

};
}
}
}
}
}

#endif
