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
#include "nDataGroup.h"
#include "nPkgCloseListener.h"
#include "fSortedList.h"
#include "Poco/Mutex.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nDataGroup;
namespace p2p {
class nServiceFactory;
class nServiceInfo;
}
}
namespace nbase {
class nSecureChannel;
}
namespace nAdminAPI {

using namespace foundation::collections;
using namespace nbase;
using namespace client::p2p;
using namespace client;

class nACL;
class nDataGroupsContainer;

/**
 * This represents a node within the Nirvana Realm namespace which contains other nodes, such as a directory or another Realm.
 * nContainer performs no functions other than containing the other nodes and being a placeholder in the namespace.
 */
class nContainer :
    public nNode, public nPkgCloseListener {
  public:
    nContainer(void);
    virtual ~nContainer(void);

    virtual void addRef() {
        nNode::addRef();
    }

    virtual bool delRef() {
        return nNode::delRef();
    }

    /**
     * Given a name of the form /container/container/name this function will locate the name object and
     * return it, or null if that object can not be found.
     *
     * @param name the name of the node to locate as a String
     * @return a nNode which could be a nRealmNode, nLeafNode or a nContainer
     * @exception nAdminIllegalArgumentException thrown if null is passed as the nNode
     * @see nRealmNode
     * @see nLeafNode
     * @see nContainer
     */
    DLL virtual nNode* findNode(std::string name);

    /**
     * Given a mount point this function will determine if this container contains a
     * mounted realm at the specified mount point
     *
     * @param name the mount point as a string as a String
     * @return true if container contains realm at that mount point
     * @exception nAdminIllegalArgumentException thrown if null is passed as the nNode
     */
    DLL virtual bool hasRealmAt(std::string name);

    /**
     * Given a mount point this function will return
     * a realm if one exists at the specified mount point
     *
     * @param name the mount point as a string as a String
     * @return nRealmNode if container contains realm at that mount point, else null
     * @exception nAdminIllegalArgumentException thrown if null is passed as the nNode
     */
    DLL virtual nRealmNode* getRealmAt(std::string name);
    /**
     * Called when a realm node is closed, for internal use only
     * @param *pNode the node which has been closed
     */
    virtual void closed(nRealmNode *pNode);
    /**
     * Returns the type of this object, for internal use only.
     * @return the type of the object
     */
    virtual int getType();

    /**
     * Returns an fSortedList of all the nodes under this container. These could be
     * other nContainer nodes, nLeafNode or nRealmNode objects.
     *
     * @return An fSortedList of node name, nNode objects pairs under this container
     * @see nRealmNode
     * @see nLeafNode
     * @see nContainer
     */
    DLL virtual fSortedList<std::string, nNode*>& getNodes();

    /**
    * Adds an acl to the list of nodes.
    *
    * @param *pAcl An nACL to apply to the list of nodes
    * @param ppNodes the list of nodes to apply the acl to
    * @param numNode the size of the node array
    * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
    * @exception nNodeException if the ACLs being set are invalid
    * @exception nBaseAdminException if unable to perform the operation, check the message for further information
    */
    DLL void addACLEntries(nACL *pAcl, nNode **ppNodes = NULL, int numNode = 0);

    /**
     * Adds a specific acl entry to all known nodes within the nContainer node.
     *
     * @param *pEntry An nACL entry containing the subject and permissions to apply to all nodes under the container
     * @param bAllChannels if set then all channels within the container will have the acl applied
     * @param bAllQueues if set then all queues within the container will have the acl applied
     * @param bAllServices if set then all services within the container will have the acl applied
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL virtual void addACLEntry(nACLEntry *pEntry, bool bAllChannels = true, bool bAllQueues = true);

    /**
    * Modifies an existing acl for the list of nodes.
    *
    * @param *pAcl An nACL to apply to the list of nodes
    * @param ppNodes the list of nodes to apply the acl to
    * @param numNode the size of the node array
    * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
    * @exception nNodeException if the ACLs being set are invalid
    * @exception nBaseAdminException if unable to perform the operation, check the message for further information
    */
    DLL void modACLEntries(nACL *pAcl, nNode **ppNodes = NULL, int numNode = 0);

    /**
     * modifies a specific acl entry's permissions for all known nodes within the nContainer node.
     *
     * @param *pEntry An nACL entry containing the subject and permissions to apply to all nodes under the container
     * @param bAllChannels if set then all channels within the container will have the acl modified
     * @param bAllQueues if set then all queues within the container will have the acl modified
     * @param bAllServices if set then all services within the container will have the acl modified
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL virtual void modACLEntry(nACLEntry *pEntry, bool bAllChannels = true, bool bAllQueues = true);

    /**
    * Removes the contents of an acl list from the list of nodes.
    *
    * @param *pAcl An nACL of entries to be applied to the list of nodes
    * @param ppNodes the list of nodes to apply the acl to
    * @param numNode the size of the node array
    * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
    * @exception nNodeException if the ACLs being set are invalid
    * @exception nBaseAdminException if unable to perform the operation, check the message for further information
    */
    DLL void removeACLEntries(nACL *pAcl, nNode **ppNodes = NULL, int numNode = 0);

    /**
     * removes a specific acl entry from all known nodes within the nContainer node.
     *
     * @param *pEntry An nACL entry containing the subject and permissions to apply to all nodes under the container
     * @param bAllChannels if set then all channels within the container will have the acl removed
     * @param bAllQueues if set then all queues within the container will have the acl removed
     * @param bAllServices if set then all services within the container will have the acl removed
     * @exception nInsufficientPrivilegesException If the user is not permitted to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    DLL virtual void removeACLEntry(nACLEntry *pEntry, bool bAllChannels = true, bool bAllQueues = true);

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
    DLL virtual nNode* findNode(nNode *pNode);

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
    DLL virtual nNode* findNode(nNode *pNode, bool searchChildren);

    /**
     * In findnode we were calling getNextSibling and occassionally hitting an nDataStreamNode.  We needed to then step
     * over this node and get the next sibling.  This method allows you to specify an offset i.e 1 means get sibling after
     * next
     *
     * @param idx offset
     * @return the sibling node for the given index
     */
    virtual nNode* getNextSibling(int idx=0);

    /**
     * Returns the total number of nodes within this container and all subsequent children by traversing the entire structure beneath this container node
     *
     * @return the total number of nodes counted beneath this container and it's children
     */
    virtual int getTotalNodes();

    /**
     * Changes the entire ACL entries for the selected nodes with the new ACL passed in
     *
     * @param pAcl         An nACL containing the nAclEntry objects that will be applied to all nodes under the container
     * @param allChannels if set then all channels within the container will have the acl added
     * @param allQueues   if set then all queues within the container will have the acl added
     * @param allServices if set then all services within the container will have the acl added
     * @exception nInsufficientPrivilegesException
     *                             If the user is not permissioned to perform this operation
     * @exception nNodeException      if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    virtual void setACL(nACL *pAcl, bool allChannels = true, bool allQueues = true, bool allServices = true);

  protected:
    nContainer(const std::string& name, nNode *pParent);

    virtual void handleDisconnect();
    virtual void handleReconnect();
    virtual void addNode(nNode *pNode);
    virtual void delNode(nNode *pNode);
    virtual nNode* parseName(std::string name, nSecureChannel *pNsl);
    virtual nNode* parseName (std::string name, nContainer *pRealm);
    virtual nNode* parseName(nDataGroup *anode);
    virtual nNode* parseName(std::list<nDataGroup*>* groups);
    virtual int getSize();

    fSortedList<std::string, nNode*> m_nodes;
    Poco::Mutex m_nodeMutex;

    static const std::string slash;
    static const std::string empty;

  private:
    std::string* createNodeList(nNode **ppNodes, int numNode);
    nRealmNode* getRealmNode();
    fAclEntry** createAclList(nACL *pAcl, int& numEntry);
    nNode* findNode(nNode *pFind, nNode *pFrom);

    friend class nRealmNode;
    friend class nPkgAdminListener;
    friend class nPkgValidateNamespace;
    friend class nClusterNode;
    friend class nPkgDataGroupListener;
    friend class nDataGroupsContainer;
    friend class nDataGroupNode;
};

}
}
}
}
