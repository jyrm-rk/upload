/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FPOCOTHREADPOOL_H
#define	FPOCOTHREADPOOL_H

#include "Poco/ThreadPool.h"
#include "Poco/Runnable.h"
#include "Poco/Mutex.h"

// NOTE PLEASE DO NOT USE THIS, USE THE NEW fThreadPool class since it grows and is what we need

namespace com {
namespace pcbsys {
namespace foundation {
namespace threads {
class fPocoThreadPool {
public:
    fPocoThreadPool(const std::string& name, int minCapacity = 2, int maxCapacity = 16, int idleTime = 30);
    virtual ~fPocoThreadPool();

    void start(Poco::Runnable& target);

    void stopAll();
    
private:
    Poco::ThreadPool *pThreadPool;
    Poco::Mutex mutex;
    bool stopped;
};
}
}
}
}

#endif	/* FPOCOTHREADPOOL_H */

