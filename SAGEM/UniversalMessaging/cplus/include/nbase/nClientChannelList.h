/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fPrioritized.h"
#include "fBase.h"
#include "fBaseEvent.h"
#include "fPocoThreadPool.h"
#include "nChannelQueue.h"
#include "nChannelImpl.h"
#include "Poco/AtomicCounter.h"

#include <queue>
#include <vector>

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {
class Queue;
}
}
namespace nirvana {
namespace client {
class nChannelConnectionListener;
class nEventListener;
class nConsumeEvent;
}
namespace nbase {
namespace events {
class nPurge;
class nConnectionUpdate;
class nPublished;
}

class nChannelQueue;
class nPushTask;
class nBaseChannelAttributes;
class nRegisteredEventManager;

using namespace client;
using namespace events;
using namespace foundation::collections;
using namespace com::pcbsys::foundation::fbase::collections;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::io;

class nClientChannelList : public Poco::Mutex {
  public:

    DLL nClientChannelList(nChannelQueue *pImpl);
    DLL virtual ~nClientChannelList(void);

    DLL bool hasSubscribers();
    DLL bool hasListeners();
	DLL void reconnect();
	DLL void startSubscribers();
	DLL void setAttributes(nBaseChannelAttributes *pAttr);
	DLL nChannelQueue* getBaseStore();
	DLL const std::string getName();
	DLL void addSub(nEventListener *pNel, nChannelQueue *pChannel);
	DLL void deleteSub(nEventListener *pNel);
	DLL void push(nPublished *pPublished);
    //void push(nConsumeEvent *pEvent);
	DLL void push(nPurge *pEvent);
	DLL nBaseChannelAttributes* getAttributes();
	DLL void push(nConnectionUpdate *pEvent);
	DLL bool containsListener(nChannelConnectionListener *pListener);
	DLL void addConnectionListener(nChannelConnectionListener *pListener);
	DLL void clearAsyncQueue();
	DLL void delConnectionListener(nChannelConnectionListener *pListener);
	DLL void delAllConnectionListener();
	DLL nEventListener* getSubscriber();
	DLL int getQueueSize();
	DLL void close();
	DLL void enqueue(nPushTask *task);
	DLL static void shutdown();

	static bool m_sUseThreadPool;
	bool m_bIsSubscribed;

	DLL void addRef(){ m_pBaseImpl->addRef(); }
	DLL bool delRef(){ return m_pBaseImpl->delRef(); }

  protected:
    std::vector<nChannelConnectionListener*> m_conListeners;

  private:
    void callbackListeners(nConnectionUpdate *pEvent);
    void pushPurgeCallback(nPurge *pEvent);
    void pushCallback(nConsumeEvent *pEvent, unsigned char *pSignature);

    nEventListener* volatile m_pChannelSub;
	std::queue<fBaseEvent*> m_pEventQueue;
	NotifyableCountableObject m_pEventQueueMutex;

    nChannelQueue * volatile m_pSubChannelImpl;
    nChannelQueue *m_pBaseImpl;
    nPushTask *m_pTask;
    nBaseChannelAttributes *m_pAttr;
    bool m_bIsQueue;
    std::string m_name;
    Poco::AtomicCounter currentExecutingEvents;

    class WrappedConsumeEvent : public fPrioritized, public CountableObject {
      public:
        WrappedConsumeEvent(nConsumeEvent* cEvent);
        nConsumeEvent* pConsumeEvent;
        virtual unsigned int getPriority();
        virtual int getType();
    };

    static com::pcbsys::foundation::threads::fPocoThreadPool *m_sThreadPool;

    friend class nPushTask;
	friend class com::pcbsys::nirvana::client::nChannelImpl;
};

}
}
}
}
