/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fDriverConfig;
}
}
}
namespace nirvana {
namespace nbase {
class nDriverStatus;
}
namespace nAdminAPI {

using namespace nbase;
using namespace foundation::fbase;
using namespace foundation::drivers::configuration;

class nInterfaceManager;
class nInterface;

/**
 * Contains the status of a Nirvana Realm server interface
 */
class nInterfaceStatus :
    public Observable {
  public:
    /**
     * Constructs a new nInterfaceStatus
     * @param *pCfg the nDriverStatus for this object
     * @param *pIm the interface manager which this object is to use
     */
    nInterfaceStatus(nDriverStatus *pCfg, nInterfaceManager *pIm);
    virtual ~nInterfaceStatus(void);

    /**
     * Returns the number of bytes this interface has received
     *
     * @return long byte count
     */
    virtual longlong getRxBytes();

    /**
     * Returns the number of bytes this interface has transmitted
     *
     * @return long byte count
     */
    virtual longlong getTxBytes();

    /**
     * Returns the total number of connections created by this interface
     *
     * @return long count
     */
    virtual longlong getTotalConnections();

    /**
     * Returns the number of idle threads waiting for connections
     *
     * @return long count
     */
    virtual int getCurrentIdleCount();

    /**
     * Returns the total number of connections which failed during the initial
     * security handshake and validation
     *
     * @return long count
     */
    virtual longlong getTotalFailedConnections();

    /**
     * Returns the total milliseconds that there was no accept thread processing
     * new connections
     *
     * @return long milliseconds
     */
    virtual longlong getWaitTime();

    /**
     * This method returns the interface configuration details
     *
     * @return nInterface object containing the interface details
     */
    virtual nInterface* getInterface();

    /**
    * Indicates a stopped state on an interface
    */
    static const int s_stopped = 0;
    /**
    * Indicates a started state on an interface
    */
    static const int s_started = 1;
    /**
    * Indicates an interface with an error during startup
    */
    static const int s_error = 3;

    /**
     * Only valid if the state is s_error
     *
     * @return Exception message created during interface startup
     */
    virtual const std::string& getErrorMessage();

    /**
     * Returns the total number of times the thread pool reached 0 idle
     *
     * @return longlong count
     */
    virtual longlong getPoolExhausted();

    /**
     * Returns the current status of this interface. Can be one of stopped, started, paused or error
     *
     * @return current status
     */
    virtual int getStatus();

    /**
     * Return the total time spent authenticating connections
     *
     * @return longlong milliseconds
     */
    virtual longlong getTotalAuthenticationTime();

    /**
     * Return a string repsentation of the interface configuration
     *
     * @return the string that represents the interface configuration
     */
    virtual std::string toString();

    /**
    * Return the amount of MBs read by this interface / second
    *
    * @return Current rate of MBs read
    */
    int getReadBandWidth();

    /**
    * Return the total amount of MBs written by this interface / second
    *
    * @return Total MBs written
    */
    int getWriteBandWidth();

    /**
    * Return the total amount of MBs read by this interface
    *
    * @return Total MBs read
    */
    longlong getTotalReads();

    /**
    * Return the total amount of MBs written by this interface
    *
    * @return Total MBs written
    */
    longlong getTotalWrites();



  protected:
    virtual void setInterface(fDriverConfig *pCfg, nInterfaceManager *pIm);
    virtual void setErrorMessage(const std::string& msg);
    virtual void setStatus(int status);

    virtual void setConnCount(longlong conn);
    virtual void setAuthTime(longlong auth);
    virtual void setFailedConn(longlong failed);
    virtual void setExhaustedTime(longlong exhausted);
    virtual void setExhaustedCount(int exhausted);
    virtual void setIdleThreads(int idle);
    virtual void setTxBytes(longlong tx);
    virtual void setRxBytes(longlong rx);
    void setReadBW(int readBW);
    void setWriteBW(int writeBW);
    void setTotalReads(longlong totalReads);
    void setTotalWrites(longlong totalWrites);

  private:
    int m_status;
    std::string m_errMsg;
    nInterface *m_pConfig;
    longlong m_tx;
    longlong m_rx;
    longlong m_conn;
    longlong m_failedConn;
    int m_idleThreads;
    longlong m_authTime;
    longlong m_exhaustedTime;
    int m_exhausted;
    int myReadBW;
    int myWriteBW;
    longlong myTotalReads;
    longlong myTotalWrites;

    friend class nInterfaceManager;
    friend class nPkgAdminListener;
    friend class nClusterNode;
};

}
}
}
}
