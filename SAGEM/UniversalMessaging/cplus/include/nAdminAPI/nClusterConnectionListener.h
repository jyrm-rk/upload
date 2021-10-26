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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;
class nConnectionDetails;

/**
 * Any class that extends this class can be registered against a Nirvana Cluster node to receive
 * notification when remote connections are made or dropped on any of the cluster realm node objects.
 */
class nClusterConnectionListener {
  public:
    DLL nClusterConnectionListener(void);
    virtual DLL ~nClusterConnectionListener(void);

   /**
    * This method is asynchronously called when a connection is established with a realm in the cluster.
    *
    * @param details The nConnectionDetails object that contains all the information about the connection added
    * @param realm The nRealmNode object that the connection was made to
    * @see com.pcbsys.nirvana.nAdminAPI.nConnectionDetails
    * @see com.pcbsys.nirvana.nAdminAPI.nRealmNode
    */
    virtual DLL void add(nRealmNode *pRealm, nConnectionDetails *pDetails) = 0;

    /**
     * This method is asynchronously called when the connection is lost or is no longer required on a realm within a cluster.
     *
     * @param details The nConnectionDetails object that contains all the information about the connection deleted
     * @param realm The nRealmNode object that the connection was lost from
     * @see com.pcbsys.nirvana.nAdminAPI.nConnectionDetails
     * @see com.pcbsys.nirvana.nAdminAPI.nRealmNode
     */
    virtual DLL void del(nRealmNode *pRealm, nConnectionDetails *pDetails) = 0;
};

}
}
}
}
