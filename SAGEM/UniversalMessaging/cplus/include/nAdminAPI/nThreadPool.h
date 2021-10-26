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

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

/**
 * This class is used to represent an instance of a thread pool being used within
 * a Nirvana realm
 *
 * Each threadpool is known by a name, and has a number of values that can be accessed
 *
 * @see nThreadEntry
 * @since 4.0
 *
 */
class nThreadPool {
  public:
    /**
     * Constructs a new nThreadPool
     * @param name the name of the thread pool
     * @param size the size
     * @param idle number of idle threads
     * @param queue number of queued tasks
     * @param total number of tasks executed during lifetime
     */
    nThreadPool(const std::string& name, int size, int idle, int queue, longlong total);
    virtual ~nThreadPool(void);

  public:
    /**
     * Get the name of this thread pool
     * @return the thread pool name
     */
    virtual const std::string& getName();

    /**
     * Get the size of the pool, i.e. the number of threads allocated to the pool
     * @return the number of threads used within the pool
     */
    virtual int getSize();

    /**
     * Get the number of idle threads within the thread pool
     * @return the number of idle threads
     */
    virtual int getIdle();

    /**
     * Get the number of current tasks queued within the thread pool
     * @return the current number of queued tasks
     */
    virtual int getQueue();

    /**
     * Get the total number of tasks executed by the thread pool during it's lifetime
     * @return the total number of tasks executed
     */
    virtual longlong getTotal();

  private:
    std::string m_name;
    int m_size;
    int m_idle;
    int m_queue;
    longlong m_total;
};

}
}
}
}
