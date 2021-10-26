/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nContainer.h"
#include "nRemovable.h"
#include "nPkgCloseListener.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;


/**
 * Since the Nirvana namespace can contain multiple links to Nirvana Realm servers at
 * different parts of the namespace, including namespace loops, this node represents
 * a RealmServer which has been mounted elsewhere in the namespace. It is basically
 * a placeholder within the namespace and can be used by the application to stop looping
 * through the namespace and to render the node differently or perhaps display a link
 * between this node and the other nRealmNode.
 *
 * @see nRealmNode
 */
class nLinkNode :
    public nContainer, public nRemovable {
  public:
    /**
     * Construct a new nLinkNode
     * @param *pNode the actual realm node to be added
     * @param *pParent the parent of this node
     * @param mntPnt the mount point for this node
     */
    nLinkNode(nRealmNode *pNode, nNode *pParent, const std::string& mntPnt);
    virtual ~nLinkNode(void);

    /**
     * Returns true if the node is removable
     * @return true if the node is removable, false otherwise
     */
    virtual bool IsRemovable();
    /**
     * Returns the type of this object, for internal use only
     * @return the type of the object
     */
    virtual int getType();

    /**
     * Returns the actual nRealmNode to the application
     *
     * @see nRealmNode
     * @return nRealmNode object of the real Realm Server
     */
    virtual nRealmNode* getRealmNode();

    /**
     * This method enables the removal of the object from the namespace, in this case an nRealmNode from
     * the namespace.
     * If you specify true, all child nodes, including channels, queues and services
     * will also be removed from the realm before removing it from its parent
     *
     * @param removeChildren a boolean specifying whether siblings should be removed too
     *
     * @exception nUnsupportedRemoveException thrown if remove is not supported (e.g. on the namespace root Realm)
     * @exception nNodeException is thrown if an error occurs in the remove operation
     *
     * @see nLeafNode
     * @see nRealmNode
     */
    virtual void remove(bool removeChildren);
    virtual void closed(nRealmNode *pNode);

  protected:
    virtual void close();

    nRealmNode *m_pActualNode;
    std::string m_mountPoint;

    friend class nRealmNode;
};

}
}
}
}
