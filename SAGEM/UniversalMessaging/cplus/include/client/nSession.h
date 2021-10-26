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
#include "fSortedList.h"
#include "nAbstractChannel.h"
#include "nDataGroupAdmin.h"
#include "nBaseDataGroup.h"
#include "fPrioritized.h"
#include "nServerExtensionCallback.h"
#include "nStorePermission.h"

#include "Poco/Random.h"
#include "Poco/Thread.h"
#include "Poco/SynchronizedObject.h"

#include <string>
#include <map>
#include <vector>
#include <list>
#include "nExceptionEvent.h"

typedef std::vector<nStorePermission> nStorePermissionList;

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fDriverFactory;
class fDriver;
class fConnectionDetails;
}
namespace io {
class fConnection;
class fBaseEventFactory;
class fConnectionQueueListener;
}
}
namespace nirvana {
namespace nbase {
class nClientChannelList;
class nBaseChannelAttributes;
class nBaseRealm;
class nDataGroupEventPump;

namespace events {
class nSynchronous;
class nEvent;
class nPublished;
class nTimeOutUpdate;
class nStreamStatusUpdate;
class nDataGroupStreamTransitionManager;
class nDataStreamPublish;
}
}
namespace client {

class nSessionAttributes;
class nRunLoop;
class nRequestResponseContainer;
class nReconnectHandler;
class nConnectionQueueListener;
class nChannel;
class nChannelAttributes;
class nChannelImpl;
class nAsyncExceptionListener;
class nConsumeEvent;
class nQueue;
class nSubject;
class nRealm;
class nDataGroup;
class nDataGroupListener;
class nDataStreamListener;
class nDataStream;
class nFindResult;
class nSubscriptionAttributes;
class nConflationAttributes;
class nRegisteredEvent;
class nMulticastReceiver;
class nCreateResult;
class nDeleteResult;

using namespace com::pcbsys::foundation::drivers;
using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::collections;
using namespace com::pcbsys::foundation::fbase::collections;
using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::nirvana::nbase::events;

/**
 * This class represents a Nirvana session, the logical connection between the client API and the Nirvana realm.
 * A Nirvana session is defined through a set of session attributes that is represented by the nSessionAttributes
 * class in the same package. This set of attributes is then passed to the session factory object which creates
 * the session. A session object needs to be initialised in order for the physical connection to be opened to the server.
 * Please note that when using a session to retrieve events from a channel or queue, you can only have 1 listener
 * specifying a set filter per session object. For example if you have a selector set as CCY='USD' you can use that filter
 * by only one object implementing the nEventListener interface per session, otherwise a nUserAlreadySubscribedException
 * will be thrown.
 */
class nSession : public NotifyableCountableObject {
    friend class nMulticastReceiver;
  public:
    DLL virtual ~nSession(void);

    /**
    * Initialises a session object, opening the physical connection to the
    * server
    *
    * @throws nRealmUnreachableException    if the realm is currently not available
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nSessionAlreadyInitialisedException
    *                                       The session has already been initialised
    * @throws nSecurityException       Insufficient privileges
    */
    DLL void init();

    /**
    * Initialises a session object, opening the physical connection to the
    * server
    *
    * @param disconnectIfClusterFails - if the cluster loses quorum, should this nSession become disconnected (true/false)
    * @throws nRealmUnreachableException    if the realm is currently not available
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nSessionAlreadyInitialisedException
    *                                       The session has already been initialised
    * @throws nSecurityException       Insufficient privileges
    *
    * @since 4.0
	* @deprecated as of 10.7. When in future releases the API is removed the behaviour will be as the flag is set to true,
    * i.e. non-admin client sessions will be disconnected when cluster is not formed.
    */
	UM_DEPRECATED DLL void init(bool disconnectIfClusterFails);

    /**
    * Adds a new connection queue listener, which will be notified when
    * the internal outbound queue reaches defined limits.  Such as
    * <p></p>
    * Reaching high water mark
    * Reaching low water mark
    * Exceeding the time it should take to access the queue object
    * Exceeding the time it should take to push an event onto the queue
    * Exceeding the time for a queue to be blocked due to reaching its high water mark
    *
    * @param *pListener The asynchronous exception listener to be added
    * @throws nIllegalArgumentException if the listener is Null of if already has a listener registered
    */
    DLL void addConnectionQueueListener(nConnectionQueueListener *pListener);

    /**
    * Finds and returns a nirvana channel that exists on the realm this session
    * is connected to, or a joined realm.
    *
    * @param *pAttr The channel attributes of the channel to be found
    * @return The nChannel object if it was found.
    * @throws nChannelNotFoundException     The channel specified could not be found
    * @throws nUnknownRemoteRealmException  The remote realm responded with an unknown exception
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nIllegalChannelMode           The channel referenced is a queue
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL nChannel* findChannel(nChannelAttributes *pAttr, bool useCache = true);

    /**
    * Returns true if this session is still connected with the remote realm
    *
    * @return result of the test
    */
    DLL bool isConnected();

    /**
    * Adds a new asynchronous exception listener, which will be notified when
    * an exception occurs while performing an asynchronous operation
    *
    * @param *pListener The asynchronous exception listener to be added
    * @throws nIllegalArgumentException Illegal parameter, check the message for more information
    */
    DLL void addAsyncExceptionListener(nAsyncExceptionListener *pListener);

    /**
    * Returns the unique session Id for this session
    *
    * @return String representation of this ID
    * @throws nSessionNotConnectedException Current session is not connected
    */
    DLL std::string getId();

    /**
    * Closes this session, disconnecting from the server and killing all threads
    */
    DLL void close();

    /**
    * Returns the number of bytes sent to the server using this session object
    *
    * @return longlong byte count
    */
    DLL ulonglong getOutputByteCount();

    /**
    * Returns the number of bytes received from the server on this session object
    *
    * @return longlong byte count
    */
    DLL ulonglong getInputByteCount();

    /**
    * Finds and returns a nirvana queue that exists on the realm this session
    * is connected to, or a joined realm.
    *
    * @param *pAttr The channel attributes of the queue to be found
    * @return The nChannel object if it was found.
    * @throws nChannelNotFoundException     The specified queue could not be found
    * @throws nUnknownRemoteRealmException  The remote realm responded with an unknown exception
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nIllegalChannelMode           The queue referenced is a channel
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL nQueue* findQueue(nChannelAttributes *pAttr);

    /**
    * Gets the current time on the server
    *
    * @return The current time on the Realm Server as a longlong value
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nSessionPausedException The session is currently paused, please resume
    *
    */
    DLL ulonglong getServerTime();

	/**
	* If the realm this session is connected to is part of a cluster then this function will return true
	*
	* @return true if part of a cluster
	*/
	DLL bool isMemberOfCluster();

  /**
  *   Creates new channels on the realm this session is connected.
  *
  *   @param attr The channel attributes array containing the new channel or queue attributes
  *   @param numAttr The length of the attr array
  *   @param numResults The length of the array that is returned
  *   @return an nCreateResult array representing the newly created nirvana channels or queues or exceptions
  *   @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
  *   @throws nSecurityException             User is not authorised for the function
  *   @throws nChannelAlreadyExistsException The channel already exists
  *   @throws nSessionNotConnectedException  Current session is not connected
  *   @throws nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
  *   @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
  *   @throws nIllegalArgumentException      Illegal parameter, check the message for more information
  *   @throws nSessionPausedException        The session is currently paused, please resume
  */
  DLL nCreateResult** create(nChannelAttributes** attr, int numAttr, int& numResults);

    /**
    *   Creates new channels on the realm this session is connected.
    *
    *   @param attr The channel attributes array containing the new channel or queue attributes
    *   @param numAttr The length of the attr array
    *   @param numResults The length of the array that is returned
    *   @param permissions vector containing vectors of permission entries
    *                        to be applied during creation. Permission lists and channel attributes are
    *                        mapped by their order.
    *   @return an nCreateResult array representing the newly created nirvana channels or queues or exceptions
    *   @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception 
    *   @throws nSecurityException             User is not authorised for the function 
    *   @throws nChannelAlreadyExistsException The channel already exists 
    *   @throws nSessionNotConnectedException  Current session is not connected 
    *   @throws nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence 
    *   @throws nRequestTimedOutException      The server has not responded to the request in the timeout period 
    *   @throws nIllegalArgumentException      Illegal parameter, check the message for more information 
    *   @throws nSessionPausedException        The session is currently paused, please resume
    *   @since 9.12
    */
  DLL nCreateResult** create(nChannelAttributes** attr, int numAttr, int& numResults, const std::vector<nStorePermissionList>& permissions);

    /**
    *   Deletes all channels in the array of nChannelAttributes array.
    *   @param attr The channel attributes array to delete
    *   @param numAttr The length of the attr array
    *   @param numResults The length of the array that is returned
    *   @return returns an nDeleteResult array representing the deleted nirvana channels or queues or exceptions 
    *   @throws nUnknownRemoteRealmException">   The remote realm responded with an unknown exception 
    *   @throws nSecurityException">             User is not authorised for the function 
    *   @throws nChannelNotFoundException">      The channel doesn't exist 
    *   @throws nSessionNotConnectedException">  Current session is not connected 
    *   @throws nUnexpectedResponseException">   Internal Error has occured, since we received a response from the server out of sequence 
    *   @throws nRequestTimedOutException">      The server has not responded to the request in the timeout period 
    *   @throws nIllegalArgumentException">      Illegal parameter, check the message for more information 
    *   @throws nSessionPausedException">        The session is currently paused, please resume 
    */
    DLL nDeleteResult** remove(nChannelAttributes** attr, int numAttr, int& numResults);

    /**
    * Creates a new channel on the realm this session is connected.
    * <p></p>
    * If the channel attributes specify a realm different than the one this session is
    * connected to, a transparent redirection will occur and the channel will be created on
    * that realm.
    *
    * @param *pAttr       The channel attributes object containing the parameters for
    *                     the new channel to be created
    * @param p_initialEID The value to start the event id at
    * @return an nChannel object representing the newly created nirvana channel
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL nChannel* createChannel(nChannelAttributes *pAttr, ulonglong p_initialEID = 0);
    
    /**
    * Creates a new channel on the realm this session is connected.
    * <p/>
    * If the channel attributes specify a realm different than the one this session is
    * connected to, a transparent redirection will occur and the channel will be created on
    * that realm.
    *
    * @param pAttr              The channel attributes object containing the parameters for
    *                           the new channel to be created
    * @param p_initialEID        The value to start the event id at
    * @param channel_permissions vector containing nStorePermission entries with security privileges that
    *                           can be applied for a specific user
    * @return an nChannel object representing the newly created nirvana channel
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    * @since 9.12
    */
    DLL nChannel* createChannel(nChannelAttributes *pAttr, ulonglong p_initialEID, const std::vector<nStorePermission>& channel_permission);

    /**
    * Gets the session attribute object associated with this session
    *
    * @return the nSessionAttributes object associated with this session
    */
    DLL nSessionAttributes* getAttributes();

    /**
    * Gets the subject associated with this nirvana session
    *
    * @return an nSubject object with the subject details associated with the session
    * @throws nSessionNotConnectedException If the session is not currently connected with the server
    */
    DLL nSubject* getSubjectObject();

    /**
    * Remove the reconnect handler from the session
    *
    * @param *pHandler - the reconnect handler to be removed
    */
    DLL void removeReconnectHandler(nReconnectHandler *pHandler);

    /**
    * Add a session reconnect handler to the session. Usually the handler is passed
    * in when the session is constructed from the nSessionFactory, however this method
    * allows you to pass in a handler once a session has been constructed.
    *
    * @param *pHandler - the nReconnectHandler object for this session
    */
    DLL void addReconnectHandler(nReconnectHandler *pHandler);

    /**
    * Returns the sessions server realm name
    *
    * @return Realm Server name
    * @throws nSessionNotConnectedException If the session is not currently connected with the server
    */
    DLL std::string getServerRealmName();

    /**
    * Gets the subject associated with this nirvana session
    *
    * @return an nSubject array object with the subject details associated with the session
    * @throws nSessionNotConnectedException If the session is not currently connected with the server
    */
    DLL nSubject** getSubject(int& numSubject);

    /**
    * Creates a new queue on the realm this session is connected.
    * <p></p>
    * If the channel attributes specify a realm different than the one this session is
    * connected to, a transparent redirection will occur and the queue will be created on
    * that realm.
    *
    * @param *pAttr The channel attributes object containing the parameters for the new queue to be created
    * @param privMask     Privilege mask to apply to the "everyone" subject for this queue
    * @return an nQueue object representing the newly created nirvana queue
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL nQueue* createQueue(nChannelAttributes *pAttr, long privMask = -1);

    /**
    * Creates a new queue on the realm this session is connected.
    * <p / >
    * If the channel attributes specify a realm different than the one this session is
    * connected to, a transparent redirection will occur and the queue will be created on
    * that realm.
    *
    * @param pAttr                          The channel attributes object containing the parameters for the new queue to be created
    * @param permissions                    vector containing nStorePermission permission entries with security privileges that
    *                                       can be applied for a specific user
    * @return an nQueue object representing the newly created nirvana queue
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    * @since 9.12
    */
    DLL nQueue* createQueue(nChannelAttributes *pAttr, const std::vector<nStorePermission>& permissions);

    /**
    * Deletes a nirvana channel that exists on the realm this session is connected to, or a joined realm.
    * <p></p>
    * Note: all events in that channel will be deleted too and are not recoverable.
    *
    * @param *pAttr The channel attributes of the channel to be deleted
    * @throws nUnknownRemoteRealmException  The remote realm responded with an unknown exception
    * @throws nSecurityException            User is not authorised for the function
    * @throws nChannelNotFoundException     The specified channel could not be found
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL void deleteChannel(nChannelAttributes *pAttr);

    /**
    * Update the current session attributes with the RNAMEs retrieved from the server.
    */
    DLL void updateConnectionListWithServerList();

    /**
    * Gets a reference to a realm that is already joined
    *
    * @param name A string specifying the name of the realm to be returned
    * @return An nRealm object referring to the realm, or null if no realm with that name is found
    * @throws nRealmNotFoundException       The realm name supplied could not be found on the server
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */

    DLL nRealm* getRealm(const std::string& name);

    /**
    * Adds a new connection queue listener, which will be notified when
    * the internal outbound queue reaches defined limits, such as
    * <p></p>
    * Reaching high water mark
    * Reaching low water mark
    * Exceeding the time it should take to access the queue object
    * Exceeding the time it should take to push an event onto the queue
    * Exceeding the time for a queue to be blocked due to reaching its high water mark
    *
    * @param *pListener The asynchronous exception listener to be added
    * @param hwm      true to receive notifications of reaching queue high water mark
    * @param lwm      true to receive notifications of reaching queue low water mark
    * @param access   true to receive notification of exceeding queue access time
    * @param push     true to receive notification of exceeding queue access and push time
    * @param block    true to receive notification of exceeding queue block time
    * @param unblock  true to receive notification of exceeding queue unblock time
    * @throws nIllegalArgumentException if the listener is Null of if already has a listener registered
    */
    DLL void addConnectionQueueListener(nConnectionQueueListener *pListener,
                                        bool hwm, bool lwm, bool access, bool push,
                                        bool block, bool unblock);

    /**
    * Adds (Joins) another realm to the realm this session is connected to
    *
    * @param *pNewRealm The realm to join as an nRealm object
    * @param *pSession A session to the realm we want to add to
    * @throws nRealmAlreadyBoundException   The realm is known by the server
    * @throws nRealmUnreachableException    The specified realm is already configured
    * @throws nRealmNotFoundException       The realm is not known by the server
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nNameSpaceConflictException   The realm conflicts with the existing namespace
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL void addRealm(nRealm *pNewRealm, nSession *pSession = NULL);

    /**
    * Creates a new channel on the realm this session is connected.
    * <p></p>
    * If the channel attributes specify a realm different than the one this session is
    * connected to, a transparent redirection will occur and the channel will be created on
    * that realm.
    *
    * @param *pAttr         The channel attributes object containing the parameters for
    *                     the new channel to be created
    * @param initialEID The value to start the event id at
    * @param privMask     Privilege mask to apply to the "everyone" subject for this channel
    * @return an nChannel object representing the newly created nirvana channel
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL nChannel* createChannel(nChannelAttributes *pAttr, ulonglong initialEID, long privMask);

    /**
    * Deletes a nirvana queue that exists on the realm this session is connected to, or a joined realm.
    * <p></p>
    * Note: all events in that queue will be deleted too and are not recoverable.
    *
    * @param *pAttr The channel attributes of the queue to be deleted
    * @throws nUnknownRemoteRealmException  The remote realm responded with an unknown exception
    * @throws nSecurityException            User is not authorised for the function
    * @throws nChannelNotFoundException     The specified channel could not be found
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL void deleteQueue(nChannelAttributes *pAttr);

    /**
    * Deletes (unjoins) another realm from the realm this session is connected to
    *
    * @param *pRealm The realm to unjoin as an nRealm object
    * @throws nRealmNotFoundException       The supplied realm could not be found on the server
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL void deleteRealm(nRealm *pRealm);

    /**
    * Returns a list of all known channels and queues
    *
    * @param nAttr the length of the returned array
    * @param folder specify the starting point in the namespace within which to retrieve the channels
    *
    * @return An nChannelAttributes array object referring to the channels, or null if no channels are defined
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL nChannelAttributes** getChannels(int& nAttr, const std::string folder = "");

    /**
    * Returns a comma separated list of RNAMEs which can be used to access the realm or cluster namespace.
    * This value is calculated and updated by the server which this session is currently connected to.
    *
    * @return Comma separated list of rnames which can be used to construct a nSessionAttributes.
    */
    DLL std::string getConnectionList();

    /**
    *  Returns the round trip time of the last synchronous request that was made
    * @return the current round trip time
    */
    DLL long getCurrentLatency();

    /**
    * Returns the outbound connection queue size
    *
    * @return the size of the queue
    */
    DLL ulonglong getQueueSize();

    /**
    * Returns a list of all known realms on the connected realm
    *
    * @return An nRealm array object referring to the realm, or null if no realms are defined
    * @throws nSecurityException            User is not authorised for the function
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
    * @throws nSessionPausedException       The session is currently paused, please resume
    */
    DLL nRealm** getRealms(int& numRealm);

    /**
    * Return the number of events received by this session
    *
    * @return the number of sent received
    */
    DLL ulonglong getReceivedEventCount();

    /**
    * Returns the rname that this session has used
    *
    * @return String representation of the rname
    * @throws nSessionNotConnectedException Current session is not connected
    */

    DLL std::string getRemoteId();

    /**
    * Return the number of events sent by this session
    *
    * @return the number of sent events
    */
    DLL ulonglong getSentEventCount();

    /**
    * Returns the unique connection id associated with this session by the server.
    *
    * @return the server's connection id for this nSession
    */

    DLL ulonglong getSessionConnectionId();

    /**
    * Removes an already added asynchronous exception listener, which will not
    * be notified of asynchronous exceptions anymore.
    *
    * @param *pListener The asynchronous exception listener to be added
    * @throws nIllegalArgumentException Illegal parameter, check the message for more information
    */

    DLL void removeAsyncExceptionListener(nAsyncExceptionListener *pListener);
    /**
    * Removes an already added connection queue listener, which will not
    * be notified of queue state changes anymore.
    *
    * @param *pListener The asynchronous exception listener to be added
    * @throws nIllegalArgumentException if the listener is Null of if no listener registered
    */

    DLL void removeConnectionQueueListener(nConnectionQueueListener *pListener);

    /**
    * Returns true if this session is paused
    *
    * @return result of the test
    */

    DLL bool isPaused();

    /**
    * This function pauses delivery of new events to all subscribed nEventListeners until resume is called
    *
    * @param release specifies whether to release any outstanding synchronous requests awaiting responses from the server
    */

    DLL void pause(bool release);

    /**
    * Resumes delivery of events to nEventListeners
    */

    DLL void resume();

    /**
    * Unblocks the thread of the given name that my be in a synchronous call.
    *
    * @param name the name of the thread
    */

    DLL void unblockThread(const std::string& name);

    /**
    * Set size of thread pool.
    *
    * @param size the size of the thread pool
    */

    DLL void setThreadPoolSize (int size);

	/**
	* Remove channel from cache
	*
	* @deprecated This function will be removed as it was unsafe. Calling this function now has no effect
	*/

	UM_DEPRECATED void removeChannelFromCache(nChannelAttributes *pAttr);

    /**
    * Get the stream Id for this session if initialised with an nDataStreamListener
    *
    * @return a string representation of the stream id
    */

    DLL virtual const std::string& getStreamId();

    /**
    * Pause the events being received by the Data Group Listener.
    * 
    * This is not currently implemented
    *
    * @throws Exception
    * @since 6.0
    */

    DLL virtual void pauseStream();

    /**
    * Resumes the events being received by the Data Group Listener.
    * 
    * 
    * This is not currently implemented
    *
    * @throws Exception
    * @since 6.0
    */

    DLL virtual void resumeStream();

    /**
    * Sends the event to the specified stream
    *
    * @param pEvt    the event to write to the stream
    * @param pStream the stream to write to
    * @param waitForResponse whether to wait for a response. Default = false
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */

    DLL	virtual void writeDataStream(nConsumeEvent *pEvt, nDataStream *pStream, bool waitForResponse = false);

    /**
    * Sends the event to the specified streams
    *
    * @param pEvt     the event to write to the streams
    * @param ppStreams the array of streams to write to
    * @param numStream the number of streams in the array
    * @param waitForResponse whether to wait for a response. Default = false
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */

    DLL virtual void writeDataStream(nConsumeEvent *pEvt, nDataStream **ppStreams, int numStream, bool waitForResponse = false);

    /**
    * Sends the events to the specified stream
    *
    * @param ppEvts   the array of events to write to the stream
    * @param numEvent the number of events in the array
    * @param pStream the stream to write to
    * @param waitForResponse whether to wait for a response. Default = false
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */

    DLL virtual void writeDataStream(nConsumeEvent **ppEvts, int numEvent, nDataStream *pStream, bool waitForResponse = false);

    /**
    * Sends the events to the specified streams
    *
    * @param ppEvts    the array of events to write to the stream
    * @param numEvent the number of events in the array
    * @param ppStreams the array of streams to write to
    * @param numStream the number of streams in the array
    * @param waitForResponse whether to wait for a response. Default = false
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */
    DLL virtual void writeDataStream(nConsumeEvent **ppEvts, int numEvent, nDataStream **ppStreams, int numStream,
                                     bool waitForResponse = false);

    /**
    * Sends each event in the list to its corresponding data stream
    * @param waitForResponse if true then the method will not return until it receives a response from the server
    * @param registered whether the event is registered. Default = false
    * @param list the <key,value> list of nConsumeEvent and data streams
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */
    DLL void writeDataStream(std::map<nConsumeEvent*, nDataStream*>* list, bool waitForResponse = false, bool isRegisteredEvent = false);

    /**
     * Sends the event to the specified data group
     *
     * @param pEvt       the event to write to the data group
     * @param pDataGroup the data group to write to
     * @param waitForResponse whether to wait for a response. Default = false
     * @param registered whether the event is registered. Default = false
     * @throws nSecurityException
     * @throws nRequestTimedOutException
     * @throws nSessionPausedException
     * @throws nSessionNotConnectedException
	 * @throws nPublishPausedException when publishing is paused server side
     * @since 6.0
     */
    DLL virtual void writeDataGroup(nConsumeEvent *pEvt, nDataGroup *pDataGroup, bool waitForResponse = false, bool registered = false);

    /**
    * Sends the event to all of the specified data groups
    *
    * @param pEvt        the event to write to the data groups
    * @param ppDataGroups the array of data groups to write to
    * @param numGroup the length of the ppDataGroups array
    * @param waitForResponse whether to wait for a response. Default = false
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */

    DLL virtual void writeDataGroup(nConsumeEvent *pEvt, nDataGroup **ppDataGroups, int numGroup, bool waitForResponse = false);

    /**
    * Sends the list of events to the specified data group
    *
    * @param ppEvts      the array of events to write to the group
    * @param numEvent the number of events in the array
    * @param pDataGroup the data group to write to
    * @param waitForResponse whether to wait for a response. Default = false
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */

    DLL virtual void writeDataGroup(nConsumeEvent **ppEvts, int numEvent, nDataGroup *pDataGroup, bool waitForResponse = false);

    /**
    * Sends the events to the specified streams
    *
    * @param ppEvts    the array of events to write to the stream
    * @param numEvent the number of events in the array
    * @param ppDataGroups the groups to write to
    * @param numGroup the number of groups in the array
    * @param waitForResponse whether to wait for a response. Default = false
    * @throws nSecurityException
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
	* @throws nPublishPausedException when publishing is paused server side
    * @since 6.0
    */

    DLL virtual void writeDataGroup(nConsumeEvent **ppEvts, int numEvent, nDataGroup **ppDataGroups, int numGroup, bool waitForResponse = false);

    /**
    * Sends each event in the list to its corresponding data group
    *
    * @param list the <key,value> list of nConsumeEvent and data groups
    * @param waitForResponse whether to wait for a response. Default = false
    * @param registered whether the event is registered. Default = false
    */

    DLL virtual void writeDataGroup(std::map<nConsumeEvent*, nDataGroup*>& list, bool waitForResponse = false, bool registered = false);

    /**
    * Create a new data group on the server. If the data group exists already, and the groups have already been retrieved by this nSession
    * the nDataGroup will be returned from the local list of data groups. Otherwise this method will send an event to the server.
    *
    * @param dataGroupName        the name of the data group to create
    * @param pListener            the instance of the nDataGroupListener that will receive the callbacks for this group. Default = NULL
    * @param pConflationAttributes the conflation strategy to use on the data group. Default = NULL
    * @return the data group matching the specified name
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    * @throws nIllegalArgumentException
    * @see nConflationAttributes
    * @since 6.0
    */

    DLL virtual nDataGroup* createDataGroup(const std::string& dataGroupName, nDataGroupListener *pListener = NULL,
                                            nConflationAttributes *pConflationAttributes = NULL, bool enableMulticast = false,unsigned int priorityLevel = fPrioritized::sDefaultPriority);

    /**
    * Create new data groups on the server if they don't exist, or return them from the local list if found
    *
    * @param pDataGroupNames       the names of the data groups to create
    * @param numGroup              the number of group names in the array
    * @param pConflationAttributes the conflation strategy to be applied to the data groups. Default = NULL
    * @return the array of data groups created / found
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    * @throws nIllegalArgumentException
    */

    DLL virtual std::list<nDataGroup*>* createDataGroups(std::string *pDataGroupNames, int numGroup,
            nConflationAttributes *pConflationAttributes = NULL);



    /**
    * Create a new data group on the server. If the data group exists already, and the groups have already been retrieved by this nSession
    * the nDataGroup will be returned from the local list of data groups. Otherwise this method will send an event to the server.
    *
    * @param dataGroupName        the name of the data group to create
    * @param enableMulticast      should this datagroup support multicast
    * @return the data group matching the specified name
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    * @throws nIllegalArgumentException
    * @see nConflationAttributes
    * @since 6.1
    */

    DLL virtual nDataGroup* createDataGroup(const std::string& dataGroupName, bool enableMulticast);
    /**
    * Deletes the specified data group from the server
    *
    * @param pDataGroupNames array of data group names to be deleted
    * @param numGroup size of data group
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nIllegalArgumentException
    * @throws nUnexpectedResponseException
    * @since 6.0
    */

    DLL void deleteDataGroup(std::string *pDataGroupNames, int numGroup);

    /**
    * Deletes the specified data group from the server
    *
    * @param dataGroupName the name of the data group to delete
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nIllegalArgumentException
    * @throws nUnexpectedResponseException
    * @since 6.0
    */

    DLL virtual void deleteDataGroup(const std::string& dataGroupName);

    /**
    * Deletes the specified data group from the server
    *
    * @param pGroup the data group to delete
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    * @since 6.0
    */

    DLL virtual void deleteDataGroup(nDataGroup *pGroup);

    /**
    * Deletes the specified data group from the server
    *
    * @param pGroups the data groups to delete
    * @param numGroup the size of the data group
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    * @since 6.0
    */

    DLL void deleteDataGroup(nDataGroup **pGroups, int numGroup);

    /**
    * Return the default nDataGroup object, and provide a listener that will receive callbacks when new streams are added or removed
    *
    * @param pListener the instance of the nDataGroupListener that will receive the callbacks to the default group
    * @return the default data group
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    */

    DLL virtual nDataGroup* getDefaultDataGroup(nDataGroupListener *pListener = NULL);

    /**
    * Get all known data groups on the server (excluding the default data group) and register a listener.  The listener will receive callbacks whenever a stream or group
    * is created/deleted or added/removed from a group.
    *
    * @param pListener the instance of the nDataGroupListener that will receive callbacks for all known data groups including the default
    * @return the data group array
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    */
    DLL virtual std::list<nDataGroup*>* getDataGroups(nDataGroupListener *pListener);

    /**
    * Get all known data groups on the server that have the given prefix (excluding the default data group) and register a listener.  The listener will receive callbacks whenever a stream or group
    * is created/deleted or added/removed from a group.
    *
    * @param prefix will only return datagroups that have names with this prefix
    * @param pListener the instance of the nDataGroupListener that will receive callbacks for all known data groups including the default
    * @return the data group array
    * @throws nRequestTimedOutException
    * @throws nSessionPausedException
    * @throws nSessionNotConnectedException
    * @throws nSecurityException
    * @throws nUnexpectedResponseException
    */
    DLL virtual std::list<nDataGroup*>* getDataGroups(std::string prefix="", nDataGroupListener *pListener=NULL);

    /**
    * Get the size of the known data groups list
    *
    * @return the current size of the data groups list
    */
    DLL int getKnownGroupCount();

    void dataGroupUpdate(nStreamStatusUpdate *pUpd);
    /**
     * Finds and returns an array of nFindResult objects that correspond to the results of the find operations on each nChannelAttributes.
     *
     * @param **ppAttr The channel attributes of the channels / queues to be found
     * @param nAttr The length of the returned ppAttr array
     * @return The nFindResult array that represents the result of the find call
     * @throws nUnknownRemoteRealmException  The remote realm responded with an unknown exception
     * @throws nSecurityException            User is not authorised for the function
     * @throws nSessionNotConnectedException Current session is not connected
     * @throws nUnexpectedResponseException  Internal Error has occurred, since we received a response from the server out of sequence
     * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
     * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
     * @throws nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual fSortedList<std::string, nFindResult*>* find(nChannelAttributes **ppAttr, int nAttr);

    /**
    * Subscribe to the channels specified within the nSubscriptionAttributes array
    *
    * @param ppAttributes - the details of each channel subscription
    * @param nAttribute - the returned length of ppAttributes
    * param nAttribute - the number of attributes
    * @return the response from the server will be either an Exception or an nChannel within each subscription attributes object
    * @throws Exception if the server encounters any problem during this operation
    * @throws nIllegalArgumentException if attributes contains a illegal value
    * @see nSubscriptionAttributes
    */
    DLL virtual nSubscriptionAttributes** subscribe(nSubscriptionAttributes **ppAttributes, int nAttribute);

    /**
    * Initialises a session object, opening the physical connection to the
    * server and supplies a nDataStreamListener to receive asynchronous direct events
    *
    * @throws nRealmUnreachableException    if the realm is currently not available
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nSessionAlreadyInitialisedException
    *                                       The session has already been initialised
    * @throws nSecurityException            Insufficient privileges
    * @param pStreamListener - a stream listener to receive asynchronous events
    * @since 6.0
    */

    DLL nDataStream* init(nDataStreamListener *pStreamListener);

    /**
    * Initialises a session object, opening the physical connection to the
    * server and supplies a nDataStreamListener to receive asynchronous direct events
    *
    * @param disconnectIfClusterFails - if the cluster loses quorum, should this nSession become disconnected (true/false)
    * @throws nRealmUnreachableException    if the realm is currently not available
    * @throws nSessionNotConnectedException Current session is not connected
    * @throws nSessionAlreadyInitialisedException
    *                                       The session has already been initialised
    * @throws nSecurityException            Insufficient privileges
    * @param fails - if the cluster loses quorum, should this nSession become disconnected (true/false)
    * @param pStreamListener - a stream listener to receive asynchronous events
    * @since 6.0
	* @deprecated as of 10.7. When in future releases the API is removed the behaviour will be as the flag is set to true,
	* i.e. non-admin client sessions will be disconnected when cluster is not formed.
    */
    UM_DEPRECATED DLL nDataStream* init(bool fails, nDataStreamListener *pStreamListener);

    /**
     * Commit all registered event changes in a single call to the server
     *
     * @param events the registered events that have changed
     * @param replace override the events on the server
     * @throws nSecurityException
     * @throws nSessionPausedException
     * @throws nIllegalArgumentException
     * @throws nSessionNotConnectedException
     * @throws nRequestTimedOutException
     * @throws nUnexpectedResponseException
	 * @throws nPublishPausedException when publishing is paused server side
     */
    DLL void commitRegisteredEventsToDataGroups(std::list<nRegisteredEvent*>& events, bool replace = false);
    DLL virtual void write(nConsumeEvent* evt, nAbstractChannel** destinations, int ndestinations);

    /**
    *    Sends the events to the specified channel / queue
    *
    *   @param evts   the array of events to write to the channel
    *   @param nevents the size of the evts array
    *   @param destination the stream to write to
    */
    DLL virtual void write(nConsumeEvent** evts, int nevents, nAbstractChannel* destination);

    /**
    *    Sends the events to the specified channels / queues
    *
    *   @param evts    the array of events to write to the channels / queues
    *   @param destinations the array of channels / queues to write to
    *   @param ndestinations the size of the destinations array
    */
    DLL virtual void write(nConsumeEvent** evts, int nevents, nAbstractChannel** destinations, int ndestinations);

    /**
    *    Sends the events to the specified channels / queues
    *
    *   @param evts         the array of events to write to the channels / queues
    *   @param nevents the size of the evts array
    *   @param destinations      the array of channels / queues to write to
    *   @param ndestinations the size of the destinations array
    *   @param waitForReply if true then the method will not return until it receives a response from the server
    */
    DLL virtual void write(nConsumeEvent** evts, int nevents, nAbstractChannel** destinations, int ndestinations, bool waitForReply);

    /**
    *    Sends the event to the specified channels / queues
    *
    *   @param evts         the event to write to the channels / queues
    *   @param destinations      the array of channels / queues to write to
    *   @param ndestinations the size of the destinations array
    *   @param waitForReply if true then the method will not return until it receives a response from the server
    */
    DLL virtual void write(nConsumeEvent* evts, nAbstractChannel** destinations, int ndestinations, bool waitForReply);

    /**
    *    Sends the events to the specified channels / queues
    *
    *   @param evts         the array of events to write to the channel / queue
    *   @param nevents the size of the evts array
    *   @param destination      the channel / queue to write to
    *   @param waitForReply if true then the method will not return until it receives a response from the server
    */
    DLL virtual void write(nConsumeEvent** evts, int nevents, nAbstractChannel* destination, bool waitForReply);

    /**
    *    Sends the event to the specified channel / queue
    *
    *   @param evt          the event to write to the channel / queue
    *   @param destination       the channel / queue to write to
    *   @param waitForReply if true then the method will not return until it receives a response from the server
    */
    DLL virtual void write(nConsumeEvent* evt, nAbstractChannel* destination, bool waitForReply);

    /**
    *    Sends each event in the list to its corresponding channel / queue
    *
    *   @param list            key,value list of nConsumeEvent and channel / queue
    *   @param waitForResponse if true then the method will not return until it receives a response from the server
    */
    DLL virtual void write(std::map<nConsumeEvent*, nAbstractChannel*> *list, bool waitForResponse);

    DLL std::list<nAsyncExceptionListener*>& getAsyncListeners();


    /**
    * Sets the maximum client buffer size.
    * 
    * The default value is 1 MB
    *
    * @param size an int specifying the new maximum client buffer size
    * @throws nIllegalArgumentException Illegal parameter, check the message for more information
    */
    DLL static void setMaxBufferSize(long size);

    /**
     * Gets the maximum client buffer size.
     * 
     * The default value is 1 MB
     *
     * @return an int specifying the current maximum client buffer size
     */
    DLL static long getMaxBufferSize();

	/**
	* Dynamically reset the client keep alive interval of a particular session.
	* @param time indicates the time (in milliseconds) of the new keep alive interval.
	*/
	DLL void setClientKeepAlive(long time);
	/**
	* Retrieve the current keep alive interval of a particular session.
	* @return a long indicating an actual time interval (in milliseconds).
	*/
	DLL long getClientKeepAlive();

	/**
	* Sends an event to the server, to see if the server is still responding to requests.
	* The call is synchronous, meaning that the call will wait for a response from the server before returning to the caller.
	* Note that this call is completely exception safe (ie. no exceptions are thrown).
	* @param timeoutMS indicates the amount of time in milliseconds to wait for a response.
	* @param autoClose is optional, and will automatically close the session if the value is true and the value in timeoutMS
	*	has elapsed.  After closure, the session will attempt to automatically reconnect to the server.
	* @return true if the session could contact the server, false otherwise.
	*/
	DLL bool pingServer(long timeoutMS, bool autoClose = false);

  protected:
    nChannel* createChannel(nChannelAttributes *pAttr, ulonglong initialEID, long privMask, const std::vector<nStorePermission>& permissions);
    nQueue* createQueue(nChannelAttributes *pAttr, long privMask, const std::vector<nStorePermission>& permissions);
    static fBaseEventFactory* sFactory;

    DLL virtual void mainClose();
    DLL void registerExtensionCallback(nServerExtensionCallback *callback);
    DLL void sendExtensionData(ulonglong id, unsigned char *data, int len, nEventProperties *props);
    DLL virtual void write(std::map<nConsumeEvent*, nAbstractChannel*> *list, bool waitForResponse, bool isRegisteredEvent);
    DLL nSession(nSessionAttributes *pAttributes);
    DLL virtual nRealm* getRealm(const std::string& name, bool isAdmin);
    DLL virtual bool handleSynchronousEvents(nSynchronous *pEvent);
    DLL virtual bool handleAsynchronousEvents(nEvent *pEvent);

    nSession(nSessionAttributes *pAttributes, nReconnectHandler *pHandler, std::string& username);

    void addToChannelList(nClientChannelList *pClient);
    void addRealm(nRealm *pNewRealm, nSession *pSession, bool update, std::string clName="", std::string rClName="");

	void eraseChannelFromCache(nChannelAttributes *pAttr);
    nChannelImpl* getChannelFromCache(nBaseChannelAttributes *pAttr);
    nEvent* writeEvent(nEvent *pEvent, bool checkDisconnect=true);
    nChannel* constructChannel(nBaseChannelAttributes *pCa);
    nQueue* constructQueue(nBaseChannelAttributes *pCa);
    nClientChannelList* findChannel(ulonglong id);
    nConsumeEvent* nPublishedTonConsumeEvent(nPublished *pEvent);

    fSortedList<longlong, std::string> m_groupMapping;
    Poco::Mutex m_groupMappingLock;

    fSortedList<longlong, nDataGroup*> m_knownDataGroups;
    Poco::Mutex m_knownDataGroupLock;

    bool _isAdmin;
    bool _getMasterRealm;
    std::string currentMaster;

    nDataGroupEventPump* m_pDataGroupPump;
    nDataGroupListener *m_pGroupListener;
    fConnection *m_pConnection;

  private:
    nSession(nSessionAttributes *pAttributes, nReconnectHandler *pHandler);
    nSession(nSession *pSession);

	ulonglong getServerTimeHelper(long timeoutMS);
	void closeWithReconnect();
    void reconnectDataGroups();
    void handleServerReconnectDataGroup(nDataGroupAdmin* admin);
    void updateGroup(nDataGroup* local, nBaseDataGroup* remote);
    longlong getServerTransactionTTL();
    ulonglong getNextTXId();
    void actualInit();
    void createFactory(nSessionAttributes *pAttributes);
    void establishFirstConnection();
    fConnection* establishConnection();
    void doReconnect ();
    void shutdownMulticast();
    void reconnectToServer();
    void requestHandshake(bool sync);
    void setRNameList(std::string list);
    void processEvent(nEvent *pEvent);
    nSession* handleRedirect(nBaseRealm *pRealm);
    nRealm* getRealmFromCache(const std::string& name);
    nEvent* writeEvent(nEvent *pEvent, longlong timeout, bool checkDisconnect=true);

    /**
    * Releases (clears) all events currently waiting for response from server.
    */
    void releaseRequests();

    /**
    * Releases (clears) all events which match the specified predicate.
    * @param predicate Predicate to match each nSynchronous event which is currently waiting for response, all events which match the predicate will be released.
    */
    template<typename EventPredicate>
    void releaseRequests(EventPredicate &predicate);

    void handleTimeOutUpdate(nTimeOutUpdate *pUpdate);
    void handleServerRedirection(std::string rname);
    void _deleteRealm(std::string realm, bool update);
    std::string* checkForNAT(fConnectionDetails *pPhysicalConnection, std::string* pTestRealm, int& nTestRealm, int &nProtocol);
//	void setupMultiplexChannel ();
    nDataGroup* getDataGroup(const std::string& name);
    nDataGroup** getGroupsContaining(nDataGroup *pGroup, int& numGroup);

	void deleteConnection(bool bClose = false);

	void clearLastPublish();

    void checkQueueAttributes(nChannelAttributes *attr);

	void writeDataStreamPublish(nDataStreamPublish* ev);

	bool isEventAllowedOnSessionPause(nEvent* pEvent);
	void handleMasterRedirect(nExceptionEvent *sevent, bool initConnection);


    static long sMaxBufferSize;

    bool m_bDisconnectIfClusterFails;
	volatile bool m_bCanRun;
    bool m_bRetryInit;
    bool m_bIsInitialised;
    bool m_bIsDisconnected;
    bool m_bGotFirstConnection;
	volatile bool m_bIsClosing;
    bool m_bHandshakeSent;
    bool m_bHandshakeRecd;
    bool m_isMemberOfCluster;
    bool enableMulticast;
    bool m_bIsPaused;
    bool m_bEnableMultiplexing;
    bool m_bCloneDictionary;
    bool m_bHasFiredDisconnect;
    
    int m_sessionId;
    int m_delayCounter;

    long m_initialConxnRetryCount;////***********
    long m_lastReconnectTime;

    ulonglong m_serverSessionId;
    
    longlong m_serverTransactionTTL;

    std::string m_realmName;
    std::string m_rnameList;
    std::string m_username;


    nSessionAttributes *m_pAttributes;
    fDriverFactory *m_pFactory;
    nRunLoop *m_pRunLoop;
    fBaseEventFactory *m_pEventFactory;
    fDriver *m_pDriver;


    fConnectionQueueListener *m_pConnectionQueueListener;

    nClientChannelList *m_pLastPublish;

    std::string m_streamId;
    nDataStreamListener *m_pStreamListener;
    nDataGroup *m_pGlobal;
//	fMultiplexManager* m_pMultiplexManager;		// Leave out for now
    nServerExtensionCallback *myExtensionCallback;

    std::vector<nReconnectHandler*> m_reconnectHandlers;
    std::list<nAsyncExceptionListener*> m_asyncListeners;

    std::map<std::string, nChannelImpl*> m_redirList;
    std::map<std::string, nSession*> m_redirSessions;
    std::map<std::string, nBaseRealm*> m_realmsList;
    std::map<longlong,nDataGroupStreamTransitionManager*>* myDataGroupTransistion;
    std::map<short, nMulticastReceiver*>* myMulticastRecievers;
    std::map<longlong, nClientChannelList*> m_channelList;
    std::map<longlong, nRequestResponseContainer*> m_eventVector;

    Poco::Mutex myDataGroupTransistionLock;
    Poco::Mutex myMulticastRecieversLock;

    Poco::Mutex m_channelListMutex;
    Poco::Mutex m_eventVectorMutex;

    Poco::Mutex m_syncMutex;
    Poco::Mutex m_runLoopMutex;
    Poco::Mutex m_nextTXIdMutex;

    Poco::Random m_pRdm;

	friend class nSessionFactory;
    friend class conQueueListener;
    friend class nRunLoop;
    friend class nChannelImpl;
    friend class nTransaction;
    friend class nTransactionAttributes;
    friend class nChannelIterator;
    friend class nDataGroup;
    friend class nDataGroupPumpImpl;
};

}
}
}
}
