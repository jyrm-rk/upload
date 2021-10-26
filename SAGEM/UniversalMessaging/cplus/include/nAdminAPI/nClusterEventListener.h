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

class nRealmNode;
class nClusterStatus;

/**
 * Interface allowing client applications to receive cluster specific callbacks.
 */
class nClusterEventListener {
  public:

    /**
     * Called with a new Nirvana Realm is added to the cluster.
     *
     * @param pNode *nRealmNode object of the added realm.
     */
    virtual void memberAdded(nRealmNode *pNode) = 0;

    /**
     * Called when a Nirvana Realm is deleted from the cluster.
     *
     * @param pNode *nRealmNode object of the deleted realm.
     */
    virtual void memberDeleted(nRealmNode *pNode) = 0;

    /**
     * Called when the cluster achieves quorum.
     *
     * @param pMasterNode *nRealmNode of the master node for the cluster.
     */
    virtual void quorumReached(nRealmNode *pMasterNode) = 0;

    /**
     * Called when the cluster has lost quorum.
     */
    virtual void quorumLost() = 0;

    /**
     * Called when a Cluster status has changed.
     *
     * @param pUpdate *nClusterStatus object containing the changes to the cluster.
     */
    virtual void statusUpdate(nClusterStatus *pUpdate) = 0;

    /**
     * Called when a member of the cluster changes state.
     *
     * @param pNode of the realm within the cluster.
     * @param newState new state that the node has achieved as a string.
     */
    virtual void stateChange(nRealmNode *pNode, const std::string& newState) = 0;

    /**
     * Called when cluster log events are received.
     *
     * @param source Realm server where the log event came from.
     * @param message Cluster message text.
     */
    virtual void report(const std::string& source, const std::string& message) = 0;
};

}
}
}
}
