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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::fbase;

/**
 * This class contains the online/offline status for a realm within a cluster
 */
class nClusterStatusEntry :
    public Observable {
  public:
    virtual ~nClusterStatusEntry(void);

    /**
     * The realm name which this status belongs to
     *
     * @return Realm name
     */
    virtual const std::string& getName();

    /**
     * Return the status of the realms online/offline
     *
     * @return bool indicating if the realm is online
     */
    virtual bool isOnline();

  protected:
    /**
     * Creates a new nClusterStatusEntry for the specified name
     *
     * @param name the string name of the realm within the cluster
     * @param bool the boolean status of the realm true/false(online/offline)
     */
    nClusterStatusEntry(const std::string& name, bool conState);

    /**
     * set the Boolean indicating if the realm is online or offline
     *
     * @param newState bool indicating if the realm is online
     */
    virtual void setState(bool newState);

  private:
    std::string m_realmName;
    bool m_connectionState;

    friend class nClusterStatus;
};

}
}
}
}
