/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nPkgCloseListener.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nSessionAttributes;
}
namespace nAdminAPI {

class nRealmNode;

using namespace client;

/**
 * This object is used to create/modify clusters.
 * It contains the relevant information regarding a specific node
 * to be added to the cluster.
 */
class nClusterMemberConfiguration :
    public nPkgCloseListener {
  public:
    /**
     * Constructor using an existing nRealmNode.
     * @param realmNode realm node object connected to the node to be added.
     * @param canBeMaster boolean if this node can be a master within the cluster.
     */
    nClusterMemberConfiguration(nRealmNode *pRealmNode, bool bCanBeMaster = true);

    /**
     * Constructor using the nSessionAttributes to connect to the Nirvana Realm Server.
     *
     * @param sessionAttributes details of the server to connect to.
     * @param canBeMaster       boolean if this node can be a master within the cluster.
     * @throws nBaseAdminException if unable to connect to the specified realm.
     */
    nClusterMemberConfiguration(nSessionAttributes *pSessionAttributes, bool bCanBeMaster = true);

    /**
     * Constructor using the nSessionAttributes to connect to the Nirvana Realm Server.
     *
     * @param sessionAttributes details of the server to connect to.
     * @param canBeMaster       boolean if this node can be a master within the cluster.
     * @param username          to use to connect to the remote realm with.
     * @throws nBaseAdminException if unable to connect to the specified realm.
     */
    nClusterMemberConfiguration(nSessionAttributes *pSessionAttributes, bool bCanBeMaster, const std::string& username);

    /**
     * Constructor using the nSessionAttributes to connect to the Nirvana Realm Server.
     *
     * @param rname			details of the server to connect to.
     * @param canBeMaster   boolean if this node can be a master within the cluster.
     * @throws nBaseAdminException if unable to connect to the specified realm.
     */
    nClusterMemberConfiguration(const std::string& rname, bool bCanBeMaster = true);

    /**
     * Constructor using a Nirvana Realm URL to connect to the Nirvana Realm server.
     *
     * @param rname       to connect to.
     * @param canBeMaster boolean if this node can be a master within the cluster.
     * @param username    to use to connect to the remote realm with.
     * @throws nIllegalArgumentException if the rname is not valid.
     * @throws nBaseAdminException       if unable to connect to the specified realm.
     */
    nClusterMemberConfiguration(const std::string& rname, bool bCanBeMaster, const std::string& username);
    virtual ~nClusterMemberConfiguration(void);

    /**
     * Called when a realm node is closed, for internal use only
     * @param *pNode the node which has been closed
     */
    virtual void closed(nRealmNode *pNode);

  protected:
    virtual void close();

    /**
     * Returns the nRealmNode object of the Nirvana Server.
     * @return nRealmNode object.
     */
    virtual nRealmNode* getNode();

  private:
    virtual bool canBeMaster();

    nRealmNode *m_pNode;
    bool m_bCanBeMaster;
    bool m_bCreated;

    friend class nRealmNode;
    friend class nClusterNode;
};

}
}
}
}
