/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nNode.h"
#include "nRemovable.h"
#include "nCopyable.h"
#include "nJoinable.h"
#include "nPkgCloseListener.h"
#include "nSecurityGroup.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nChannelAttributes;
class nChannel;
class nQueue;
class nJoinInformation;
}
namespace nbase {
class nSecureChannel;
class nChannelStatus;
}
namespace nAdminAPI {

class nChannelListener;
class nJoinDetails;
class nACL;
class nRealmNode;
class nACLEntry;
class nConnectionDetails;
class nAPIConnectionListener;

using namespace client;
using namespace nbase;
using namespace foundation::fbase;

/**
 * This class represents the Nirvana Channel or Queue on the Nirvana Realm. The super class is nNode which implements
 * Observable. When any details change for this object any registered Observers are notified with the change.
 * The status functions may return 0 until the status events are received from the server.
 *
 * @see nNode
 * @see nRemovable
 * @see nCopyable
 * @see nJoinable
 * @see nPkgCloseListener
 * @see Observable
 */
class nLeafNode :
    public nNode, public nRemovable, public nCopyable, public nJoinable, public nPkgCloseListener {
  public:

    virtual void addRef() {
        nNode::addRef();
    }

    virtual bool delRef() {
        return nNode::delRef();
    }

    /**
     * Creates a new nLeafNode
     *
     * @param name the name of the new leaf node
     * @param *pChannel the channel associated with the leaf node
     * @param *pParent the nNode parent of this node
     */
    nLeafNode(const std::string& name, nSecureChannel *pChannel, nNode *pParent);
    virtual ~nLeafNode(void);



    /**
     * Returns true if this node is removable
     *
     * @return a bool, true if the node is removable
     */
    virtual bool IsRemovable();

    /**
     * This method removes this nLeafNode (channel or queue) from its parent nRealmNode.
     *
     * @param removeChildren a boolean specifying whether siblings should be removed too. Specify false,
     * as nLeafNodes do not have children
     *
     * @exception nUnsupportedRemoveException thrown if join is not supported (e.g. on queues)
     * @exception nNodeException is thrown if an error occurs in the remove operation
     *
     * @see nRealmNode
     * @see nLinkNode
     */
    virtual void remove(bool removeChildren);

    /**
     * Copies this nLeafNode (channel or queue) to a new nLeafNode (channel or queue) within the nRealmNode
     * passed as a parameter, with the specified channel name.
     *
     * Using this method, allows nLeafNodes to be copied to other realms within the namespace
     *
     * The channel name used for the new copied nLeafNode must be unique in the destination realm
     *
     * @param *pToNode The nRealmNode to copy the channel to
     * @param toName The name of the new nLeafNode (channel or queue)
     * @param bWaitForCompletion Specifies whether the method returns before copy operation has completed
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object that will inform you of the operation status
     * @exception nUnsupportedCopyException Thrown if copy is not supported
     * @deprecated As of version 2.0
     */
    virtual void copy(nNode *pToNode, std::string& toName, bool bWaitForCompletion, nACL *pAcl, nCommandStatus *pCmdStatus);

    /**
     * Copies this nLeafNode (channel or queue) to a new nLeafNode (channel or queue) within same realm
     * with the specified channel name.
     *
     * The channel name used for the new copied nLeafNode must be unique in the realm
     *
     * @param toName The name of the new nLeafNode (channel or queue)
     * @param bWaitForCompletion Specifies whether the method returns before copy operation has completed
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object that will inform you of the operation status
     * @exception nUnsupportedCopyException Thrown if copy is not supported
     * @deprecated As of version 2.0
     */
    virtual void copy(std::string& toName, bool bWaitForCompletion, nACL *pAcl, nCommandStatus *pCmdStatus);

    /**
     * Copies this nLeafNode (channel or queue) to a new nLeafNode (channel or queue) within the nRealmNode
     * passed as a parameter, with the specified channel attributes.
     *
     * Using this method, allows nLeafNodes to be copied to other realms within the namespace
     *
     * Attributes can be different on the copied channel, such as ttl, capacity and type
     *
     * @param *pToNode The nRealmNode to copy the channel to
     * @param bWaitForCompletion Specifies whether the method returns before copy operation has completed
     * @param *pAttrib The channel attributes of the new nLeafNode
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object that will inform you of the operation status
     * @exception nUnsupportedCopyException Thrown if copy is not supported
     */
    virtual void copy(nNode *pToNode, bool bWaitForCompletion, nChannelAttributes *pAttrib, nACL *pAcl, nCommandStatus *pCmdStatus);

    /**
     * Copies this nLeafNode (channel or queue) to a new nLeafNode (channel or queue) within the same
     * realm node with the specified channel attributes.
     *
     * Attributes can be different on the copied channel, such as ttl, capacity and type
     *
     * @param bWaitForCompletion Specifies whether the method returns before copy operation has completed
     * @param *pAttrib The channel attributes of the new nLeafNode
     * @param *pAcl an optional initial acl object that will be set on the object being copied
     * @param *pCmdStatus an optional nCommandStatus object that will inform you of the operation status
     * @exception nUnsupportedCopyException Thrown if copy is not supported
     */
    virtual void copy(bool bWaitForCompletion, nChannelAttributes *pAttrib, nACL *pAcl, nCommandStatus *pCmdStatus);

    /**
     * This method enables the joining of the object from one node to another, specifying a
     * selector, and a maximum hop count for the events. This is only supported on channel
     * objects.
     *
     * @param *pToNode the nNode object to join this node to
     * @param bIsRouted Reserved for future use.
     * @param hopcount if an event is published directly to this node (i.e. does not
     * arrive here through another join), this is the maximum number of hops it will follow
     * @param selector a message selector specifying a filter for this message route
     *
     * @exception nUnsupportedJoinException thrown if join is not supported (e.g. on queues)
     * @exception nBaseAdminException is thrown if the join creation fails
     *
     */
    virtual void join(nNode *pToNode, bool bIsRouted, int hopcount, const std::string& selector);

    /**
     * This method enables the joining of the object from one node to another, specifying a
     * selector, and a maximum hop count for the events. This is only supported on channel
     * objects.
     *
     * @param *pToNode the nNode object to join this node to
     * @param bIsRouted Reserved for future use.
     * @param hopcount if an event is published directly to this node (i.e. does not
     * arrive here through another join), this is the maximum number of hops it will follow
     * @param selector a message selector specifying a filter for this message route
     * @param allowPurge whether purges will be propagated to the joined channel
     *
     * @exception nUnsupportedJoinException thrown if join is not supported (e.g. on queues)
     * @exception nBaseAdminException is thrown if the join creation fails
     *
     */
    virtual void join(nNode *pToNode, bool bIsRouted, int hopcount, const std::string& selector, bool allowPurge);

    /**
     * This method enables the joining of the object from one node to another, specifying a
     * selector for filtered joins
     *
     * @param *pToNode the nNode object to join this node to
     * @param selector the filter to be applied to the join
     *
     * @exception nUnsupportedJoinException thrown if join is not supported (e.g. on queues)
     * @exception nBaseAdminException is thrown if the join creation fails
     *
     */
    virtual void join(nNode *pToNode, const std::string& selector);

    /**
     *  Called when the nRealmNode is closed.
     *  @param *pNode The nRealmNode which has been closed.
     */
    virtual void closed(nRealmNode *pClose);

    /**
     * Returns the channel attributes for this channel/queue.
     *
     * @see com.pcbsys.nirvana.client.nChannelAttributes
     * @return nChannelAttributes
     */
    virtual nChannelAttributes* getAttributes();

    /**
     * Retrieves the channel/queues ACLs which can then be modified and committed with the setACLs() function
     *
     * @return The list of nChannelACLEntry in a nACL object
     * @exception nBaseAdminException If this user is not permitted to view this data
     */
    virtual nACL* getACLs();

    /**
     * Returns true if this node is a channel
     *
     * @return a bool, true if the node is a channel
     */
    virtual bool isChannel();

    /**
     * Returns true if this node is a queue
     *
     * @return a bool, true if the node is a queue
     */
    virtual bool isQueue();

    /**
     * Returns the Realm Node this leaf node is associated with. Please note this might not be the root of the namespace
     * but a federated realm.
     *
     * @return nRealmNode value
     */
    virtual nRealmNode* getRealm();

    /**
     * Commits the ACL passed in with the Realm Server. This causes these ACLs to be active once the function
     * returns. The nACL object can be retrieved by calling the getACLs() function which returns the channel/queues
     * current list.
     *
     * @param *pAcl A nACL containing nChannelACLEntry
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    virtual void setACLs(nACL *pAcl);

    /**
     * Adds a specific acl entry to the leaf node acl
     *
     * @param *pEntries An nACL list containing the subjects and permissions to add to the leaf node acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void addACLEntries(nACL *pEntries);

    /**
     * Adds a specific acl entry to the leaf node acl
     *
     * @param *pEntry An nACL entry containing the subject and permissions to add to the leaf node acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void addACLEntry(nACLEntry *pEntry);

    /**
     * modifies a specific acl entry's permissions in the leaf node acl.
     *
     * @param *pEntries An nACL entry containing the subject and permissions to modify in the leaf node acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void modACLEntries(nACL *pEntries);

    /**
    * modifies a specific acl entry's permissions in the leaf node acl.
    *
    * @param *pEntry An nACL entry containing the subject and permissions to modify in the leaf node acl
    * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
    * @exception nNodeException if the ACLs being set are invalid
    * @exception nBaseAdminException if unable to perform the operation, check the message for further information
    */
    DLL void modACLEntry(nACLEntry *pEntry);

    /**
     * removes a specific acl entry from the leaf node acl.
     *
     * @param *pEntries An nACL list containing the subjects and permissions to remove from the leaf node acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void removeACLEntries(nACL *pEntries);

    /**
     * removes a specific acl entry from the leaf node acl.
     *
     * @param *pEntry An nACL entry containing the subject and permissions to remove from the leaf node acl
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL void removeACLEntry(nACLEntry *pEntry);

    /**
     * Adds a specific acl entry to the leaf node acl
     *
     * @param *pEntries An nACL list containing the subjects and permissions to add to the leaf node acl
     * @exception nInsufficientPrivilegesException If the user is not permissioned to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    virtual nACLEntry* createACLEntry(const std::string& subject, BitArray *pBs);

	/**
	* This method creates an ACL entry
	*
	* @param grp the security group to create the ACL for
	* @param *pBs the BitArray representing the ACL settings to use.
	* @throws Exception If the name space is not completed with in the time specified
	*/
	DLL virtual nACLEntry* createACLEntry(nSecurityGroup* grp, BitArray* pBs);

    /**
     * Registers the listener object with the channel/queue so that whenever a connection is made or lost with the channel
     * such as a subscriber is added the listener is notified of the change in state of the channel.
     * Currently only one listener per session is supported.
     *
     * @param *pListener the connection listener to be added to the leaf node (channel or queue)
     * @see nConnectionListener
     * @exception nBaseAdminException if the user is not permitted to access these lists, check the message for further information
     */
    virtual void addListener(nAPIConnectionListener *pListener);

    /**
     * This method enables the joining of the object from one node to another, specifying a
     * selector for filtered joins
     *
     * @param *pToNode   the nNode object to join this node to
     * @param selector the filter to be applied to the join
     * @exception nUnsupportedJoinException thrown if join is not supported (e.g. on queues)
     * @exception nBaseAdminException       is thrown if the join creation fails
     */
    void archiveJoin(nNode *pToNode, const std::string& selector);

    /**
     * This method deletes the join between nodes. This is only supported where the source node is a channel
     *
     * @param pNode the nNode object this node is joined to
     * @exception nUnsupportedJoinException thrown if join is not supported (e.g. from queues)
     * @exception nBaseAdminException       is thrown if the join deletion fails
     */
    virtual void deleteJoin(nNode *pNode);

    /**
     * Removes the registered listener from the channel so no further callbacks are made to the listener
     *
     * @exception nBaseAdminException if the user is not permitted to access these lists
     * @see nConnectionListener
     */
    virtual void delListener();

    /**
     * Requests that the Realm frees the unused space within this channel/queue. If the Channel/Queue has a large number
     * of events it could take some time to perform. It is recommended to do this during quiet periods.
     *
     * @exception nBaseClientException If the user does not have the permission to request this
     */
    virtual void freeUnusedSpace();

    /**
     * Retreives the channel/queues cache ratio. This ratio represents the (number of cache hits)/(Total Access).
     * This cache is only active when the channel/queue is a persistant store and the server caches the event instead
     * of re-reading it from the store again.
     *
     * @return float value
     */
    virtual double getCacheHitRatio();

    /**
     * This function walks the tree to the root to generate a fully qualified name for this node
     *
     * @return String full path and name
     */
    const std::string & getAbsolutePath();

    /**
     * The number of subscriptions made to this store per second
     *
     * @return float value
     */
    virtual double getConnectionRate();

    /**
     * The number of events published per second
     *
     * @return float value
     */
    virtual double getConsumedRate();

    /**
     * Retrieves the current number of connections to this channel
     *
     * @return long value
     */
    virtual longlong getCurrentNoOfConnections();

    /**
     * Returns the number of events within the channel/queue
     *
     * @return long value
     */
    virtual longlong getCurrentNumberOfEvents();

    /**
     * The total number of milliseconds it takes to fanout each event to all consumers
     *
     * @return long value
     */
    virtual longlong getFanoutTime();

    /**
     * Returns a map of nJoinDetails objects containing information about channels
     * sending events to this channel
     *
     * @return Map of joins for this leaf node
     * @see nJoinDetails
     */
    virtual std::map<nLeafNode*, nJoinDetails*>& getInboundJoins();

    /**
     * Returns the last EID that was used for the channel/queue
     *
     * @return long value
     */
    virtual longlong getLastEID();

    /**
     * Returns a count of outbound joins this channel has
     *
     * @return count of joins
     * @see nJoinDetails
     */
    virtual int getOutboundJoinCount();

    /**
     * Returns a map of nJoinDetails objects containing information about channels
     * that this channel will pass events to
     *
     * @return map of joins for this leaf node
     * @see nJoinDetails
     */
    virtual std::map<std::string, nJoinDetails*>& getOutboundJoins();

    /**
     * Returns the amount of free space within a store as a percentage of the overall space used
     *
     * @return int value
     */
    virtual int getPercentageFreeInStore();

    /**
     * The number of events published per second
     *
     * @return int value
     */
    virtual double getPublishRate();

    /**
     * Returns the total number of events that this channel has delivered to subscribers
     *
     * @return long value
     */
    virtual longlong getTotalConsumed();

    /**
     * Returns the total number of connections that this channel has had since the realm started
     *
     * @return long value
     */
    virtual longlong getTotalNoOfConnections();

    /**
     * Returns the total number of events published/pushed to this channel/queue since the realm has started
     *
     * @return long value
     */
    virtual longlong getTotalPublished();

    /**
     * Returns the number of bytes that this channel/queue consumes on the server
     *
     * @return long value
     */
    virtual longlong getUsedSpace();

    /**
     * Returns true if this represents a nirvana channel or queue that is part of a cluster
     *
     * @return boolean value
     */
    virtual bool isClusterWide();

    static nACL* createACL();

  protected:
    virtual void disconnected();
    virtual void reconnected();
    virtual int getType();
    virtual void getJoinDetailsFromServer();
    virtual bool constructJoinInfo(nJoinInformation *pJi);
    virtual void statusUpdate(nChannelStatus *pStatus);

    nChannelListener *m_pListener;
    bool m_bGotJoins;
    longlong m_currentNumberOfEvents;
    nChannel *m_pClientChannel;

  private:
    std::map<std::string, nConnectionDetails*> m_connections;
    std::map<std::string, nJoinDetails*> m_outbound;
    std::map<nLeafNode*, nJoinDetails*> m_inbound;
    nSecureChannel* m_pChannel;
    nACL *m_pACLs;
    bool m_bIsChannel;
    nRealmNode *m_pRealm;
    nQueue* m_pClientQueue;
    longlong m_lastUpdate;
    longlong m_lastNullUpdate;
    double m_cacheHitRatio;
    longlong m_totalNoOfConnections;
    longlong m_currentNoOfConnections;
    longlong m_lastEID;
    longlong m_totalConsumed;
    longlong m_totalPublished;
    int m_consumedRate;
    int m_publishRate;
    int m_connectionRate;
    longlong m_usedSpace;
    int m_percentageFreeInStore;
    longlong m_fanoutLatency;

    friend class nPkgReconnectHandler;
    friend class nPkgAdminListener;
    friend class nPkgStatusListener;
    friend class nContainer;
    friend class nPkgGetJoins;
    friend class nPkgLeafCopy;
    friend class nPkgQLeafCopy;
    friend class nRealmNode;
    friend class nChannelListener;
    friend class nPkgIncompleteJoinQueue;
    friend class nClusterNode;
    friend class StoreStatusHandler;
};

}
}
}
}
