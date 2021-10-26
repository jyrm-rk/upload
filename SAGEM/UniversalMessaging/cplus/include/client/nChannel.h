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
#include "nAbstractChannel.h"
#include "nQueue.h"
#include "nRegisteredEvent.h"
#include "nChannelPublishKeys.h"
#include "fObject.h"
#include "nObject.h"
#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nClientChannelList;
class nBaseChannelAttributes;
namespace events {
class nPublished;
class nEvent;
}
}
namespace client {

class nChannelImpl;
class nEventListener;
class nConsumeEvent;
class nChannelIterator;
class nChannelAttributes;
class nChannelConnectionListener;
class nNamedObject;
class nJoinInformation;

using namespace nbase;
using namespace nbase::events;
using namespace com::pcbsys::foundation::fbase;

/**
 * This class is a Nirvana channel, offering the Nirvana channel related services
 */
class nChannel :
    public nAbstractChannel {
  public:
    DLL virtual ~nChannel(void);

    /**
    * Gets the last event id of this channel
    *
    * @return a long specifying the last event id of this channel
    *
    * @throws nSecurityException is thrown if the caller has unsufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nSessionPausedException The session is currently paused
    */
    DLL longlong getLastEID();

    /**
     * Gets the last event id of this channel
     *
     * @return a long specifying the last event id stored on this channel
     *
     * @throws nSecurityException is thrown if the caller has unsufficient permissions
     * @throws nChannelNotFoundException if the channel no longer exists
     * @throws nRequestTimedOutException if the request exceeded the timeout value
     * @throws nSessionNotConnectedException The session is not currently connected to the server
     * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
     * @throws nSessionPausedException The session is currently paused
     */
    DLL longlong getLastStoredEID();

    /**
    * Registers the specified nEventListener as a subscriber to this channel.
    * The subscriber will receive all events contained in this channel.
    *
    * @param *pNel the nEventListener object to be registered as a subscriber
    *
    * @throws nSecurityException is thrown if the caller has unsufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    */
    DLL void addSubscriber(nEventListener *pNel);

    /**
    * Registers the specified nEventListener as a subscriber to this channel.
    * The subscriber will receive all events with event id greater than or equal
    * to the one specified.
    *
    * @param *pNel the nEventListener object to be registered as a subscriber
    * @param eid a long specifying the subscription's start eid
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    * @throws nSessionPausedException The session is currently paused
    */
    DLL void addSubscriber(nEventListener *pNel, longlong eid);

    /**
    * Registers the specified nEventListener as a subscriber to this channel.
    * The subscriber will receive all events with event id greater than or equal
    * to the one specified, apart from the ones restricted by the specified filter.
    *
    * @param *pNel the nEventListener object to be registered as a subscriber
    * @param selector a string specifying a filter to this subscription request
    * @param eid a long specifying the subscription's start eid
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    * @throws nSessionPausedException The session is currently paused
    */
    DLL void addSubscriber(nEventListener *pNel, const std::string& selector, longlong eid = -1);

    /**
    * Registers the specified nEventListener as a named subscriber to this channel.
    * The subscriber will receive all events from the last acknowledged event for the name supplied
    * If the name is new it will start from the END of the channel.
    *
    * @param *pNel the nEventListener object to be registered as a subscriber
    * @param *pName a nNamedObject specifying a name for this subscription
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    * @throws nNameAlreadyBoundException The name is already bound and used by another client
    * @throws nSessionPausedException The session is currently paused
    * @throws nNameDoesNotExistException if the server does not know about the named object
    */
    DLL void addSubscriber(nEventListener *pNel, nNamedObject *pName);

    /**
    * Registers the specified nEventListener as a named subscriber to this channel.
    * The subscriber will receive all events from the last acknowledged event for the name supplied
    * If the name is new it will start from the END of the channel.
    *
    * @param *pNel the nEventListener object to be registered as a subscriber
    * @param *pName an nNamedObject specifying a name for this subscription
    * @param selector a string specifying a filter to this subscription request
    * @param bAutoAck a bool used to control whether the nirvana client will automatically ack events
    * or if the user will ack events later
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    * @throws nNameAlreadyBoundException The name is already bound and used by another client
    * @throws nSessionPausedException The session is currently paused
    * @throws nNameDoesNotExistException if the server does not know about the named object
    */
    DLL void addSubscriber(nEventListener *pNel, nNamedObject *pName, const std::string& selector, bool bAutoAck);

    /**
    * Unregisters the specified nEventListener as a subscriber from this channel.
    * The subscriber will not receive any more events.
    *
    * @param *pNel the nEventListener object to be registered as a subscriber
    *
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL void removeSubscriber(nEventListener *pNel);

    /**
    * Unregisters the specified nEventListener as a subscriber from this channel.
    * The subscriber will not receive any more events.
    *
    * @param *pNel the nEventListener object to be registered as a subscriber
    * @param waitForResponse if true the call will block waiting for the server to complete the request
    *
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL void removeSubscriber(nEventListener *pNel, bool waitForResponse);

    /**
     * Pause the subscription of the specified nEventListener. This means that no new events will be received
     * from the server until the subscription is resumed. All events that have already been received will be
     * processed normally.
     *
     * @param eventListener the nEventListener object registered as a subscriber
     *
     * @throws nSessionPausedException The session is currently paused, please resume
     * @throws nSessionNotConnectedException The session is not currently connected to the server
     * @throws nRequestTimedOutException if the request exceeded the timeout value
     * @throws nUnexpectedResponseException Received a response from the server which we can not deal with, see
     *     the message for further information
     */
    DLL void pauseSubscriber(nEventListener *pNel);

    /**
     * Resumes the subscription of the specified nEventListener. See nChannel#pauseSubscriber.
     *
     * @param eventListener the nEventListener object registered as a subscriber
     *
     * @throws nSessionPausedException The session is currently paused, please resume
     * @throws nSessionNotConnectedException The session is not currently connected to the server
     * @throws nRequestTimedOutException if the request exceeded the timeout value
     * @throws nUnexpectedResponseException Received a response from the server which we can not deal with, see
     *     the message for further information
     */
    DLL void resumeSubscriber(nEventListener *pNel);

    /**
    * Returns true if the subscription of the specified nEventListener object is paused.
    *
    * @param eventListener the nEventListener object registered as a subscriber
    * @throws nIllegalArgumentException if the provided nEventListener is null or does not belong to the channel
    */
    DLL bool isSubscriberPaused(nEventListener *pNel);

    /**
    * Publishes the specified nConsumeEvent to this channel
    *
    * @param *pEvent the nConsumeEvent object to be published to this channel
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused
    */
    DLL void publish(nConsumeEvent *pEvent);

    /**
    * Create a default channel iterator starting at the eid specified in the channel with
    * the events which match the selector being returned
    *
    * @param selector Used to specify a sub set of the current channel events
    * @param startEID The event to start iterating the channel from
    *
    * @return nChannelIterator for the current channel
    *
    */
    DLL nChannelIterator* createIterator(const std::string& selector, longlong startEID);

    /**
    * Create a default channel iterator starting at the eid specified in the channel with
    * the events which match the selector being returned
    *
    * @param selector Used to specify a sub set of the current channel events
    * @param *pName Named Object reference to use for this iterator
    * @return nChannelIterator for the current channel
    */
    DLL nChannelIterator* createIterator(nNamedObject *pName, const std::string& selector);

    /**
    * Create a default channel iterator starting at the eid specified in the channel with
    * the events which match the selector being returned
    *
    * @param *pName Named Object reference to use for this iterator
    * @return nChannelIterator for the current channel
    *
    */
    DLL nChannelIterator* createIterator(nNamedObject *pName);

    /**
    * Create a default channel iterator starting at the EID specified
    *
    * @param startEID The event to start iterating the channel from
    * @return nChannelIterator for the current channel
    */
    DLL nChannelIterator* createIterator(longlong startEID);

    /**
    * Create a default channel iterator starting at the beginning of the channel with
    * the events which match the selector being returned
    *
    * @param selector Used to specify a sub set of the current channel events
    *
    * @return nChannelIterator for the current channel
    *
    */
    DLL nChannelIterator* createIterator(const std::string& selector);

    /**
    * Create a default channel iterator starting at the beginning of the channel
    *
    * @return nChannelIterator for the current channel
    */
    DLL nChannelIterator* createIterator();

    /**
    * Gets the channels local attributes
    *
    * @return The associated nChannelAttributes object specifying the channel attributes
    */
    DLL nChannelAttributes* getChannelAttributes();

    /**
    * Adds a nChannelConnectionListener to this channel so that when new connections are made to this channel the
    * listener is notified
    *
    * @param *pListener to add
    *
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits, or has already been set.
    * @throws nSessionPausedException The session is currently paused, please resume
    */
    DLL void addConnectionListener(nChannelConnectionListener *pListener);

    /**
    * Adds a nChannelConnectionListener to this channel so that when new connections are made to this channel the
    * listener is notified
    *
    * @param *pListener to add
    * @param isSync the call is synchronous
    *
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits, or has already been set.
    * @throws nSessionPausedException The session is currently paused, please resume
    */
    DLL void addConnectionListener(nChannelConnectionListener *pListener, bool isSync);

    /**
    * Gets the name of this channel
    *
    * @return a string specifying the name of this channel
    */
    DLL std::string getName();

    /**
    * Removes the connection listener to this channel
    *
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL void removeConnectionListener();

    /**
    * Removes the connection listener to this channel
    *
    * @param *pListener remove the listener
    *
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nSessionPausedException The session is currently paused, please resume
    */
    DLL void removeConnectionListener(nChannelConnectionListener *pListener);

    /**
    * Creates a named object on the channel with the given name and depending on
    * the persistent flag informs the server to store the name and value to disk or not
    *
    * @param name to create
    * @param startEID event EID to start the named object from
    * @param persistent flag to indicate to the server where to store it
    * @param clusterWide flag to indicate if this named object is valid in the entire cluster
    * @return the nNamedObject created
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nNameAlreadyBoundException If the name is already in use
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    * @deprecated The persistent and clusterWide flags are deprecated since 10.5. These flags will be removed. 
    * Persistence of the durable will be defined by the persistence support of the parent channel. If the parent channel supports persistent events,
    * its durables will always be created as persistent. The durable will be treated as cluster-wide if its parent channel is a cluster-wide one.
    */
    UM_DEPRECATED DLL nNamedObject* createNamedObject(const std::string& name, longlong startEID, bool persistent, bool clusterWide);
    /**
    * Creates a named object on the channel with the given name and depending on
    * the persistent flag informs the server to store the name and value to disk or not
    *
    * @param name to create
    * @param persistent flag to indicate to the server where to store it
    * @param clusterWide flag to indicate if this named object is valid in the entire cluster
    * @return the nNamedObject created
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nNameAlreadyBoundException If the name is already in use
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    * @deprecated The persistent and clusterWide flags are deprecated since 10.5. These flags will be removed. 
    * Persistence of the durable will be defined by the persistence support of the parent channel. If the parent channel supports persistent events,
    * its durables will always be created as persistent. The durable will be treated as cluster-wide if its parent channel is a cluster-wide one.
    */
    UM_DEPRECATED DLL nNamedObject* createNamedObject(const std::string& name, bool persistent, bool clusterWide);

    /**
    * Creates a named object on the channel with the given name and depending on
    * the persistent flag informs the server to store the name and value to disk or not
    *
    * @param name to create
    * @param persistent flag to indicate to the server where to store it
    * @return the nNamedObject created
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nNameAlreadyBoundException If the name is already in use
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    * @deprecated This persistent flag is deprecated since 10.5. The parameter will be removed. Persistence of the durable
    * will be defined by the persistence support of the parent channel. If the parent channel supports persistent events,
    * its durables will always be created as persistent.
    */
    UM_DEPRECATED DLL nNamedObject* createNamedObject(const std::string& name, bool persistent);

    /**
    * Creates a named object on the channel with the given name and depending on
    * the persistent flag informs the server to store the name and value to disk or not
    *
    * @param name to create
    * @param startEID event EID to start the named object from
    * @param persistent flag to indicate to the server where to store it
    * @return the nNamedObject created
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nNameAlreadyBoundException If the name is already in use
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    * @deprecated This persistent flag is deprecated since 10.5. The parameter will be removed. Persistence of the durable
    * will be defined by the persistence support of the parent channel. If the parent channel supports persistent events,
    * its durables will always be created as persistent.
    */
    UM_DEPRECATED DLL nNamedObject* createNamedObject(const std::string& name, longlong startEID, bool persistent);

    /**
    * Creates a named object on the channel with the given name
    *
    * @param name to create
    * @param startEID event EID to start the named object from
    * @return the nNamedObject created
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nNameAlreadyBoundException If the name is already in use
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL nNamedObject* createNamedObject(const std::string& name, longlong startEID);

    /**
    * Creates a named object on the channel with the given name
    *
    * @param name to create
    * @return the nNamedObject created
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nNameAlreadyBoundException If the name is already in use
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL nNamedObject* createNamedObject(const std::string& name);

    /**
    * Deletes a join between this channel and the queue referenced in the destination parameter
    *
    * @param *pDestination This is an nQueue object referencing the destination queue
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the queue no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void deleteJoin(nQueue *pDestination);

    /**
    * Deletes a join between this channel and the channel referenced in the destination parameter
    *
    * @param *pDestination This is an nChannel object referencing the destination channel
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void deleteJoin(nChannel *pDestination);

    /**
    * Removes all references for this name on the realm Server
    *
    * @param name the name to be removed from the server
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nNameDoesNotExistException The name specified does not exist on the server
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL void delNamedObject(const std::string& name);

    /**
    * Removes all references for this name on the realm Server
    *
    * @param *pName the name to be removed from the server
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nNameDoesNotExistException The name specified does not exist on the server
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL void delNamedObject(nNamedObject *pName);

    /**
    * Returns an instance of the nNamedObject referenced by the parameter
    *
    * @param name of the nNamedObject
    * @return nNamedObject
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nNameDoesNotExistException The name specified does not exist on the server
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL nNamedObject* getNamedObject(const std::string& name);

    /**
    * Returns an array of all known nNamedObjects registered with this channel
    *
    * @param numObject number of nNamedObjects returned
    * @return nNamedObject[] named objects
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL nNamedObject** getNamedObjects(int& numObject);

    /**
    * Returns an array of nJoinInformation objects which describe the links this channel
    * has configured for it.
    * @param numJoin number of nJoinInformation objects
    * @return array of nJoinInformation objects
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL nJoinInformation** getJoinInformation(int& numJoin);

    /**
    * Gets the type of this channel
    * <p>
    * Currently supported types are:
    <p><KBD>
    *    nChanneAttributes.MIXED_TYPE <br>
    *    nChanneAttributes.PERSISTENT_TYPE <br>
    *    nChanneAttributes.RELIABLE_TYPE <br>
    * </KBD>
    * <p>
    * @return an int specifying the channel's type, which will be equal to one of :
    * <p><KBD>
    *    nChanneAttributes.MIXED_TYPE <br>
    *    nChanneAttributes.PERSISTENT_TYPE <br>
    *    nChanneAttributes.RELIABLE_TYPE <br>
    * </KBD>
    * <p>
    * @see nChannelAttributes
    */

    DLL int getType();

    /**
    * Sets a server based link between this channel and the queue
    * defined within the provided nQueue. Additional parameters specify
    * whether the event is routable or not, the maximum number of hops the event
    * can pass through and the filter applied to the join (link).
    *
    * @param *pDest a nQueue object defining the queue to be joined (linked)
    * to this channel
    * @param isRouted a  bool flag specifying whether the event will be routed or not
    * @param hopCount an int specifying the maximum number of hops the event can pass through
    * @param selector A string defining a filter that will be applied in the join (link)
    * from the source channel
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void joinChannel(nQueue *pDest, bool isRouted, int hopCount, const std::string& selector);

    /**
    * Sets a server based link between this channel and the queue
    * defined within the provided nQueue. The link has a filter applied
    * to it, defined by the provided selector string
    *
    * @param *pDest a nQueue object defining the queue to be joined (linked)
    * to this channel
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void joinChannel(nQueue *pDest);

    /**
    * Sets a server based link between this channel and the queue
    * defined by the *pDest parameter. Additional parameter specifies
    * the filter applied to the join (link).
    *
    * @param *pDest a nQueue object defining the queue to be joined (linked)
    * to this channel
    * @param selector A string defining a filter that will be applied in the join (link)
    * from the source channel
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void joinChannel(nQueue *pDest, const std::string& selector);

    /**
    * Sets a server based link between this channel and the channel
    * defined within the provided nChannel. Additional parameters specify
    * whether the event is routable or not, the maximum number of hops the event
    * can pass through and the filter applied to the join (link).
    *
    * @param *pDest a nChannel object defining the channel to be joined (linked)
    * to this channel
    * @param isRouted a  bool flag specifying whether the event will be routed or not
    * @param hopCount an int specifying the maximum number of hops the event can pass through
    * @param selector A string defining a filter that will be applied in the join (link)
    * of these 2 channels
    * @param allowPurge if allow purge is true then when the source channel is purged events source from it will also be purged
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void joinChannel(nChannel *pDest, bool isRouted, int hopCount, const std::string& selector, bool allowPurge);

    /**
    * Sets a server based link between this channel and the channel
    * defined within the provided nChannel. Additional parameters specify
    * whether the event is routable or not, the maximum number of hops the event
    * can pass through and the filter applied to the join (link).
    *
    * @param *pDest a nChannel object defining the channel to be joined (linked)
    * to this channel
    * @param isRouted a  bool flag specifying whether the event will be routed or not
    * @param hopCount an int specifying the maximum number of hops the event can pass through
    * @param selector A string defining a filter that will be applied in the join (link)
    * of these 2 channels
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void joinChannel(nChannel *pDest, bool isRouted, int hopCount, const std::string& selector);

    /**
    * Sets a server based link between this channel and the channel
    * defined within the provided nChannel.
    *
    * @param *pDest a nChannel object defining the channel to be joined (linked)
    * to this channel
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void joinChannel(nChannel *pDest);

    /**
    * Sets a server based link between this channel and the channel
    * defined within the provided nChannel. The link has a filter applied
    * to it, defined by the provided selector string
    *
    * @param *pDest a nChannel object defining the channel to be joined (linked)
    * to this channel
    * @param selector A string defining a filter that will be applied in the join (link)
    * of these 2 channels
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void joinChannel(nChannel *pDest, const std::string& selector);

    /**
    * Purges a single event from this channel
    *
    * @param eidval a long specifying the event id of the event to be purged
    * from the channel
    * @param purgeJoins a bool specifying if the event will be removed from all subsequent joins
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void purgeEvent(longlong eidval, bool purgeJoins = false);

    /**
    * Purges a single event from this channel and does not wait for the response from the server
    *
    * @param eidval a long specifying the event id of the event to be purged
    * from the channel
    * @param purgeJoins a bool specifying if the event will be removed from all subsequent joins
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void purgeEventAsync(longlong eidval, bool purgeJoins = false);

    /**
    * Purges a range of events from this channel and does not wait for the response from the server
    *
    * @param startEID a long specifying the start event id of the range of events to be purged from the channel
    * @param endEID a long specifying the end event id of the range of events to be purged from the channel
    * @param selector A messages selector which will be used to filter out only the events which match this criteria
	* @param purgeJoins a bool specifying if the event will be removed from all subsequent joins
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused
    */

	DLL void purgeEventsAsync(longlong startEID, longlong endEID, const std::string& selector = "", bool purgeJoins = false);

    /**
    * Purges a range of events from this channel
    *
    * @param startEID a long specifying the start event id of the range of events
    * to be purged from the channel
    * @param endEID a long specifying the end event id of the range of events
    * to be purged from the channel
    * @param selector A messages selector which will be used to filter out only
    * the events which match this criteria
	* @param purgeJoins a bool specifying if the event will be removed from all subsequent joins
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSessionPausedException The session is currently paused
    */

	DLL void purgeEvents(longlong startEID, longlong endEID, const std::string& selector = "", bool purgeJoins = false);

    /**
    * Determines whether the underlying channel is currently being subscribed to
    *
    * @return true if the channel object is currently subscribed to
    */

    DLL bool isSubscribed();

    /**
    * Removes the current subscriber and registers the specified nEventListener as a named subscriber to this channel.
    * The subscriber will receive all events from the last acknowledged event for the name supplied
    * If the name is new it will start from the END of the channel.
    *
    * @param *pName a named object for this subscription
    * @param selector a string specifying a filter to this subscription request
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    * @throws nNameAlreadyBoundException The name is already bound and used by another client
    * @throws nSessionPausedException The session is currently paused
    * @throws nNameDoesNotExistException if the server does not know about the named object
    */

    DLL void reSubscribe(nNamedObject *pName, const std::string& selector);

    /**
    * Removes the current subscriber and re-registers the nEventListener as a subscriber to this channel.
    * The subscriber will receive all events with event id greater than or equal
    * to the one specified, apart from the ones restricted by the specified filter.
    *
    * @param selector a string specifying a filter to this subscription request
    * @param eid a long specifying the subscription's start eid
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void reSubscribe(const std::string& selector, longlong eid = -1);

    /**
    * Removes the current subscriber and registers the specified nEventListener as a subscriber to this channel.
    * The subscriber will receive all events with event id greater than or equal
    * to the one specified
    *
    * @param eid a long specifying the subscription's start eid
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nSelectorParserException The selector has syntax errors
    * @throws nChannelAlreadySubscribedException A subscriber is already registered with this channel on this session
    * @throws nSessionPausedException The session is currently paused
    */

    DLL void reSubscribe(longlong eid);

    /**
    * Unbinds the named object from the current connection
    *
    * @param name the name to be unbound
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nNameDoesNotExistException The name specified does not exist on the server
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL void unbindNamedObject(const std::string& name);

    /**
    * Unbinds the named object from the current connection
    *
    * @param *pName the named object to be unbound
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nNameDoesNotExistException The name specified does not exist on the server
    * @throws nSessionPausedException The session is currently paused, please resume
    */

    DLL void unbindNamedObject(nNamedObject *pName);

    /**
    * Sets a server based link between this channel and the queue
    * defined within the provided nQueue. Events will NOT be checked for duplicates since this is an archive join, any
    * events that are published to the source will appear in the destination queue. This may result in duplicate events in the
    * queue if the queue has multiple sources. This is by design.
    *
    * @param dest a nQueue object defining the queue to be joined (linked)
    * to this channel
    *
    * @throws nSecurityException is thrown if the caller has insufficient permissions
    * @throws nChannelNotFoundException if the channel no longer exists
    * @throws nRequestTimedOutException if the request exceeded the timeout value
    * @throws nSessionNotConnectedException The session is not currently connected to the server
    * @throws nUnexpectedResponseException Received a response from the server for which we can not deal with, see the message for further information
    * @throws nIllegalArgumentException Passed am illegal argument. This means the value passed is outside expected limits
    * @throws nDuplicateJoinException The join already exists on the server
    * @throws nRealmNotFoundException The remote realm could not be found
    * @throws nSessionPausedException The session is currently paused
    */

    void joinChannelToArchive(nQueue *pDest, const std::string& selector);

    /**
     * Creates a new nRegisteredEvent bound to this channel using the keyValue as its unique id.
     *
     * @param keyValue Unique Id to use for the nRegisteredEvent
     * @param isTransactional Indicates that all commits on the nRegisteredEvent should use transactional symantics
     * @return nRegisteredEvent
     * @throws nIllegalArgumentException if unable to create the nRegisteredEvent object
     */
    DLL nRegisteredEvent* createRegisteredEvent(nObject *keyValue, bool isTransactional = false);

  protected:
    DLL nRegisteredEvent* createRegisteredEvent(fObject* keyValue, bool isTransactional = false);
    nChannel(nChannelImpl *pChannel, bool bIgnored = false);
    nClientChannelList* getChannelList();
    nBaseChannelAttributes* getAttributes();
    virtual nChannelAttributes* getClientChannelAttributes();
    nEvent* writeEvent(nEvent *pEvt);
    void setupSubscription(nEventListener *pListener);

  private:
    void addSub(nEventListener *pNel, const std::string& selector, longlong eid);
    void checkListener(nEventListener *pNel);

    friend class nSession;
    friend class FindAndSubscribeCallback;

};

}
}
}
}
