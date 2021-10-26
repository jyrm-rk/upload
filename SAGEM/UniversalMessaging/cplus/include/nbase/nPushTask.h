/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fTask.h"
#include "Poco/Runnable.h"
#include "fBaseEvent.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

class nClientChannelList;

using namespace foundation::fbase;

class nPushTask : public Poco::Runnable, public Poco::Mutex {
  
public:
	DLL nPushTask(nClientChannelList *pChannel);
	DLL virtual ~nPushTask(void);
	DLL bool isRunning() { return m_bIsRunning; }
	DLL void setRunning(bool value) { m_bIsRunning = value; }

	DLL void close();
	DLL void run();

private:
    volatile bool m_bIsClosed;
    volatile bool m_bIsRunning;
	Poco::Mutex m_taskLock;
    nClientChannelList *m_pChannel;

private:    
    void handleEvent(fBaseEvent *evt);
	void doRun();
};

}
}
}
}
