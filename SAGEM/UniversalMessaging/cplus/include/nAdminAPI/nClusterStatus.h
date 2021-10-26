/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {
class nLatticeMember;
}
namespace nAdminAPI {

class nClusterSite;
class nClusterStatusEntry;

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::nirvana::nAdmin;

/**
 * This class contains the status of the of a realm within the cluster, What state it has, which node is the elected master etc.
 */
class nClusterStatus :
    public Observable {
  public:

    /**
     * Creates a new nClusterStatus Object for the specified realm
     * @param name the string name of the cluster
     */
    nClusterStatus(const std::string& name);
    virtual ~nClusterStatus(void);

    /**
     * The name of the realm which these status's are related to.
     *
     * @return the name of the realm.
     */
    virtual const std::string& getName();

    /**
     * The name of the nodes elected master.
     *
     * @return  the elected master's name as a string
     */
    virtual const std::string& getElectedMaster();

    /**
     * Indicates whether the cluster member can be selected as master within the cluster.
     *
     * @return whether the member can be elected master
     */
    virtual bool canBeMaster();

    /**
     * Returns the realms cluster state.
     *
     * @return String representing the current state of this node within the cluster.
     */
    virtual std::string getState();

    /**
     * Returns nClusterStatusEntry for the realm at the index specified
     *
     * @param idx to get the status for.
     * @return status object at the requested index.
     */
    virtual nClusterStatusEntry* getStatus(int idx);

    /**
     * Returns nClusterStatusEntry for the specified realm.
     *
     * @param realm name to get status for.
     * @return status for specified realm.
     */
    virtual nClusterStatusEntry* getStatus(const std::string& realm);

    /**
     * The number of known nodes within the cluster.
     *
     * @return number of nodes within the cluster.
     */
    virtual int size();

  protected:
    virtual void statusUpdate(nLatticeMember *pLm, nClusterSite *pSite);
    virtual nClusterStatusEntry* find(const std::string& realm);
    virtual void addMember(const std::string& name);
    virtual void delMember(const std::string& name);
    virtual void setSite(nClusterSite *pSite);

    nClusterSite* m_pSite;

  private:
    std::string m_electedMaster;
    bool m_bCanBeMaster;
    int m_state;
    std::list<nClusterStatusEntry*> m_connections;
    std::string m_realmName;

    friend class nClusterNode;
};

}
}
}
}
