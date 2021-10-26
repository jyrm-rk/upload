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
#include "nBaseChannelAttributes.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
class nRealmAdmin;
}
namespace nbase {
class nBaseChannelAttributes;
}
/*! \namespace com.pcbsys.nirvana.client
Documentation for the Nirvana C++ Client API
*/
namespace client {

class nChannelImpl;
class nSession;
class nChannelAttributes;

using namespace nbase;

/**
 * This is the base class for all nirvana channel types, including queues and normal pub/sub channels
 * and as such has no public methods
 *
 * @see nChannel
 * @see nQueue
 */
class nAbstractChannel : public CountableObject {
  public:
    nAbstractChannel(nChannelImpl *pChannel);
    DLL virtual ~nAbstractChannel(void);

    /**
     * Returns the nSession used to create/find this channel
     *
     * @return the nSession associated with this channel
     */
    DLL nSession* getSession();

    /**
     * Returns the size of the underlying event queue waiting for delivery via the go method
     *
     * @return number of events to be delivered
     */
    DLL int getQueueSize();

    /**
     * Update the Protocol Buffer definition for the store.
     *
     * @param descriptors An array of descriptors as byte[] to set as the new channel's descriptors.
     * @throws nIllegalArgumentException descriptors cannot be sent to the realm.
     * @throws nSessionNotConnectedException if the session for this store is not currently connected
     * @throws nRequestTimedOutException if there is no response to the request to set the store's descriptors within the timeout period.
     * @throws nSessionPausedException if the session for this store is currently paused
     */
	DLL void updateProtobufDefinitions(const std::vector<ProtobufDescriptor*> & descriptors);

  protected:
    nChannelImpl *m_pChannel;
    nBaseChannelAttributes *getBaseAttributes();
    virtual nChannelAttributes* getClientChannelAttributes() = 0;

    friend class nChannelImpl;
    friend class nChannelAttributes;
    friend class nChannelIterator;
    friend class nQueueAsyncReader;
    friend class nQueueAsyncTransactionReader;
    friend class nQueueSyncReader;
    friend class nQueueSyncTransactionReader;
    friend class nQueueReader;
    friend class nSession;
    friend class nTransaction;
    friend class nTransactionAttributes;
    friend class com::pcbsys::nirvana::nAdminAPI::nRealmAdmin;

};

}
}
}
}

