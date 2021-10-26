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

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fConnectionSettings {
    
  public:
    fConnectionSettings(void);
    virtual ~fConnectionSettings(void);

    static void setPushWaitLimit(int pushWait);
    static int getPushWaitLimit();
    static void setAccessWaitLimit(int accessWait);
    static int getAccessWaitLimit();
    static void setBlockLimit(int blockWait);
    static int getBlockLimit();
    static void setBlockWeighting(int blockWeighting);
    static int getBlockWeighting();
    static void setHWMark(int hwMark);
    static int getHWMark();
    static void setLWMark(int lwMark);
    static int getLWMark();
    static void setSocketConnectTimeout(int sTimeout);
    static int getSocketConnectTimeout();
    static std::string getProxyHost();
    static int getProxyPort();
    static void setProxy(const std::string& host, int& port);
    
    
    static bool isEnablePriority();
    static void setEnablePriority(bool flag);
    
    static const int sPeakWriteHandler = 0x1;
    static const int sDirectWriteHandler = 0x2;

    
    static std::string m_sProxyHost;
    static int m_sProxyPort;
    static int m_sWriteHandlerType;
    static int m_sPermittedMissedKeepAlives;
    static int socketReceiveBufferSize;
    static int socketSendBufferSize;

private:
    static int m_sLowWMark;
    static int m_sHighWMark;
    
    static bool sm_bEnablePriority;

    static int m_sPushWaitLimit;
    static int m_sAccessWaitLimit;
    static int m_sQueueBlockLimit;
    static int m_sQueueBlockWeighting;
    static int m_sSocketConnectionTimeout;
};

}
}
}
}
