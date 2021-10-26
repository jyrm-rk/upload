/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fVendorDriver.h"
#include "fMonitorable.h"
#include "fMonitorState.h"
#include "fDriverConfig.h"
#include "fAcceptHandler.h"
#include "fUsage.h"
#include "fAcceptThread.h"
#include <string>
#include "fThreadPool.h"
#include "Poco/AtomicCounter.h"
#include "Poco/Mutex.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fServerDriver : public virtual fVendorDriver, public virtual com::pcbsys::foundation::base::fMonitorable, public fbase::Countable {
  public:
    fServerDriver(configuration::fDriverConfig* config, handlers::fAcceptHandler* aHandler);
    virtual ~fServerDriver();
    //fMonitorable
    virtual void rectify();
    virtual com::pcbsys::foundation::base::fMonitorState* state();
    //fVendorDriver Interface
    virtual void remove(fDriver *vended);
	virtual void add(fDriver *vended);
    virtual fUsage* getUsage();
    virtual void close();
	bool is_Closing() { return isClosing; }
	bool is_Closed() { return isClosed; }
    virtual fDriver* performAccept()=0;
    //Temporary exposure of config
    configuration::fDriverConfig* getConfig();
    virtual bool validate(fDriver* driver)=0;


  protected:
    void start();
    void stop();
    void incrementTasks();
    void decrementTasks();

  protected:
    configuration::fDriverConfig* m_config;
    handlers::fAcceptHandler* m_acceptHandler;
    bool isActive;
    volatile bool isClosed;		// TODO:  make <atomic> in future or refactor to use Pimpl
	volatile bool isClosing;	// same
    std::string m_name;
    int m_noOfThreads;
    fUsage* m_usage;
    com::pcbsys::foundation::threads::fThreadPool* m_threadPool;
    fAcceptThread* m_acceptThread;
    
private:
	Poco::AtomicCounter m_currentTasks;
	Poco::Mutex m_activeMutex;
    std::vector<fDriver*> m_active;
    Poco::AtomicCounter m_totalConnectionCount;

    friend class fWorkerTask;
};
}
}
}
}