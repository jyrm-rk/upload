/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nConnectionDetails.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
/**
 * This class contains additional information about a channel connection. Typically a channel connection is a
 * subscription from a client to a channel on a realm server.
 */
class nChannelConnectionDetails :
    public nConnectionDetails {
  public:
    /**
     * Constructs a new nChannelConnectionDetails
     * @param *pData the nConnectionDataContainer for the connection
     * @param selector the selector used in the subscription
     * @param name the name of the subscriber
     * @param channel the name of the channel the connection is made to
     */
    nChannelConnectionDetails(nConnectionDataContainer *pData, const std::string& selector, const std::string& name, const std::string& channel);
    virtual ~nChannelConnectionDetails(void);
    /**
     * Returns the type of the connection details this object represents.  In this case the object represents channel connection details.
     * @return the type of connection details represented
     */
    virtual int getType ();
    /**
    * If the connection used a nNamedObject then this method would return the name of the nNamedObject. This method
    * can return null if there is no nNamedObject associated with this connection.
    *
    * @return std::string name of the nNamedObject
    */
    virtual const std::string& getNamedSubscriber();


    /**
     * Get the name of the channel
     *
     * @return String name of the channel
     */
    virtual const std::string& getChannel();

    /**
     * Returns the message selector used for the connection. If no selector was used then this method returns null.
     *
     * @return Message selector used.
     */
    virtual const std::string& getSelector();

  private:
    std::string m_selector;
    std::string m_namedSubscriber;
    std::string m_channel;
};

}
}
}
}
