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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {
class nGetDetails;
}
}
namespace client {

using namespace nbase::events;

/**
 * Container class, containing statistics on the queue
 */
class nQueueDetails {
  public:
    virtual ~nQueueDetails(void);

    /**
    * Retrieves the total number of events in this queue
    *
    * @return The current number of events on the queue
    */
    DLL int getNoOfEvents();

    /**
    * Retrieves the timestamp of the last event in this queue
    * @return The timestamp of the last event in the queue as a long
    */
    DLL longlong getLastEventTime();

    /**
    * Retrieves the timestamp of the first event in this queue
    *
    * @return The timestamp of the first event in the queue as a long
    */
    DLL longlong getFirstEventTime();

    /**
    * Retrieves the total size in bytes the queue currently consumes
    *
    * @return total size in bytes the queue currently consumes
    */
    DLL longlong getTotalMemorySize();

    /**
    * Retrieves the total number of readers on this queue
    *
    * @return The current number of readers on the queue as an int
    */
    DLL int getNoOfReaders();

  private:
    nQueueDetails(nGetDetails *pResp);
    int m_noOfReaders;
    int m_noEvents;
    longlong m_firstEventTime;
    longlong m_lastEventTime;
    longlong m_totalSize;

    friend class nChannelImpl;

};

}
}
}
}
