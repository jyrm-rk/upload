/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nNode;
/**
 * All classes that can be joined from one part of the namespace to another implement
 * this interface. This allows easy manipulation of the nirvana namespace objects that
 * can be joined together i.e. channels
 */
class nJoinable {
  public:
    nJoinable(void);
    virtual ~nJoinable(void);


    /**
     * This method enables the joining of the object from one node to another, specifying a
     * selector, and a maximum hop count for the events
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
     *
     * @see nLeafNode
     */
    virtual void join(nNode *pToNode, bool bIsRouted, int hopcount, const std::string& selector) = 0;

    /**
     * This method enables the joining of the object from one node to another, specifying a
     * selector, and a maximum hop count for the events
     *
     * @param *pToNode the nNode object to join this node to
     * @param bIsRouted Reserved for future use.
     * @param hopcount if an event is published directly to this node (i.e. does not
     * arrive here through another join), this is the maximum number of hops it will follow
     * @param selector a message selector specifying a filter for this message route
     * @param allowPurge specifies whether the join will permit purges to be propagated to all subsequent channels in the join path
     *
     * @exception nUnsupportedJoinException thrown if join is not supported (e.g. on queues)
     * @exception nBaseAdminException is thrown if the join creation fails
     *
     *
     * @see nLeafNode
     */
    virtual void join(nNode *pToNode, bool bIsRouted, int hopcount, const std::string& selector, bool allowPurge) = 0;

    /**
     * This method enables the joining of the object from one node to another, specifying a
     * selector for filtered joins
     *
     * @param *pToNode the nNode object to join this node to
     * @param selector a message selector specifying a filter for this message route
     *
     * @exception nUnsupportedJoinException thrown if join is not supported (e.g. on queues)
     * @exception nBaseAdminException is thrown if the join creation fails
     *
     * @see nLeafNode
     */
    virtual void join(nNode *pToNode, const std::string& selector) = 0;
};

}
}
}
}
