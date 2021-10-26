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
#include "fBase.h"

#include <list>
#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace foundation::fbase;

class nClusterNode;
/**
 * This class defines a collection of realms within a cluster into a physical site / location.
 * <p>
 * A site can be given prime status, which means that in failover with 2 sites defined, the prime site will receive and additional vote enabling the remaining cluster realms to achieve quorum
 */
class nClusterSite : public CountableObject {
  public:

    /**
     * Creates a new site with a given name within the supplied owning cluster
     * @param name name of the site
     * @param *pOwningCluster the nClusterNode of the owning cluster
     * @return true / false whether the realm is a member
     */
    nClusterSite(const std::string& name, nClusterNode *pOwningCluster);
    virtual ~nClusterSite(void);

    /**
     * Check if a realm is a member of this site
     * @param name string of the realm to check
     * @return true / false whether the realm is a member
     */
    virtual bool isMember(const std::string& name);

    /**
     * Find a specific member realm in this site
     *
     * @param name name string of the realm you wish to find in the members
     * @return the name string of the realm or null if not found
     */
    virtual std::string findNode(const std::string& name);

    /**
     * Remove a realm as a member of a site
     * @param realmName the realm name to delete from the site as a string
     * @throws Exception if the operation could not be completed
     */
    virtual void delMember(const std::string& realmName);

    /**
     * Get the name of the defined cluster site
     * @return the cluster site name
     */
    virtual const std::string& getName ();

    /**
     * Sets whether this site is defined as prime
     * @param flag whether the site is prime
     * @throws Exception if the operation could not be completed
     */
    virtual void setPrime(bool flag);

    /**
     * Add a realm to this site
     * @param name name of the realm to be added
     */
    virtual void addMember(const std::string& name);

    /**
     * Returns a list of known site member realm names
     * @return iterator of site member realm names
     */
    virtual std::list<std::string>& getMembers();

    /**
     * Return the number of members defined in this site
     *
     * @return The number of site members
     */
    virtual int getNoOfMembers();

    /**
     * Returns if the defined site is regarded as prime
     *
     * @return true if prime
     */
    virtual bool isPrime();

  protected:
    virtual void updateMembers(const std::string& name);

    bool m_bPrime;
    std::string m_name;
    nClusterNode *m_pClusterNode;
    std::list<std::string> m_nodes;

  private:
    void addNode(const std::string& name);
    void delNode(const std::string& name);

    friend class nClusterNode;
};

}
}
}
}
