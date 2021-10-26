/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Queue.h"
#include "fDriverMonitorEntry.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fServerDriver;
class fAcceptThread : public Poco::Runnable {
  public:
    fAcceptThread(fServerDriver* driver);
    virtual ~fAcceptThread(void);
    void run();
    fDriverMonitorEntry* getNext();
    void close();
    void begin();

  private:
    Poco::Thread m_thread;
    com::pcbsys::foundation::collections::Queue* const m_acceptQueue;
    fServerDriver* const m_server;
    volatile bool isRunning;	// TODO:  make <atomic> in future or refactor to use Pimpl
	void waitFor(int millis = -1);


};

}
}
}
}
