/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nConnectionDataContainer;
class ObservableMapping;
class nNode;
class nLeafNode;

using namespace com::pcbsys::foundation::fbase;
/**
 * This class contains the details about an individual connection. It extends the Observable class
 * to allow a user program to be informed about changes to the statistics of the connection.
 *
 */
class nConnectionDetails :
    public Observable {
  public:
    nConnectionDetails(nConnectionDataContainer *pData);
    virtual ~nConnectionDetails(void);

    /**
     * Returns the unique connection ID used to identify this connection
     *
     * @return The connection ID as a String
     */
    virtual const std::string& getId();

    /**
     * Returns a string that the connection used to authenticate with the server.
     * The first entry is the primary principal and is the only one used in the ACL validation.
     * There will only be more than one entry in a client certificate validated SSL session
     * which will use CN@HOST as the primary principal followed by the user supplied principal.
     *
     * @return the string for the specified subject.
     */
    virtual std::string* getSubject(int& numSubject);


    /**
     * This method returns the protocol string, currently one of NSP, NHP, NSPS or NHPS.
     *
     * @return A String indicating the protocol used by this connection
     */
    virtual std::string getProtocol();

    /**
     * Returns an collection of nNodes that this connection is bound to.
     *
     * @return A map of nNode objects that this connection is bound to.
     */
    virtual std::map<std::string, nNode*>& getBoundNodes();

    /**
     * Returns the number of events that this connection has received from the remote client
     *
     * @return a long representing the number of events received by this connection
     */
    virtual longlong getEventsReceived();

    /**
     * Returns the number of events sent to the remote client
     *
     * @return a long representing the number of events transmitted by this connection
     */
    virtual longlong getEventsTransmitted();

    /**
     * Returns a protocol description of the last event received from the connection
     *
     * @return a String containing the protocol description of the last event received
     */
    virtual const std::string& getLastReceivedEvent();

    /**
     * Returns a protocol description of the last event transmitted from the connection
     *
     * @return a String containing the protocol description of the last event transmitted
     */
    virtual const std::string& getLastTransmittedEvent();

    /**
     * This field is updated by the client heartbeat and as such only changes when the server
     * receives a heart beat from the client
     *
     * @return a int in milliseconds of the last request/response
     */
    virtual int getLatency();

    /**
     * This queue size is the internal server buffer where all events are pushed awaiting delivery
     * A large number here or a number that is not moving maybe indicative of a slow or problematic
     * connection.
     *
     * @return a long representing the queue size
     */
    virtual int getQueueSize();

    /**
     * Returns the name of the realm
     *
     * @return the name of the realm
     */
    virtual const std::string& getRealmName();

    /**
     * Returns the number of bytes that this connection has received from the remote client
     *
     * @return Long count
     */
    virtual longlong getReceivedByteCount();

    /**
     * Returns the Selector that the connection used to bind to a channel/queue
     *
     * @param leafNode The node being queried
     * @return the selector used for event filtering as a String
     * @throws nAdminIllegalArgumentException is thrown if leafNode is null
     */
    virtual const std::string& getSelector(nLeafNode *pLeafNode);

    /**
     * Returns the timestamp since the last received event
     *
     * @return a long representing the timestamp since the last received event
     */
    virtual longlong getTimeOfLastReceive();

    /**
     * Returns the number of milliseconds since the last event was sent
     *
     * @return a long representing the timestamp since the last transmitted event
     */
    virtual longlong getTimeOfLastTransmit();

    /**
     * Returns the number of bytes that this connection has transmitted to the remote client
     *
     * @return the number of bytes transmitted by this connection as a long
     */
    virtual longlong getTransmittedByteCount();

    /**
     * Returns the number of milliseconds that the connection has been active for
     *
     * @return a long representing the number of ms the server has been up
     */
    virtual longlong getUpTime();

    /**
     * This method will show that after this connection has received a delete callback, whether the close was
     * initiated by the client. The client close is generated from the nSessionFactory.close(nSession) method. Other
     * closes or disconnections will return false, since the client did not send a session close event.
     *
     * @return true if the client initiated the session close
     */
    virtual bool wasClosedByClient();

  protected:
    virtual void update(Observable *pObs, void *pObj);

    nConnectionDataContainer *m_pData;
    ObservableMapping *m_pMapping;

    friend class nPkgReconnectHandler;
    friend class nPkgStatusListener;
    friend class nServiceNode;
    friend class ObservableMapping;
    friend class nChannelListener;
    friend class nPkgListenerMapper;
    friend class ClusterNodeConnectionListener;
    friend class ConnectionStatusHandler;
};

}
}
}
}
