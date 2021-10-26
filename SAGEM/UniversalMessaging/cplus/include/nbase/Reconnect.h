/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

class nChannelQueue;

class Reconnect {
  public:
    Reconnect(nChannelQueue *pQueue);
    virtual ~Reconnect(void);

    int getAttempts();
    int getMaxAttempts();
    void reset();
    void execute();

  private:
    nChannelQueue *m_pQueue;
    int m_maxAttempts;
    int m_attempts;
};

}
}
}
}
