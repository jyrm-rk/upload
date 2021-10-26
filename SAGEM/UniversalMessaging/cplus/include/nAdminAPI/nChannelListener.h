/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nChannelConnectionListener.h"
#include "Poco/Mutex.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nLeafNode;
class nAPIConnectionListener;

using namespace com::pcbsys::nirvana::client;

/**
 * receives callback each time a new connection is added to or deleted from the channel
 */
class nChannelListener :
    public nChannelConnectionListener {
  public:
    /**
     * Constructs a new listener for the given channel
     * @param *pLeaf the leaf node to listen for connection changed on
     * @param *pList
     */
    nChannelListener(nLeafNode *pLeaf, nAPIConnectionListener *pList);
    virtual ~nChannelListener(void);
    /**
     * called when a new connection is added to the channel
     * @param connectionId ID of the new connection
     * @param *pSubject user name for the connection
     * @param filter selector applied
     * @param protocol protocol used
     * @param subscriberName subscription name
     */
    virtual void newConnection(std::string connectionId, std::string *pSubject, int nSubject, std::string filter, std::string protocol, std::string subscriberName);
    /**
     * called when a connection is removed from the channel
     * @param connectionId ID of the deleted connection
     */
    virtual void delConnection(std::string connectionId);

  protected:
    nLeafNode *m_pLeafNode;
    nAPIConnectionListener *m_pListener;

    Poco::Mutex m_newMutex;
    Poco::Mutex m_delMutex;
};

}
}
}
}
