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
#include "fBaseConnection.h"
#include "fQueueHandler.h"
#include "Poco/Mutex.h"

#include <string>
#include <vector>

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {
class fQueue;
}
namespace drivers {
class fDriver;
class fDriverFactory;
class fConnectionDetails;
}
namespace security {
class fSubject;
}
namespace fbase {
class fProcessQueue;
}

using namespace com::pcbsys::foundation::collections;
using namespace fbase;
using namespace drivers;
using namespace security;

namespace io {

class fEventOutputStream;
class fEventInputStream;
class fBaseEventFactory;
class fConnectionFactory;
class fConnectionKeepAlive;
class fCloseListener;
class fConnectionHandler;
class fConnectionQueueListener;
class fBaseEvent;
class fReconnectionHandler;
class fConnectionWriteHandler;
class fOutOfBandEventHandler;

class fConnection :
    public fBaseConnection, public fQueueHandler {
  public:
    static long getKeepAlive();
    static void setKeepAlive(long time);


	static DLL fConnection* createConnection(fDriverFactory *pDriverFactory, fBaseEventFactory *pEventFactory, int bufSize, bool enableCompression, int version, long initialKeepAliveInterval = 0);
    virtual DLL ~fConnection(void);

    DLL std::string getID();
    DLL fDriver* getDriver ();
    DLL void close();
    void close(bool wait);
    DLL void addConnectionQueueListener(fConnectionQueueListener *pListener);
    DLL void setBufferSize(int size);
    DLL bool isAlive();
    DLL bool write(fBaseEvent *pEvent);
    DLL bool write(fBaseEvent *pEvent, bool block);
    DLL void setCurrentResponseTime(int currentResponseTime);
    DLL fConnectionDetails* getConnectionDetails();
    DLL fBaseEvent* read();


    virtual void processObject(CountableObject *pObject, long queueSize, bool allowClose);
    virtual void readExternal(fEventInputStream *pIstream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);

    void actualWrite(fBaseEvent *pEvent);
    fSubject* getSubject();
    std::string getLocalID();

    virtual void reachedLWM();
    virtual void reachedHWM();
    void removeConnectionQueueListener();

    void setInWrite(bool bInWrite);
    bool getInWrite();

    void setCurrentKeepAliveTime(long time);

    bool write(fBaseEvent *pEvent, bool block, bool notifyImmediatly);
    bool writeWithListener(fBaseEvent *pEvent, bool block, bool notifyImmediatly);
    bool pauseWrites() {
        return m_pauseWrites;
    }

    bool isBlocked() {
        return m_bIsBlocked;
    }
    void setIsBlocked(bool flag) {
        m_bIsBlocked = flag;
    }

    bool atLowWater() {
        return m_bRecvLWM;
    }

    long getcurrentKeepAlive();
    long blockedFor() {
        return m_blockedFor;
    }
    long getInWriteLastEventRXCount() {
        return m_inWriteLastEventRXCount;
    }


    virtual int getType();

    ulonglong getCurrentResponseTime();
    ulonglong getMaxResponseTime();
    ulonglong getMinResponseTime();

    ulonglong getQueueSize();
    ulonglong getOutputByteCount();
    ulonglong getInputByteCount();
    ulonglong getEventRxCount();
    ulonglong getEventTxCount();

    ulonglong getWriteTime() {
        return m_inWriteTime;
    }
    ulonglong getLastTxTime() {
        return m_lastTxTime;
    }
    ulonglong getLastRxTime() {
        return m_lastRxTime;
    }



    fEventInputStream* getInputStream() {
        return m_pEventIn;
    }
    fEventOutputStream* getOutputStream() {
        return m_pEventOut;
    }
    fBaseEventFactory* getFactory() {
        return m_pFactory;
    }

    void registerOOBHandler(int id, fOutOfBandEventHandler* handler);

//==================================================================
// Should be made protected / private with an inline call to get it
//==================================================================



    fProcessQueue *m_pQueue;
    fConnectionQueueListener *m_pListener;
    Poco::Mutex m_disconnectedListMutex;


  protected:
    static fConnectionFactory *m_pConnectionFactory;

    bool m_bIsBlocked;
    bool m_pauseWrites;
    bool m_bInWrite;
    bool m_bRecvLWM;
    bool m_bRecvHWM;
    bool m_bRecvAcc;
    bool m_bRecvPush;
    bool m_bRecvBlock;

	volatile bool m_bAlive;

    int m_queueBlockWeighting;

    long m_queueBlockLimit;
    long m_pushWaitLimit;
    long m_accessWaitLimit;
    long m_lastTxEventId;
    long m_lastRxEventId;
    long m_blockedFor;
    long m_inWriteTime;
    long m_inWriteLastEventRXCount;

    ulonglong m_eventTxCount;
    ulonglong m_eventRxCount;
    ulonglong m_lastTxTime;
    ulonglong m_lastRxTime;

    std::string m_id;
    std::string m_localId;

    fConnectionKeepAlive *m_pKeepAlive;
    fBaseEventFactory *m_pFactory;

    fEventOutputStream *m_pEventOut;
    fEventInputStream *m_pEventIn;

    fCloseListener *m_pCloseListener;
    fConnectionHandler *m_pHandler;
    void *m_pCloseObject;

  private:
	  DLL fConnection(fDriver *pDriver, fEventOutputStream *pOstream, fEventInputStream *pIstream, fBaseEventFactory *pFactory, bool doThreadedQueue, bool enablePriority, long initialKeepAliveInterval = 0);
	void finalize();
	void setupQueue(bool doThreadedQueue, bool threadPooling, int writeHandler, bool enablePriority);
    void setupKeepAlive();
    fConnectionWriteHandler* createWriteHandler(int writeHandler);
    fQueueHandler *m_pWriteHandler;

    bool m_bSupportThreadPools;

    long m_currentResponseTime;
    long m_minResponseTime;
    long m_maxResponseTime;
    long myOOBHandlersLen;
	long m_initialKeepAliveInterval;

    fDriver *m_pDriver;
    fSubject *m_pRemoteSubject;
    fOutOfBandEventHandler** myOOBHandlers;
    fQueue* pQueue;

    friend class fDefaultConnectionFactory;
};


class cInWriteMonitor{
    
public:
    cInWriteMonitor(fConnection* con) : p_fConnection(con){
        p_fConnection->setInWrite(true);
    }
    
    virtual ~cInWriteMonitor(){
        p_fConnection->setInWrite(false);
    }
private:
    fConnection* p_fConnection;
};
}
}
}
}
