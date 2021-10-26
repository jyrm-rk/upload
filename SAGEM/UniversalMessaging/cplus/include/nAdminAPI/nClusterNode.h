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
#include "nPkgCloseListener.h"
#include "fSortedList.h"

#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nSessionAttributes;
}
namespace nAdmin {
class nLatticeMember;
class nConnectionListener;
namespace events {
class nClusterRequest;
}
}
namespace nAdminAPI {

class nClusterEventListener;
class nRealmNode;
class nClusterStatus;
class nClusterSite;
class nPkgClusterIndex;
class nClusterConnectionListener;
class nClusterMemberConfiguration;
class nClusterConversionStatus;
class ClusterNodeConnectionListener;
class nLogListener;
class nAPIConnectionListener;
class nLeafNode;

using namespace nAdmin;
using namespace nAdmin::events;
using namespace foundation::collections;
using namespace client;

/**
 * Contains the status and configuration of a Nirvana cluster.
 * <p/>
 * Each Nirvana cluster is made up of multiple Nirvana Realm servers and this group is given a name, the Cluster Name.
 * The class supplies helper functions to query, create and delete clusters.
 */
class nClusterNode :
    public nContainer {
  public:
    /**
     * Constructs a new nClusterNode
     */
    nClusterNode(void);
    nClusterNode(nClusterRequest *pReq);
    virtual ~nClusterNode(void);

    virtual void closed(nRealmNode *pNode);

    /**
     * Returns an iterator of nClusterSite objects
     *
     * @param site site name.
     *
     * @return nClusterSite object for specified site.
     */
    nClusterSite* getSite(const std::string& site);


    /**
     * Returns the nClusterNode for the specified clusterName.
     *
     * @param clusterName name of the cluster to lookup as a string.
     * @return nClusterNode or null if no such cluster is found.
     */
    static nClusterNode* find(const std::string& clusterName);

    /**
     * Returns the type of node that this object represents.
     * @return the type of this node
     */
    virtual int getType();

    /**
     * Returns the current master of the cluster.
     *
     * @param timeout the amount of time in milliseconds to wait for the connection to the master
     *
     * @return nRealmNode of the master.
     */
    nRealmNode* getMaster();

    /**
     * Adds a nClusterConnectionListener to the cluster to receive callbacks as connections are made or lost to
     * any realms within the cluster.
     *
     * @param pListener to register for callbacks.
     */
    void addConnectionListener(nClusterConnectionListener *pListener);

    /**
     * Adds a nConnectionListener to each nLeaNode of each nRealmNode in the cluster
     *
     * @param pListener to register for callbacks.
     */
    void addConnectionListenerToAllLeafNodes(nAPIConnectionListener *pListener);

    /**
     * Adds a nClusterEventListener to the cluster to receive callbacks as the state of the cluster changes.
     *
     * @param pListener to register for callbacks.
     */
    void addListener(nClusterEventListener *pListener);

    /**
     * Adds a new node to an existing cluster.
     *
     * @param pNode details about the new node to add.
     * @exception nSessionNotConnectedException if unable to connect to the new node.
     * @exception nRequestTimedOutException     if the node fails to respond within the timout period.
     * @exception nSecurityException            if the client has no administration priviliges on the node.
     * @exception nBaseClientException          if any unexpected exceptions are raised.
     */
    void addMember(nClusterMemberConfiguration *pNode);

    /**
     * Tests to see if the supplied node can be master of the cluster.
     *
     * @param pNode to test.
     * @return true if the node is defined as able to be master.
     * @exception nSecurityException   if the client is not authorized.
     * @exception nBaseClientException if the node is not connected.
     */
    bool canBeMaster(nRealmNode *pNode);

    /**
     * Closes connections to all realms for the specified Nirvana Realm server.
     */
    void close();

    /**
     * Removes a nClusterConnectionListener from the cluster
     *
     * @param pListener to register for callbacks.
     */
    void delConnectionListener(nClusterConnectionListener *pListener);

    /**
     * Removes the specified realm from the cluster.
     *
     * The cluster must be running and all members of the cluster online for this to work correctly.
     *
     * @param pNode        to remove from the cluster.
     * @param deleteStore flag to indicate that the call should also delete ALL cluster stores
     * @exception nBaseClientException          if any nodes fail during the process.
     * @exception nSessionNotConnectedException if any of the nodes are not connected.
     * @exception nSecurityException            if the client is not authorised.
     */
    void deleteMember(nRealmNode *pNode, bool deleteStore = false);

    /**
     * Method that allows you to delete a site
     *
     * @param pSite the cluster site to delete
     * @exception Exception if the site was not able to be created
     */
    void deleteSite(nClusterSite *pSite);

    /**
     * Deregisters a nClusterEventListener from the cluster for callbacks.
     *
     * @param pListener to be removed.
     */
    void delListener(nClusterEventListener *pListener);

    /**
     * Deletes the cluster and removes all known realms from the cluster.
     *
     * @param deleteStore flag to indicate that the call should also delete ALL cluster stores
     * @exception nBaseClientException          if any nodes fail during the process.
     * @exception nSessionNotConnectedException if any of the nodes are not connected.
     * @exception nSecurityException            if the client is not authorised.
     */
    void destroy(bool deleteStore = false);

    /**
     * Adds the realm nodes in the remoteCluster node to this clusterNode, creating a logical connection between them.
     *
     * @param remoteCluster nClusterNode containing the remote cluster node to add to this cluster node
     * @exception Exception If the remoteCluster is null, or if this cluster is the same as remoteCluster.
     */
    DLL void registerRemoteCluster(nClusterNode* remoteCluster);

    /**
     * Removes the remote node given by the parameter remoteCluster from this cluster node.
     *
     * If the remoteCluster is null, or remoteCluster is the same as this cluster node, this method will throw an Exception.
     *
     * @param remoteCluster The remoteCluster to remove from this cluster nodes realm list.
     * @exception Exception If remoteCluster is null, or is the same as this cluster node.
     */
    DLL void deregisterRemoteCluster(nClusterNode* remoteCluster);

    /**
     * Joins the stores between two different clusters together.
     *
     * Additional parameters specify whether events will be routed, the maximum number of hop counts for events to pass through this join, a selector, and whether or not to allow purging.
     * @param source The source leaf node for this join
     * @param destination The destination leaf node for this join
     * @param isRouted boolean which determines if events will be routed
     * @param hopCount integer specifying the maximum hop count that events may have to pass through this join
     * @param selector a selector which filters events over this join
     * @param allowPurge boolean to allow purging of events over this join
     * @exception Exception If source or destination are null, an exception will be thrown. If source or destination are not cluster wide channels/queues, an exception will be thrown. If source and destination reside on the same cluster, an exception will be thrown.
     */
    DLL void joinRemoteClusterStore(nLeafNode* source, nLeafNode* destination, bool isRouted, int hopCount, std::string selector, bool allowPurge );

    /**
     * Returns a list of nClusterStatus which contains the current cluster status.
     *
     * @return list of nClusterStatus.
     */
    std::list<nClusterStatus*>& getClusterConnectionStatus();

    /**
     * Returns the current master of the cluster.
     *
     * @param timeout the amount of time in milliseconds to wait for the connection to the master
     * @return String name of the master.
     */
    nRealmNode* getMaster(long timeout);

    /**
     * Returns the number of defined nClusterSite objects
     *
     * @return a count of  nClusterSite objects
     * @see nClusterSite
     */
    int getNoOfSites();

    /**
     * Returns a list of nClusterSite objects
     *
     * @return a list of  nClusterSite objects
     * @see nClusterSite
     */
    fSortedList<std::string, nClusterSite*>& getSites();

    /**
     * Tests to see if the supplied node is part of the cluster.
     *
     * @param pNode to test.
     * @return true if the node is defined in the cluster else false.
     * @exception nSecurityException   if the client is not authorized.
     * @exception nBaseClientException if the node is not connected.
     */
    bool hasMember(nRealmNode *pNode);

    /**
     * Tests to see if the supplied realm name is part of the cluster.
     *
     * @param realm name to test.
     * @return true if the realm is defined in the cluster else false.
     * @exception nBaseClientException if the node is not connected.
     */
    bool hasMember(const std::string& realm);

    /**
     * Tests to see if the cluster has quorum and is functioning. Quorin is defined as the cluster having the
     * ( number of realms ) / 2 +1 being online.
     *
     * @return boolean indicating the current state.
     */
    bool hasquorum();

    /**
     * Returns true if the cluster uses sites.
     */
    bool hasSites();

    /**
     * Modifies the specified realm in the cluster as far as the CanBeMaster flag.
     *
     * The cluster must be running and all members of the cluster online for this to work correctly.
     *
     * @param pConfig The ClusterMemberConfiguration object refering to the node and configuration
     * @exception nBaseClientException          if any nodes fail during the process.
     * @exception nSessionNotConnectedException if any of the nodes are not connected.
     * @exception nSecurityException            if the client is not authorised.
     */
    void modifyMember(nClusterMemberConfiguration *pConfig);


    /**
     * Creates an instance of a nClusterNode for any cluster found on the realm specified by the nSessionAttributes.
     *
     * @param pAttr Session attributes to connect to the remote Nirvana Realm
     * @return If any cluster has been defined on the specified realm, will return the nClusterNode relevant.
     * @exception nBaseAdminException if unable to connect to the remote realm
     */
    static nClusterNode* getInstance(nSessionAttributes *pAttr);

    /**
     * Creates an instance of a nClusterNode for any cluster found on the realm specified by the nSessionAttributes and the username.
     *
     * @param pAttr     Session attributes to connect to the remote Nirvana Realm
     * @param username to use to authenticate
     * @return If any cluster has been defined on the specified realm, will return the nClusterNode relevant.
     * @exception nBaseAdminException if unable to connect to the remote realm
     */
    static nClusterNode* getInstance(nSessionAttributes *pAttr, const std::string& username);

    /**
     * Creates an instance of a nClusterNode for any cluster found on the realm specified by the rname.
     *
     * @param rname Nirvana Realm server URL
     * @return If any cluster has been defined on the specified realm, will return the nClusterNode relevant.
     * @exception nBaseAdminException       if the user has no administration priviliges
     * @exception nIllegalArgumentException if the rname is not valid
     */
    static nClusterNode* getInstance(std::string& rname);

    /**
     * Return a list of nCluster nodes.
     *
     * @return list of nodes.
     */
    static std::list<nClusterNode*>* getKnownClusters();

  protected:
    void setMaster(const std::string& name);
    void statusUpdate(nLatticeMember *pLm);
    void setState(const std::string& source, const std::string& state);
    nClusterStatus* findStatus(const std::string& realm);
    void updateClusterState();
    void sendSiteUpdates(nClusterRequest *pCr);
    virtual void addNode(nNode *pNode);
    virtual void delNode(nNode *pNode);
    void configUpdate(nClusterRequest *pCfg);
    nClusterSite* createSite(const std::string& name, const std::string& initialRealm);
    void reportToListeners(const std::string& source, const std::string& message);

    static nClusterNode* registerCluster(nClusterRequest *pReq);
    static nClusterNode* create(const std::string& clusterName,
                                nClusterMemberConfiguration **ppRealms, int numRealm,
                                bool bConvertLocal = false, nClusterConversionStatus *pCallback = NULL);

  private:
    nClusterSite* updateSite(const std::string& siteName, const std::string& nodeName, bool isPrime);
    void closeRemoteSessions(fSortedList<std::string, nNode*>& nodes);

    std::list<nClusterEventListener*> m_listeners;
    std::list<nClusterConnectionListener*> m_clusterConnectionListeners;
    std::list<nClusterStatus*> m_status;
    fSortedList<std::string, nClusterSite*> m_sites;
    nRealmNode *m_pMaster;
    ClusterNodeConnectionListener *m_pConListener;
    nLogListener *m_pLogListener;

    static fSortedList<std::string, nPkgClusterIndex*> m_clusters;
    static Poco::Mutex m_clusterMutex;

    static Poco::Mutex m_registerMutex;
    Poco::Mutex m_configUpdateMutex;
    Poco::Mutex m_updateSiteMutex;

    friend class nPkgAdminListener;
    friend class nClusterSite;
    friend class nRealmNode;
    friend class ClusterNodeConnectionListener;
    friend class nPkgClusterLogHandler;
};

}
}
}
}
