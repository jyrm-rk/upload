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

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nLeafNode;

using namespace com::pcbsys::foundation::fbase;


/**
 * This class contains information about a join between two channels. There is
 * a nJoinDetails for both sides of a join. On a channel which sends the events
 * this is known as a source channel and this class will return true to isSource()
 * function.
 *
 * The source can also have a selector associated with it while the channel
 * receiving the events, the destination, has no selector associated with it.
 *
 */
class nJoinDetails :
    public Observable {
  public:
    /**
     * Constructor for nJoinDetails
     * @param *pChannel the nLeafNode
     * @param selector the string selector used on the join
     * @param source a boolean indicating if this is the source
     * @param hopCount the int hopcount used for the join
     * @param allowPurge bool indicating if purge is allowed
     * @param archive bool indicating if this is an archive join
     *
     * @return nLeafNode remote channel / queue
     */
    nJoinDetails(nLeafNode *pChannel, const std::string& selector, bool source, int hopCount, bool allowPurge, bool archive);
    virtual ~nJoinDetails(void);

    /**
     * Returns the nLeafNode of the remote end of the join, if this is a source join then this returns
     * the destination else it returns the source.
     *
     * @return nLeafNode remote channel / queue
     */
    virtual nLeafNode* getRemoteNode();

    /**
     * Return whether purge requests are permitted in this join. When you purge an event from a channel, you can specify whether to purge from any subsequent joined channels, like a cascade deletion.
     * If this flag is set to true, any purge requests from the source channel to the destination channel / queue will be enforced. If false, purge requests will not be enforced on the destination channel / queue.
     * @return whether purge requests are honoured
     */
    virtual bool allowPurgeRequests();

    /**
     * Returns the number of times an event will be passed over a join. Useful if you wish to limit the
     * number of time an event is sent over the network.
     *
     * @return int hop count
     */
    virtual int getHopCount();

    /**
     * Returns the last Event ID sent to the remote join
     *
     * @return long eid
     */
    virtual longlong getLastEID();

    /**
     * Returns the selector used for the join. This is only applicable if the join is the source
     * since the destination side of a join is not informed of the selector
     *
     * @return String selector
     */
    virtual const std::string& getSelector();

    /**
     * Returns true if this join is an archival join
     *
     * @return boolean is archival
     */
    bool isArchival();

    /**
     * Returns a boolean flag representive of whether the channel is the source side of the join
     *
     * @return boolean flag indicating if the channel to which the join details belongs is the source channel for the join
     */
    bool isSource();

  protected:
    virtual void update(longlong eid);

  private:
    nLeafNode* m_pChannel;
    std::string m_selector;
    bool m_bSource;
    int m_hopCount;
    bool m_bAllowPurgeRequests;
    bool m_bArchive;
    longlong m_lastEID;

    friend class nLeafNode;
};

}
}
}
}
