/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>
#include <vector>
#include "fThreadPoolExecutor.h"
#include "Queue.h"
#include "fTaskThreadPool.h"
#include "Poco/Mutex.h"
#include "Poco/AtomicCounter.h"
#include "WorkerThread.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace threads {

class fThreadPool : fThreadPoolExecutor, public fbase::Countable {
  public:
    fThreadPool(std::string poolName, int noOfThreads, int priority, int maxThreads);
    virtual ~fThreadPool();

    void close();    
	void addTask(fTaskThreadPool* aTask, bool alreadyHaveRef=false);
    void execute();
    int getTaskQueue();
    unsigned int getMaxThreadCount();

  private:
    bool canRun;
    bool canGrow;
    unsigned int m_minThreads;
    unsigned int m_maxThreads;
    unsigned int m_noOfThreads;
    unsigned int m_threadCount;
    Poco::AtomicCounter m_idleThreadCount;
    std::string m_name;
    unsigned int m_priority;
    std::vector<WorkerThread*> m_threads;
    com::pcbsys::foundation::collections::Queue* m_taskQueue;
    Poco::Mutex m_ThreadsMutex;

    friend class WorkerThread;
};

}
}
}
}
