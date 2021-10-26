/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fExternalable.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;

class nConnectionStatus :
    public fExternalable, public CountableObject {
  public:
    nConnectionStatus(void);
    virtual ~nConnectionStatus(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);

    const std::string& getId();
    int getQueueSize();
    int getSentEventId();
    int getReceivedEventId();
    int getLatency();
    longlong getSentCount();
    longlong getSentTime();
    longlong getSentBytes();
    longlong getReceivedCount();
    longlong getReceivedTime();
    longlong getReceivedBytes();
    longlong getUptime();

  private:
    static const int sQSize = 0;
    static const int sLatency = 1;
    static const int sRxEvent = 2;
    static const int sTxEvent = 3;
    static const int sTime = 0;
    static const int sTxCount = 1;
    static const int sTxTime = 2;
    static const int sTxByte = 3;
    static const int sRxCount = 4;
    static const int sRxTime = 5;
    static const int sRxByte = 6;

    int m_intArray[4];
    longlong m_longArray[7];
    std::string m_id;
};

}
}
}
}
