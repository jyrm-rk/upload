/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

namespace Poco {

class Timer;

}

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {

class fConnection;

class fConnectionKeepAlive {
  public:
	fConnectionKeepAlive(fConnection *pConnection, long initialKeepAliveInterval = 0);
    virtual ~fConnectionKeepAlive(void);

    void close();
    void reSchedule(bool sentKA);
    void setKeepAliveTime(long newTime);
    long getKeepAliveTime();
	static long m_ClientKeepAliveTimer;
	static long m_ServerKeepAliveTimer;

  protected:
    int m_missedKeepAlives;
    long m_lastEventCount;

  private:
    void onTimer (Poco::Timer &timer);
    bool checkStillReceivingEvents();
	void finalize();

    fConnection *m_pConnection;
    Poco::Timer *m_pTimer;
    long m_nextHeartBeat;
	long m_keepAlive;
};

}
}
}
}
