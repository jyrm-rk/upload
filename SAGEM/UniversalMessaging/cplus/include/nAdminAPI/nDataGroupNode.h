/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NDATAGROUPNODE
#define NDATAGROUPNODE

#include "nContainer.h"
#include "nDataGroup.h"
#include "nDataGroupListener.h"
#include "nDataGroupStatus.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
class nDataGroupsContainer;

using namespace foundation::fbase;
using namespace client;
using namespace nbase;

/**
* This class is an Admin API wrapper for a Data Group object (nDataGroup)
*
* @see nDataGroup
*/
class nDataGroupNode : public nContainer {
  public:

    ~nDataGroupNode();

    /**
    *  Add an nDataGroup listener to this node. This allows multiple listeners to be added
    * to an instance of the nDataGroup object this node represents
    * @param listener the nDataGroupListener to receive callbacks when
    * streams or other groups are added/removed from this group
    * @see com.pcbsys.nirvana.client.nDataGroupListener
    */
    void addListener(nDataGroupListener* listener);

    /**
    *  Remove the specified listener
    * @param listener the nDataGroupListener to receive callbacks when
    * streams or other groups are added/removed from this group
    * @see com.pcbsys.nirvana.client.nDataGroupListener
    */
    void removeListener(nDataGroupListener* listener);

    /**
    *  Get the client API nDataGroup object represented by this node
    * @return  the nDataGroup object
    */
    nDataGroup* getDataGroup();

    /**
    *  Returns the last EID that was used for the data group
    *
    * @return  long the last event id used
    */
    longlong getLastEID();

    /**
    *  Returns the total number of streams that have been connected to this data group
    *
    * @return  long total number of streams
    */
    longlong getTotalStreamCount();

    longlong _getTotalStreamCount();

    /**
    *  Returns the current number of streams that are connected to this data group
    *
    * @return  long total number of streams
    */
    longlong getStreamCount();

    longlong _getStreamCount();

    /**
    *  Returns the total number of events that this data group and nested groups have delivered to listeners
    *
    * @return  long total number of events consumed
    */
    longlong getTotalConsumed();

    longlong _getTotalConsumed();

    /**
    *  Returns the total number of events published to this data group and nested groups since the realm has started
    *
    * @return  long total number of events written
    */
    longlong getTotalPublished();

    longlong _getTotalPublished();

    /**
    *  The number of events published per second
    *
    * @return  int event publish rate
    */
    float getPublishRate();

    /**
    *  The total number of milliseconds it takes to fanout each event to all consumers
    *
    * @return  long the fanout time in milliseconds
    */
    float getFanoutTime();

    /**
    *  The number of events consumed per second
    *
    * @return  float value the rate at which messages are being consumed
    */
    float getConsumedRate();

    nDataGroupNode(nDataGroup* group, nDataGroupsContainer* node);

    nDataGroupNode(nDataGroup* group, nDataGroupNode* node);

    virtual int getType();

  protected:
    nDataGroup* myGroup;
    std::list<nDataGroupListener*> myListeners;

    float _getConsumedRate();
    float _getPublishRate();

    void statusUpdate(nDataGroupStatus* status);
    virtual int compare(nNode *pItem);
    virtual int compare(const std::string& item);

  private:

    longlong myLastEID;

    longlong myTotalStreams;
    longlong myCurrentStreams;
    longlong myTotalConsumed;
    longlong myTotalPublished;
    longlong myFanoutLatency;

    int myConsumedRate;
    int myPublishRate;

    longlong myLastUpdate;
    longlong myLastNullUpdate;

    friend class nPkgDataGroupListener;
    friend class DataGroupStatusHandler;
};
}
}
}
}
#endif
