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

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
using namespace foundation::fbase;

/**
 * This class is a container for all the information that defines a channel
 * join.
 */
class nJoinInformation : public CountableObject {
  public:

    /**
     * Constructs a nJoinInformation object containing all the required information to define a channel join.
     *
     * @param channelName The channel which this information relates to
     * @param hopCount The number of hops before the event is expired
     * @param selector The message select which controls which events are processed
     * @param source If this channel is the source/destination
     * @param lastEID The last EID processed for this join
     * @param allowPurge Whether purges are propagated through this join
     */
    nJoinInformation(std::string& channelName, int hopCount, std::string& selector, bool source, longlong lastEID, bool allowPurge);
    virtual ~nJoinInformation(void);

    /**
    * If this the source for the join or events are sent to this channel
    *
    * @return bool flag
    */
    DLL bool isSource();

    /**
    * Returns a bool indicating if purge requests are propagated over the join link
    * @return bool flag
    */
    DLL bool allowPurgeRequests();

    /**
    * Returns the name of the destination channel if this channel is the source of the join
    * otherwise returns null
    *
    * @return String channel name
    */
    DLL std::string getDestination();


    /**
    * Returns the name of the source channel if the channel is not the source of the join
    * otherwise returns null
    *
    * @return String channel name
    */

    DLL std::string getSource();

    /**
    * Returns the selector string
    *
    * @return The message selector
    */
    DLL std::string getSelector();

    /**
    * The number of hops before the event is expired
    *
    * @return int resend or hop count
    */
    DLL int getHopCount();

    /**
    * The last Event ID processed by this join
    *
    * @return long Event ID
    */
    DLL longlong getLastEID();

    /**
     * Returns true if this join is an archival join
     *
     * @return boolean is archival
     */
    bool isArchival();

  private:
    std::string m_channel;
    std::string m_selector;
    int m_hopCount;
    longlong m_lastEID;
    bool m_bIsSource;
    bool m_bAllowPurgeRequests;
    bool m_bArchival;
};

}
}
}
}
