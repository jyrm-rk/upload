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
namespace nirvana {
namespace client {

/**
* This interface should be implemented by classes wishing to register to receive
* callbacks when connections are added or removed to a nirvana channel
*/
class nChannelConnectionListener {
  public:
    nChannelConnectionListener(void);
    virtual ~nChannelConnectionListener(void);

    /**
    * This method is called asynchronously when a new connection is added to the
    * nirvana channel.
    *
    * @param connectionId The channel connection's ID
    * @param *pSubject A string array of the subjects associated with the channel connection
    * @param nSubject The number of subjects
    * @param filter A string representation of the filter associated with the channel connection
    * @param protocol A string representation of the protocol (i.e. nsp, nhp, nsps or nhps) associated with the channel connection
    * @param subscriberName If the connection is a named subscriber, this is the name associated with that subscription
    *
    */
    virtual void newConnection(std::string connectionId, std::string *pSubject, int nSubject, std::string filter, std::string protocol, std::string subscriberName) = 0;

    /**
    * This method is called asynchronously when a connection is removed from the
    * nirvana channel.
    *
    * @param connectionId The channel connection's ID
    *
    */
    virtual void delConnection(std::string connectionId) = 0;
};

}
}
}
}
