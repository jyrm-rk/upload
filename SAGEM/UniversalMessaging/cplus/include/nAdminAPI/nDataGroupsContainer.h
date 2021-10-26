/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NDATAGROUPSCONTAINER
#define NDATAGROUPSCONTAINER

#include "nContainer.h"
#include "nDataGroupNode.h"
#include "nDataStream.h"
#include "nDataGroup.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
class nContainer;
class nDataGroupNode;
class nRealmNode;
using namespace com::pcbsys::nirvana::client;

/**
* This class is an Admin API wrapper for all configured Data Group objects (nDataGroup)
*This class also can also be used to obtain all known nDataStream objects,
*that have been added to the default data group.
*
* @see com.pcbsys.nirvana.client.nDataGroup
* @see com.pcbsys.nirvana.client.nDataStream
*/
class nDataGroupsContainer : public nContainer {
  public:
    /**
    * Obtain the default nDataGroup object
    * @return  default nDataGroup
    */
    nDataGroupNode* getDefaulDataGroup();

    /**
    * Get the current number of nDataStream objects connected.
    *
    * @return  the current number of connected nDataStream objects
    */
    int getStreamCount();

    /**
    * Get the number of known nDataGroup objects.
    *
    * @return  the total number of nDataGroup objects
    */
    int getGroupCount();

    /**
    * The number of events consumed per second across all nDataGroup objects
    *
    * @return  the rate at which events are being consumed
    */
    float getConsumedRate();

    /**
    * The number of events published per second across all nDataGroup objects
    *
    * @return  the rate at which events are being written to the groups
    */
    float getPublishRate();

    /**
    * Returns the total number of events published to this all data groups since the realm has started
    *
    * @return  total number of events published since the realm started
    */
    longlong getTotalPublished();

    /**
    * Returns the total number of events that delivered to listeners across all nDataGroup objects
    *
    * @return  total number of events consumed since the realm started
    */
    longlong getTotalConsumed();

    /**
    * Returns the total number of streams that have been added to all data groups since the realm last started
    *
    * @return  total number of streams
    */
    longlong getTotalStreamCount();

    /**
    * Get all nDataStream objects connected to the Nirvana realm
    * @return  an IEnumerable of all nDataStream objects
    */
    std::list<nDataStream*>* getAllStreams();

    /**
     * This method will return a matching nDataGroupNode if one exists
     *
     * @param name the name of the node to locate as a String
     * @return the matching nDataGroupNode or null if it does not exist
     * @throws nAdminIllegalArgumentException
     */
    virtual nNode* findNode(const std::string name);
    using nContainer::findNode;

  protected:
    nRealmNode* myRealm;

    nDataGroupsContainer(std::list<nDataGroup*> groups, nRealmNode* node);
    nDataGroupsContainer(nDataGroup** groups, int numGroups, nRealmNode* node);

  private:
    friend class nContainer;

};
}
}
}
}

#endif
