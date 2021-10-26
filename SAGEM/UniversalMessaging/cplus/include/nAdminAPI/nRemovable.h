/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

/**
 * All classes that can be removed from the namespace implement
 * this interface. This allows easy manipulation of the nirvana namespace objects that
 * can be deleted
 */
class nRemovable {
  public:
    nRemovable(void);
    virtual ~nRemovable(void);

    /**
     * This method enables the removal of the object from the namespace.
     * If you specify true, all child nodes, including channels, queues and services
     * will also be removed
     *
     * @param removeChildren a bool specifying whether siblings should be removed too
     *
     * @exception nUnsupportedRemoveException thrown if the remove operation is not supported on this node
     * @exception nNodeException is thrown if an error occurs in the remove operation
     *
     * @see nLeafNode
     * @see nRealmNode
     * @see nLinkNode
     */
    virtual void remove(bool removeChildren) = 0;

};

}
}
}
}
