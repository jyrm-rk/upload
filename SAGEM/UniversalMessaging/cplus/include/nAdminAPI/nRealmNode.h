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
#include "nContainer.h"
#include "nRemovable.h"
#include "fSortedList.h"
#include "Poco/Mutex.h"
#include "Poco/SynchronizedObject.h"
#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclGroup;
class fPrincipal;
}
namespace fbase {
class fEventDictionary;
}
}
namespace nirvana {
namespace client {
class nSessionAttributes;
class nRealm;
class nSession;
class nJoinInformation;
class nChannelAttributes;
class nChannel;
class nQueue;
class nEventProperties;
namespace p2p {
class nServiceFactory;
}
}
namespace nbase {
class nSecureRealm;
}
namespace nAdmin {
class nAdminSession;
class nStatusChannel;
}
namespace nAdminAPI {

class nNode;
class nDataGroupNode;
class nPkgReconnectHandler;
class nPkgListenerMapper;
class nPkgDataGroupListener;
class nPkgConfigListener;
class nPkgCloseListener;
class nPkgAuditListener;
class nPkgLogListener;
class nInterfaceManager;
class nConfigGroup;
class nClusterNode;
class nPkgLeafNodeIndex;
class nPkgServiceNodeIndex;
class nLinkNode;
class nLeafNode;
class nACL;
class nPkgGetJoins;
class nACLEntry;
class nConnectionDetails;
class nPkgIncompleteJoinQueue;
class nClusterMemberConfiguration;
class nAPIConnectionListener;
class nThreadPool;
class nLogListener;
class nAPIConnectionListener;
class nAuditListener;
class nThreadEntry;
class nServiceNode;
class nDataGroupsContainer;
class nMulticastManager;
class nSecurityGroupManager;
class nSecurityGroup;
class nZoneManager;
class nRemoteInterestManager;

using namespace com::pcbsys::nirvana::client;
using namespace com::pcbsys::nirvana::client::p2p;
using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::nirvana::nAdmin;
using namespace com::pcbsys::foundation::collections;


/**
 * This class represents a Realm within the Nirvana namespace. This object allows the user to access the current
 * status of the RealmServer, the current configuration parameters, change the ACL entries for the realm and access
 * to the nodes that this RealmServer manages. It extents nContainer which is a Observable via nNode, if any status
 * parameters change then the observer is notified via the notify method.
 * <p/>
 * This class also allows you to monitor connections to the realm by implementing a nConnectionListener and calling
 * addConnectionListener with the object. Then when connections are added or deleted the callbacks will be executed
 * with the details of the connections.
 *
 * @see nContainer
 * @see nNode
 */
class nRealmNode :
    public nContainer, public nRemovable {
  public:
    nRealmNode(void);
    /**
     * Constructs a link with the realm server and builds up the realm servers namespace
     * which can be retrieved using the getNameSpace() function
     *
     * @param *pAttr    nSessionAttributes representing the realm you wish to communicate with
     * @param username Username to use to login to the server
     * @throws nBaseAdminException If the user is not authorised for admin functions
     */
    DLL nRealmNode(nSessionAttributes *pAttr, const std::string& username="");

    /**
     * Constructs a link with the realm server and builds up the realm servers namespace
     * which can be retrieved using the getNameSpace() function
     *
     * @param *pAttr    nSessionAttributes representing the realm you wish to communicate with
     * @param *pParent the parent nNode of this Node
     * @throws nBaseAdminException If the user is not authorised for admin functions
     */
    DLL nRealmNode(nSessionAttributes *pAttr, nNode *pParent);

    virtual ~nRealmNode(void);

    /**
     * This method returns true if the RealmNode is removable
     *
     * @return bool if the RealmNode is removable
     */
    DLL virtual bool IsRemovable();

    /**
     * This method returns true if the connection to the remote realm is still valid
     *
     * @return bool current state
     */
    DLL virtual bool isConnected();

    /**
     * Add a closeListener for this nRealmNode
     *
     * @param nPkgCloseListener the close listener to attach to this RealmNode
     */
    DLL virtual void addCloseListener(nPkgCloseListener *pListener);

    /**
     * Remove a closeListener for this nRealmNode
     *
     * @param nPkgCloseListener the close listener to remove from this RealmNode
     */
    DLL virtual void delCloseListener(nPkgCloseListener *pListener);
    /**
     * Returns the type of this object, for internal use only
     * @return the type of the object
     */
    virtual int getType();

    /**
     * Returns an fSortedList containing nConfigGroup objects and their names
     *
     * @return fSortedList of name nConfigGroup pairs
     */
    DLL virtual fSortedList<std::string, nConfigGroup*>& getConfigGroups();

    /**
     * Finds a configuration group by the name specified by the String argument
     *
     * @param groupName Name of the config group to find
     * @return nConfigGroup object corresponding to the name or null if not found
     */
    DLL virtual nConfigGroup* findConfigGroup(const std::string& groupName);
    /**
    * Return the cluster node if one exists, i.e. if this realm is part of a cluster
    *
    * @return the cluster node for this realm, otherwise null
    */
    DLL virtual nClusterNode* getCluster();

    /**
     * Returns the nRealm object for this nRealmNode
     *
     * @return The com.pcbsys.nirvana.client.nRealm object
     * @see com.pcbsys.nirvana.client.nRealm
     */
    DLL virtual nRealm* getRealm();

    /**
     * This method enables the removal of the object from the namespace, in this case an nRealmNode from
     * the namespace.
     * If you specify true, all child nodes, including channels, queues and services
     * will also be removed from the realm before removing it from its parent
     *
     * @param removeChildren a bool specifying whether siblings should be removed too
     * @throws nUnsupportedRemoveException thrown if remove is not supported (e.g. on the namespace root Realm)
     * @throws nNodeException              is thrown if an error occurs in the remove operation
     * @see nLeafNode
     * @see nLinkNode
     */
    DLL virtual void remove(bool removeChildren);

    /**
     * Returns the nSession object for this nRealmNode
     *
     * @return The com.pcbsys.nirvana.client.nSession object
     * @see com.pcbsys.nirvana.client.nSession
     */
    DLL virtual nSession* getSession();

    /**
     * Method to return a list of nRealmNode*
     *
     * @return List of pointer to all realms known by this realm
     */
    DLL virtual std::list<nRealmNode*>* getRealmList();

    /**
     * Returns the Realms Interface Manager
     *
     * @return The com.pcbsys.nirvana.nAdminAPI.nInterfaceManager object
     * @see com.pcbsys.nirvana.nAdminAPI.nInterfaceManager
     */
    DLL virtual nInterfaceManager* getInterfaceManager();

    /**
     * Retrieves the current realms ACL so that the user can add/remove/modify the entries within.
     * This nACL contains nRealmACLEntry objects.
     *
     * @return nACL containing nRealmACLEntry objects
     * @throws nBaseAdminException if the user is not permitted to access these lists, check the message for more information
     * @see nRealmACLEntry
     */
    DLL virtual nACL* getACLs();

    /**
     * Given a name of the form /container1/container2/name this function will try to locate the name object locally and
     * return it, or null if that object can not be found.
     * This method will not wait for the server to update our local state so if a node is created in one session and this
     * method is called immediately after in another session, the local state may not be up to date and therefore the
     * node may not be found.  Optionally you can call findNode(name,true) to force the method to wait for a maximum of
     * 5 seconds for the local state to update.
     *
     * @param name the name of the node to locate as a String
     * @return a nNode which could be a nRealmNode, nLeafNode or a nContainer
     * @exception nAdminIllegalArgumentException thrown if null is passed as the nNode
     * @see nRealmNode
     * @see nLeafNode
     * @see nContainer
     */
    DLL virtual nNode* findNode(const std::string& name);

    /**
     * Given a name of the form /container/container/name this function will locate the name object and
     * return it, or null if that object can not be found.
     *
     * @param name the name of the node to locate as a String
     * @param flag bool flag indicating if we wait for the server to update our state or not
     * @return a nNode which could be a nRealmNode, nLeafNode or a nContainer
     * @exception nAdminIllegalArgumentException thrown if null is passed as the nNode
     * @see nRealmNode
     * @see nLeafNode
     * @see nContainer
     */
    DLL nNode* findNode(const std::string& name, bool flag);

    /**
     * Given a name of the form /container/container/name this function will locate the nNode object and
     * return it, or null if that can not be found. This function applies to the part of the namespace
     * relative to the current node. Currently wildcards are NOT supported.
     *
     * @param pNode the nNode to be located
     * @return a nNode which could be a nRealmNode, nLeafNode or a nContainer
     * @exception nAdminIllegalArgumentException thrown if null is passed as the nNode
     * @see nRealmNode
     * @see nLeafNode
     * @see nContainer
     */
    DLL virtual nNode* findNode(nNode *pNode) {
        return nContainer::findNode(pNode);
    };

    /**
     * Given a name of the form /container/container/name this function will locate the name object and
     * return it, or null if that can not be found. The searchChildren flag specifies whether the search
     * should be performed on the current container only or children containers too respectively.
     * This function applies to the part of the namespace  relative to the current node.
     * Currently wildcards are NOT supported.
     *
     * @param pNode           the nNode to be located
     * @param searchChildren specifies whether to traverse lower levels of the tree or not
     * @return a nNode which could be a nRealmNode, nLeafNode or a nContainer
     * @exception nAdminIllegalArgumentException thrown if null is passed as the nNode
     * @see nRealmNode
     * @see nLeafNode
     * @see nContainer
     */
    DLL virtual nNode* findNode(nNode *pNode, bool searchChildren) {
        return nContainer::findNode(pNode);
    };

    /**
     * Creates a new channel on the realm this session is connected.
     * <p/>
     * If the channel attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the channel will be created on
     * that realm.
     *
     * @param *pAttr         The channel attributes object containing the parameters for
     *                     the new channel to be created @ param initialEID The channel
     *                     will be created with the first eid being set to this value by
     *                     default it is set to 0 but the user can set it to any
     *                     positive value
     * @param initialEID The value to start the event id at
     * @param *pInitialACL   The initial ACLs to apply to the channel at creation time
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
    DLL nLeafNode* createChannel(nChannelAttributes *pAttr, longlong initialEID, nACL *pInitialACL);

    /**
     * Retrieves the current realms ACL so that the user can add/remove/modify the entries within.
    *  This nACL contains nRealmACLEntry objects.
    *
    *  @return nACL containing nRealmACLEntry obejcts
    *  @throw nBaseAdminException if the user is not permitted to access these lists, check the message for more information 
    *  @see nRealmACLEntry
    */
    DLL std::list<fAclGroup*>* getACLGroups();

    /**
     * Creates a new queue on the realm this session is connected.
     * <p/>
     * If the queue attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the queue will be created on
     * that realm.
     *
     * @param *pAttr       The queue attributes object containing the parameters for the new queue to be created
     * @param *pInitialACL The initial ACLs to apply to the queue at creation time
     * @return an nLeafNode object representing the newly created nirvana queue
     * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @throws nSecurityException             User is not authorised for the function
     * @throws nChannelAlreadyExistsException The channel already exists
     * @throws nSessionNotConnectedException  Current session is not connected
     * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
     * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
     * @throws nSessionPausedException       The session is currently paused, please resume
     */
    DLL nLeafNode* createQueue(nChannelAttributes *pAttr, nACL *pInitialACL);
    /**
     * Disconnects this realm node and closes it's session
     */
    DLL virtual void close();

    /**
     * Adds a specific acl entry to the realm acl
     *
     * @param *pEntry An nACL entry containing the subject and permissions to add to the realm acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void addRealmACLEntries(nACL *pEntry);

    /**
     * Adds a specific acl entry to the realm acl
     *
     * @param *pEntry An nACL entry containing the subject and permissions to add to the realm acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void addRealmACLEntry(nACLEntry *pEntry);

    /**
     * modifies a specific acl entry's permissions in the realm acl.
     *
     * @param  *pEntry An nACL entry containing the subject and permissions to modify in the realm node
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void modRealmACLEntries(nACL *pEntry);

    /**
     * modifies a specific acl entry's permissions in the realm acl.
     *
     * @param *pEntry An nACL entry containing the subject and permissions to modify in the realm node
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void modRealmACLEntry(nACLEntry *pEntry);

    /**
     * removes a specific acl entry from the realm acl.
     *
     * @param *pEntry An nACL entry containing the subject and permissions to remove from the realm acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void removeRealmACLEntries(nACL *pEntry);

    /**
     * removes a specific acl entry from the realm acl.
     *
     * @param *pEntry An nACL entry containing the subject and permissions to remove from the realm acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void removeRealmACLEntry(nACLEntry *pEntry);

    /**
     * This function returns true if the user is authorised for administration functions on the
     * remote realm. If the user is not authorised then this will return false and any functions
     * performed against the realm will result in a nSecurityException
     *
     * @return boolean True if the user is authorised
     */
    DLL virtual bool isAuthorised();

    /**
     * This method will block the calling thread until all of the namespace has been resolved. This
     * could take some time depending on the number of realms within the namespace.
     *
     * @param timeout milliseconds to wait for the namespace to be discovered
     * @throws Exception if unable to complete the namespace within the time specified
     */
    DLL virtual void waitForEntireNameSpace(long timeout = -1);

    /**
    * This method will block the calling thread until the namespace discovery is complete for this node or the
    * supplied timeout, in milliseconds, is reached. If the discovery is already complete the method will
    * return immediately.
    *
    * @param timeout milliseconds to wait for the namespace to be discovered
    * @throws Exception If the name space is not completed with in the time specified
    */
    DLL virtual void waitForNameSpace(long timeout = -1);


    /**
     * This method creates an ACL entry
     *
     * @param subject the subject to create the ACL for
     * @param *pBs the BitArray representing the ACL settings to use.
     * @throws Exception If the name space is not completed with in the time specified
     */
    DLL virtual nACLEntry* createACLEntry(const std::string& subject, BitArray *pBs);

	/**
	* This method creates an ACL entry
	*
	* @param grp the security group to create the ACL for
	* @param *pBs the BitArray representing the ACL settings to use.
	* @throws Exception If the name space is not completed with in the time specified
	*/
	DLL virtual nACLEntry* createACLEntry(nSecurityGroup* grp, BitArray* bs);

    DLL static nACLEntry* createACLEntryStatic(nSecurityGroup* grp, BitArray* bs);  //this is not public in dotnet

    DLL static nACLEntry* createACLEntry(fPrincipal* principle, BitArray* bs); // this is not public in dotnet

    /**
     * Registers the listener object with the realm so that whenever a connection is made or lost with the realm
     * the listener is notified of the change in state of the realm. Currently only one listener per session is
     * supported.
     *
     * @param *pListener The instance of the nConnectionListener to be called when connections are made or disconnected
     * @throws nBaseAdminException if the user is not permitted to access these lists, check the message for further information
     * @see nConnectionListener
     */
    DLL virtual void addConnectionListener(nAPIConnectionListener *pListener);

    /**
     * This method returns true when the namespace discovery process is complete. Since the process
     * of walking the entire namespace is asynchronous this method is useful to find out if the namespace
     * is complete for this Realm. If this Realm contains other Realms then you need to call this function
     * on subsequent Realms to see if the namespace is complete for them.
     * <p/>
     * Alternative, you could add a listener to this object and you will be notified when new nRealmNodes
     * are added to this object.
     *
     * @return boolean if the name space has been completed
     */
    DLL virtual bool isNamespaceComplete();

    /**
     * Returns the total number of events that this realm has sent to clients from the time it started
     *
     * @return Number if events sent to clients
     */
    DLL virtual longlong getTotalSubscribed();

    /**
     * Returns the total number of events published on this realm from the time it has started
     *
     * @return lone event count
     */
    DLL virtual longlong getTotalPublished();

	/**
	 * Returns whether server publishes are currently paused
	 *
	 * @return boolean if server publishing is paused
	 */
	DLL virtual bool isServerPausedPublishing();

    /**
     * Return a list<nThreadPool*>* that represent the different thread pools deployed within the realm.
     *
     * @return Vector of nThreadPool objects
     * @since 4.0
     */
    DLL virtual std::list<nThreadPool*>* getThreadPoolDetails();

    /**
    * Return the total number of GCs that the JVM has performed since the realm has started
    * @return GC count
    * @since 7.0
    */
    DLL longlong getTotalGCCount();

    /**
    * Returns the total time in milliseconds that the JVM jas spent doing GCs
    * @return time in ms used by the GC
    * @since 7.0
    */
    DLL longlong getTotalGCTime();

    /**
    * Returns the number of events waiting to be processed by the fanout engine
    * @return number of events
    * @since 7.0
    */
    DLL longlong getFanoutBacklog();

    /**
     * This will register the nLogListener for all log events from this realm. This can become quiet busy if the
     * log level on the realm is set for verbose.
     *
     * @param *pListener The listener object to call when new log events happen
     */
    DLL virtual void addLogListener(nLogListener *pListener);

    /**
     * This will remove the log listener from receiving future log events
     *
     * @param *pListener The listener object to remove
     */
    DLL virtual void delLogListener(nLogListener *pListener);

    /**
     * Returns the amount of free memory the Realm Server has within the JVM. This indicates
     * the difference between what the JVM has currently allocated and what the Realm Server has
     * used. The JVM may increase its memory usage if the free memory falls below a set threshold
     * depending on the JVM parameters passed during the realm server startup script.
     *
     * @return Long value of bytes
     */
    DLL virtual longlong getFreeMemory();

    /**
     * Total number of connections served by this realm from the time it started
     *
     * @return longlong count
     */
    DLL virtual longlong getTotalConnections();

    /**
     * Returns the number of connections on this realm
     *
     * @return int number of clients connected
     */
    DLL virtual int getCurrentConnections();

    /**
     * Returns the total number of bytes that the JVM has allocated from the underlying OS. This number may
     * move depending on the Realm Server startup parameters.
     *
     * @return longlong byte count
     */
    DLL virtual longlong getTotalMemory();

    /**
     * Commits the ACL passed in with the Realm Server. This causes these ACLs to be active once the function
     * returns. The nACL object can be retrieved by calling the getACLs() function which returns the realms
     * current list.
     *
     * @param *pAcl A nACL containing nRealmACLEntry
     * @throws nInsufficientPrivilegesException
     *                             If the user is not permitted to perform this operation
     * @throws nNodeException      If the ACLs being set are invalid
     * @throws nBaseAdminException If unable to successfully perform this operation, check the message for more information
     */
    DLL virtual void setACLs(nACL *pAcl);

    /**
     * Returns the current cluster membership state of this realm
     *
     * @return true if the node is a member of a cluster
     * @since 5.1
     */
    DLL bool isClustered();

    /**
    * Set whether to disable asynchronous updates from the realm
    */
    DLL static void enableAsyncUpdates(bool enable);

    /**
    * Get the default data group node
    * the default data group node
    */
    DLL nDataGroupNode* getDefaultDataGroup();

    /**
    * Get the default data group listener
    * @return the data group listener
    */
    DLL nDataGroupListener* getDataGroupListener();

    /**
     * Get all the DataGroups that have been created
     * @return the DataGroups that exist on the realm
     */
    DLL nDataGroupsContainer* getDataGroups();

    /**
     * Get the Security Group Manager for this Realm
     * @return nSecurityGroupManager* the Security Group Manager for this Realm
     */
    DLL virtual nSecurityGroupManager* getSecurityGroupManager();

    /**
     * Registers a nConnectionListener to each nLeaNode of the nRealmNode.
     *
     * @param pListener The instance of the nConnectionListener to be called when connections are made or disconnected
     * @exception nBaseAdminException if the user is not permitted to access these lists, check the message for further information
     * @see nConnectionListener
     */
    DLL virtual void addConnectionListenerToAllLeafNodes(nAPIConnectionListener *pListener);

    /**
     * This will register the nAuditListener for all audit events from this realm.
     *
     * @param pListener The listener object to call when new log events happen
     */
    DLL virtual void addAuditListener(nAuditListener *pListener);

    /**
     * This will register the nAuditListener for all audit events from this realm.
     *
     * @param pListener The listener object to call when new log events happen
     * @param replay   specify true to replay the entire audit contents
     */
    DLL virtual void addAuditListener(nAuditListener *pListener, bool replay);

    /**
     * This will register the nLogListener for all Access events from the plugin manager.
     *
     * @param pListener The listener object to call when new log events happen
     */
    DLL virtual void addPluginAccessListener(nLogListener *pListener);

    /**
     * This will register the nLogListener for all error events from the plugin manager.
     *
     * @param pListener The listener object to call when new log events happen
     */
    DLL virtual void addPluginErrorListener(nLogListener *pListener);

    /**
     * This will cause the realm server to close the current status file, delete it and recreate the file using the attributes specified.
     *
     * @param age the ttl which will be assigned as default to each nirvana status event stored into the status channel file
     * @param capacity set the maximum number of status events to store within the channel
     * @param type change the type of the status channel (default is mixed)
     *
     * @exception nBaseAdminException If the user is not authorized for this function, check the message for further information
     */
    DLL virtual void changeStatusChannel(int type, long age, int capacity);

    /**
     * This will cause the realm server to close the current transaction file, delete it and recreate the file using the attributes specified.
     *
     * @param age the ttl which will be assigned as default to each nirvana transaction
     * @param capacity set the maximum number of transactions to store within the channel
     * @param type change the type of the transaction channel (default is mixed)
     *
     * @exception nBaseAdminException If the user is not authorized for this function, check the message for further information
     */
    DLL virtual void changeTransactionChannel(int type, long age, int capacity);

    /**
     * Calling this function with causes all changes within the group to be committed on the
     * realm and activated. All config changes are immediate and do not require the realm server
     * to be restarted.
     *
     * @param pChangedGroup The nConfigGroup containing the changed nConfigEntry
     * @exception nConfigurationException If the user is not authorized for this function, Check the message for more information
     */
    DLL virtual void commitConfig(nConfigGroup *pChangedGroup);

    /**
     * Creates a new channel on the realm this session is connected.
     *
     * If the channel attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the channel will be created on
     * that realm.
     *
     * @param pAttr The channel attributes object containing the parameters for
     *             the new channel to be created
     * @return an nChannel object representing the newly created nirvana channel
     * @exception nUnknownRemoteRealmException
     *                                       The remote node responded with an unknown exception
     * @exception nSecurityException            User is not authorised for the function
     * @exception nChannelAlreadyExistsException
     *                                       The requested channel already exists
     * @exception nSessionNotConnectedException Current session is not connected
     * @exception nUnexpectedResponseException  Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException     The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException     Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createChannel(nChannelAttributes *pAttr);

    /**
     * Creates a new channel on the realm this session is connected.
     *
     * If the channel attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the channel will be created on
     * that realm.
     *
     * @param pAttr         The channel attributes object containing the parameters for
     *                     the new channel to be created @ param initialEID The channel
     *                     will be created with the first eid being set to this value by
     *                     default it is set to 0 but the user can set it to any
     *                     positive value
     * @param initialEID The value to start the event id at
     * @return an nChannel object representing the newly created nirvana channel
     * @exception nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @exception nSecurityException             User is not authorised for the function
     * @exception nChannelAlreadyExistsException The channel already exists
     * @exception nSessionNotConnectedException  Current session is not connected
     * @exception nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException      Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createChannel(nChannelAttributes *pAttr, longlong initialEID);

    /**
     * Creates a new channel on the realm this session is connected.
     *
     * If the channel attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the channel will be created on
     * that realm.
     *
     * @param pAttr         The channel attributes object containing the parameters for
     *                     the new channel to be created @ param initialEID The channel
     *                     will be created with the first eid being set to this value by
     *                     default it is set to 0 but the user can set it to any
     *                     positive value
     * @param initialEID The value to start the event id at
     * @param pInitialACL   The initial ACLs to apply to the channel at creation time
     * @param pDead         The dead event store that will contain all purged, aged and dead events
     * @return an nChannel object representing the newly created nirvana channel
     * @exception nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @exception nSecurityException             User is not authorised for the function
     * @exception nChannelAlreadyExistsException The channel already exists
     * @exception nSessionNotConnectedException  Current session is not connected
     * @exception nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException      Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createChannel(nChannelAttributes *pAttr, longlong initialEID, nACL *pInitialACL, nLeafNode *pDead);

    /**
     * Creates a new channel on the realm this session is connected.
     *
     * If the channel attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the channel will be created on
     * that realm.
     *
     * @param pAttr         The channel attributes object containing the parameters for
     *                     the new channel to be created @ param initialEID The channel
     *                     will be created with the first eid being set to this value by
     *                     default it is set to 0 but the user can set it to any
     *                     positive value
     * @param initialEID The value to start the event id at
     * @param pDead         The dead event store that will contain all purged, aged and dead events
     * @return an nChannel object representing the newly created nirvana channel
     * @exception nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @exception nSecurityException             User is not authorised for the function
     * @exception nChannelAlreadyExistsException The channel already exists
     * @exception nSessionNotConnectedException  Current session is not connected
     * @exception nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException      Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createChannel(nChannelAttributes *pAttr, longlong initialEID, nLeafNode* pDead);

    /**
     * Creates a new channel on the realm this session is connected.
     *
     * If the channel attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the channel will be created on
     * that realm.
     *
     * @param pAttr         The channel attributes object containing the parameters for
     *                     the new channel to be created @ param initialEID The channel
     *                     will be created with the first eid being set to this value by
     *                     default it is set to 0 but the user can set it to any
     *                     positive value
     * @param pDead         The dead event store that will contain all purged, aged and dead events
     * @return an nChannel object representing the newly created nirvana channel
     * @exception nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @exception nSecurityException             User is not authorised for the function
     * @exception nChannelAlreadyExistsException The channel already exists
     * @exception nSessionNotConnectedException  Current session is not connected
     * @exception nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException      Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createChannel(nChannelAttributes *pAttr, nLeafNode *pDead);

    /**
     * Creates a new queue on the realm this session is connected.
     *
     * If the queue attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the queue will be created on
     * that realm.
     *
     * @param pAttr       The queue attributes object containing the parameters for the new queue to be created
     * @return an nLeafNode object representing the newly created nirvana queue
     * @exception nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @exception nSecurityException             User is not authorised for the function
     * @exception nChannelAlreadyExistsException The channel already exists
     * @exception nSessionNotConnectedException  Current session is not connected
     * @exception nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException      Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createQueue(nChannelAttributes *pAttr);

    /**
     * Creates a new queue on the realm this session is connected.
     *
     * If the queue attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the queue will be created on
     * that realm.
     *
     * @param pAttr       The queue attributes object containing the parameters for the new queue to be created
     * @param pInitialACL The initial ACLs to apply to the queue at creation time
     * @param pDead         The dead event store that will contain all purged, aged and dead events
     * @return an nLeafNode object representing the newly created nirvana queue
     * @exception nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @exception nSecurityException             User is not authorised for the function
     * @exception nChannelAlreadyExistsException The channel already exists
     * @exception nSessionNotConnectedException  Current session is not connected
     * @exception nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException      Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createQueue(nChannelAttributes *pAttr, nACL *pInitialACL, nLeafNode *pDead);

    /**
     * Creates a new queue on the realm this session is connected.
     *
     * If the queue attributes specify a realm different than the one this session is
     * connected to, a transparent redirection will occur and the queue will be created on
     * that realm.
     *
     * @param pAttr       The queue attributes object containing the parameters for the new queue to be created
     * @param pDead         The dead event store that will contain all purged, aged and dead events
     * @return an nLeafNode object representing the newly created nirvana queue
     * @exception nUnknownRemoteRealmException   The remote realm responded with an unknown exception
     * @exception nSecurityException             User is not authorised for the function
     * @exception nChannelAlreadyExistsException The channel already exists
     * @exception nSessionNotConnectedException  Current session is not connected
     * @exception nUnexpectedResponseException   Internal Error has occured, since we received a response from the server out of sequence
     * @exception nRequestTimedOutException      The server has not responded to the request in the timeout period
     * @exception nIllegalArgumentException      Illegal parameter, check the message for more information
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual nLeafNode* createQueue(nChannelAttributes *pAttr, nLeafNode *pDead);

    /**
     * This will remove the audit listener from receiving future audit events.
     *
     * @param pListener The listener object to remove
     */
    DLL virtual void delAuditListener(nAuditListener *pListener);

    /**
     * Removes the registered listener from the realm so no further callbacks are made to the listener.
     *
     * @param pListener The listener object to remove
     * @exception nBaseAdminException if the user is not permitted to access these lists
     * @see nConnectionListener
     */
    DLL virtual void delConnectionListener(nAPIConnectionListener *pListener);

    /**
     * Removes the specified channel/queue from the server
     *
     * @param pNode LeafNode to delete
     * @exception nUnknownRemoteRealmException  if the path to the realm has been lost
     * @exception nSecurityException            If the current user has no authority to delete the resource
     * @exception nChannelNotFoundException     The channel/queue has already been deleted
     * @exception nSessionNotConnectedException The current session is not currently connected
     * @exception nUnexpectedResponseException  The request resulted in an unknown response from the server
     * @exception nRequestTimedOutException     The request exceeded the specified time out period
     * @exception nIllegalArgumentException     The argument supplied is invalid
     * @exception nSessionPausedException       The session is currently paused, please resume
     */
    DLL virtual void delLeafNode(nLeafNode *pNode);

    /**
     * This will remove the log listener from receiving future log events
     *
     * @param pListener The listener object to remove
     */
    DLL virtual void delPluginAccessListener(nLogListener *pListener);

    /**
     * This will remove the log listener from receiving future log events
     *
     * @param pListener The listener object to remove
     */
    DLL virtual void delPluginErrorListener(nLogListener *pListener);

    /**
     * Number of data buffers created within the realms and for use within event fanout
     * @return the number of buffers created
     */
    DLL virtual longlong getBuffersCreated();

    /**
     * Number of data buffers reused by the event fanout
     * @return number of reused buffers
     */
    DLL virtual longlong getBuffersReused();

    /**
     * Returns the nConfigGroup specified by the name
     *
     * @param name the name of the config group to locate
     * @return nConfigGroup of the specified name
     */
    DLL virtual nConfigGroup* getConfigGroup(const std::string& name);

    /**
     * Return the number of reused threads within the realm
     * @return the number of reused threads within the realm
     */
    DLL virtual int getReUsedThreads();

    /**
     * Returns the last status update date that the server sent
     *
     * @return Server Date
     */
    DLL virtual time_t getServerTime();

    /**
     * Returns the Date that the realm server was started
     *
     * @return Date of realm start
     */
    DLL virtual time_t getStartTime();

    /**
     * Returns the update interval for status updates
     *
     * @return a long representing the number of milliseconds between each update
     */
    DLL virtual longlong getUpdateInterval();

    /**
     * Get the total number of threads that have been allocated threads within the realm
     * @return the total number of threads allocated
     */
    DLL virtual int getVendedThreads();

    /**
     * Checks if there is a connection listener object associated with the realm.
     *
     * @return true if connection listener has been set
     * @see nConnectionListener
     */
    DLL virtual bool hasConnectionListener();

    /**
     * If the realm is running within an application then this will be set to true
     *
     * @return true if the realm is running as an embedded server
     */
    DLL virtual bool isAnEmbeddedServer();

    /**
     * This method returns true when the namespace discovery process is complete for the entire namespace
     * from this node down.
     *
     * Please refer to the isNamespaceComplete() function
     *
     * @return boolean
     */
    DLL virtual bool isEntireNamespaceComplete();

    /**
     * Sends a request to the Realm Server to release cached memory.
     */
    DLL virtual void releaseCachedMemory();

    /**
     * This method will cause the server to disconnect the connection described by the connection ID. The default
     * behaviour of the client is to reconnect so calling this alone will basically bounce the client. If your intent
     * is to disable the remote user, you must first disable the user@host from the realm and then call this function.
     *
     * @param connectionId The connectionId to disconnect
     * @param sendRedirection Tells the server to send a Server Redirection event to this client
     * @exception nBaseAdminException If the user is not authorized for this function, check the message for further information
     */
    DLL virtual void removeConnection(const std::string& connectionId, bool sendRedirection = false);

    /**
     * Sends a request to the Realm Server to produce a Thread dump.
     */
    DLL virtual void requestThreadDump();

    /**
     * This will cause the realm server to close the current audit log, rename it to the current date and start
     * a new audit log
     *
     * @exception nBaseAdminException If the user is not authorized for this function, check the message for further information
     */
    DLL virtual void rollAuditFile();

    /**
     * Rolls the servers log file
     */
    DLL void rollLogFile();

    /**
     * Return a new nACL object
     * @return a new nACL object
     */
    DLL static nACL* createACL();

    /**
     * Return whether realm node will receive asynchronous updates from the server.
     * @return whether asynchronous updates will be received
     */
    DLL static bool getAsyncUpdateFlag();

    /**
     * Flag indicating whether the realm node will receive asynchronous updates from the server.
     * @param flag inidcating whether asynchronous updates will be received
     */
    DLL static void setAsyncUpdateFlag(bool flag);

    /**
     * Return the number of channels within the realm
     *
     * @return Channels within the realm
     */
    DLL virtual int getNoOfChannels();

    /**
     * Return the number of queues within the realm
     *
     * @return Queues within the realm
     */
    DLL virtual int getNoOfQueues();

    /**
     * Number of threads currently queued ready to execute tasks
     * @return number of queued threads
     */
    DLL virtual int getQueuedThreads();

    /**
     * Return the total number of scheduled tasks currently running within the realm
     * @return the number of tasks within the realm
     */
    DLL virtual longlong getInternalSchedulerSize();

    /**
     * Return the number of thread the JVM has allocated for the Realm Server. This includes all
     * the threads used by the JVM as well.
     *
     * @return Number of threads
     */
    DLL virtual int getNoOfThreads();

    /**
     * Returns the Realms Multicast Manager
     *
     * @return The com.pcbsys.nirvana.nAdminAPI.nMulticastManager object
     * @see nMulticastManager
     */
    DLL virtual nMulticastManager* getMulticastManager();

    /** Finds the datagroup with the same name as the one specified in the current realm node
     *
     * @param name String name of the datagroup to find
     * @return The nNode object corresponding to the found datagroup, NULL if the datagroup was not found in the realm node.
     */
    DLL virtual nNode* findDatagroup(const std::string& name);

	DLL virtual nZoneManager* getZoneManager();
	/**
	 * The remote interest manager is an object that allows the user to control propagation of messages between realms.
	 * @return returns the remote interest manager for the given realm node
	 */
	DLL virtual nRemoteInterestManager* getRemoteInterestManager();

  protected:
    virtual void create();
    virtual void connectToRealm();
    virtual void triggerUpdates(Object *pArg, bool deleted);
    virtual nAdminSession* createSession();
    virtual void processCluster();
    virtual void updateRealms();
    virtual nRealmNode* findRealm(const std::string& realmname);
    virtual void addGetJoin(nLeafNode *pSource);
    virtual void addJoin(nJoinInformation *pJoin, nLeafNode *pSource);
    virtual void setCluster(nClusterNode *pNode);
    virtual nThreadEntry** getRealmScheduledThreadList(int &numEntry);
    void setThreadPoolDetails(nEventProperties* props);


    static bool sEnableUpdates;

    nSessionAttributes *m_pAttr;
    nNode *m_pParent;
    std::string m_username;

    nAdminSession *m_pSession;
    bool m_bAuthorised;
    nInterfaceManager *m_pInterfaceManager;

    std::map<std::string, nConnectionDetails*> m_connections;
    bool m_bClosed;
    int m_noOfRealms;
    nPkgListenerMapper *m_pListener;
    nPkgDataGroupListener *myDataGroupListener;
    nRealm *m_pRealm;
    fSortedList<std::string, nConfigGroup*> m_configObjects;
    longlong m_updateInterval;
    nClusterNode *m_pClusterNode;
    Poco::SynchronizedObject m_namespaceLock;
    fSortedList<longlong, nPkgLeafNodeIndex*> m_leafNodeIndex;
    fSortedList<longlong, nPkgServiceNodeIndex*> m_serviceNodeIndex;
    fSortedList<std::string, nRealmNode*> m_realmNodes;
    static fSortedList<std::string, nSecureRealm*> m_realmString;
    fSortedList<std::string, nLinkNode*> m_linkNodes;
    nACL *m_pACLs;
    nSecureRealm *m_pBaseRealm;
    int m_noThreads;
	bool m_isPausedPublishing;
    longlong m_totalSubscribed;
    longlong m_totalPublished;
    longlong m_totalMemory;
    longlong m_totalConnection;
    longlong m_currentConnections;
    longlong m_freeMemory;
    time_t m_startTime;
    time_t m_serverTime;
    std::list<nPkgCloseListener*> m_closeListeners;
    std::list<nAuditListener*> m_auditListeners;
    Poco::SynchronizedObject m_completedObject;
    nClusterMemberConfiguration *m_pClusterCfg;

    longlong gc_count;
    longlong gc_time;

    static fSortedList<std::string, nRealmNode*> m_realmLists;
    static std::vector<nRealmNode*> allRealmNodes;
    static const Poco::SynchronizedObject allRealmNodes_lock;
    static Poco::Mutex m_realmListMutex;
    static const std::string p2p;
    static const int m_ACLWaitDelay = 10000;

    nDataGroupNode* defaultGroup;
    nDataGroupsContainer* myDataGroupsContainer;

    nSecurityGroupManager* securityGroupManager;
	nZoneManager* m_pZoneManager;
	nRemoteInterestManager* m_pRemoteInterestMgr;

    void addClusterRealm(nRealm* remoteRealm, nAdminSession* session, std::string name, std::string localClusterName);

    virtual void removeLocalGroupReferences(std::string* groupNames, int numGroupNames);

  private:
    void createNameSpace();
    void searchNodes(fSortedList<std::string, nNode*>& nodes);
    nRealmNode* scanForRealm(nContainer *pCont, const std::string& name);
    nLeafNode* registerChannel(nRealmNode *pNode, nChannel *pChan);
    nLeafNode* registerQueue(nRealmNode *pNode, nQueue *pQueue);
    void doClose();
    void closeRemoteSessions(fSortedList<std::string, nNode*>& nodes);
    void scanChildren(fSortedList<std::string, nNode*>& nodes, long timeout);
    void removeRealm(const std::string& node, nContainer *pCont);
    void cleanup();
    void addConnectionListenersToLeafNodes(fSortedList<std::string, nNode*>& nodes, nAPIConnectionListener *pListener);
    bool isMemberOfRealmList(const std::string& realmName);
    bool isMemberOfLinkNodeList(const std::string& realmName);
    void addRealmNodes(std::list<nSecureRealm*> *pVec);
    void removeUnusedLinkNodes(std::list<nSecureRealm*> *pVec);
    void removeUnusedRealmNodes(std::list<nSecureRealm*> *pVec);
    void loadChannels();
    void loadDataGroups();
    void loadRealms();
    void shuffleConnectionList(nSecureRealm *pRealm);

    nPkgReconnectHandler *m_pReconnectHandler;
    nPkgConfigListener *m_pCfgListener;
    bool m_bEmbedded;
    bool m_bNamespaceComplete;
    nPkgGetJoins *m_pJoins;
    nPkgIncompleteJoinQueue *m_pIncompleteJoins;
    nPkgLogListener *m_pLogListener;
    Poco::Mutex m_addConnectionListenerMutex;
    Poco::Mutex m_delConnectionListenerMutex;
    Poco::Mutex m_addLogListenerMutex;
    Poco::Mutex m_delLogListenerMutex;
    Poco::Mutex m_addAuditListenerMutex;
    Poco::Mutex m_delAuditListenerMutex;
    Poco::Mutex m_addPluginAccessListenerMutex;
    Poco::Mutex m_delPluginAccessListenerMutex;
    Poco::Mutex m_addPluginErrorListenerMutex;
    Poco::Mutex m_delPluginErrorListenerMutex;
    nPkgAuditListener *m_pAuditListener;
    nPkgLogListener *m_pAccessListener;
    nPkgLogListener *m_pErrorListener;
    nEventProperties *m_pThreadDetails;
	nStatusChannel* m_pStatusChannel;


    friend class nPkgReconnectHandler;
    friend class nClusterRefresh;
    friend class nInterfaceManager;
    friend class nPkgAdminListener;
    friend class nClusterNode;
    friend class nServiceNode;
    friend class nLeafNode;
    friend class nPkgConfigListener;
    friend class nPkgServiceObserver;
    friend class nPkgStatusListener;
    friend class nPkgValidateNamespace;
    friend class nPkgThreadUpdate;
    friend class nContainer;
    friend class nChannelListener;
    friend class nPkgListenerMapper;
    friend class nPkgAuditListener;
    friend class nDataGroupsContainer;
    friend class nDataGroupNode;
    friend class RealmStatusHandler;
    friend class ThreadPoolStatusHandler;
    friend class DataGroupStatusHandler;
    friend class InterfaceStatusHandler;
    friend class StoreStatusHandler;
    friend class ConnectionStatusHandler;
    friend class nMulticastManager;
    friend class nNodeUtilities;
    friend class nSecurityGroupManager;

};

}
}
}
}

