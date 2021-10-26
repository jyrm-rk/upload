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

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace com::pcbsys::foundation::fbase;

/**
 * This class represents a client context on a RealmServer. In as much as that if a client
 * session is closed and sometime later a new client session is created by referencing this
 * named object the client can resume where they were
 */
class nNamedObject : public CountableObject {
  public:
    virtual ~nNamedObject(void);

    /**
    * Returns the name of this client context
    *
    * @return String
    */
    DLL std::string getName();

    /**
    * Returns the current event ID that this named context is bound to
    *
    * @return long event ID
    */
    DLL longlong getEID();

    /**
    * Will this named object be restored after the Realm Server has been restarted
    *
    * @return bool flag
    * @deprecated This persistent flag is deprecated since 10.5. The method will be removed. Persistence of the durable
    * will be defined by the persistence support of the parent channel. If the parent channel supports persistent events,
    * its durables will always be created as persistent.
    */
    UM_DEPRECATED DLL bool isPersistent();

    /**
    * Does this named object exist across the cluster
    *
    * @return if the named object is cluster wide
    * @deprecated The cluster-wide flag is deprecated since 10.5. The method will be removed. The durable will be treated
    * as cluster-wide if its parent channel is a cluster-wide one.
    */
    UM_DEPRECATED DLL bool isClusterWide();

    /**
    * If set the named object will queue multiple subscription such that the first subscriber will receive all events until
    * it either disconnects or deletes the subscription, at which time, the next subscription request will start to
    * receive events.
    *
    * @return if the named object is cluster wide
    */
    DLL bool isPriorityEnabled();
    
    /**
     * Returns the total number of events for this particular named context
     *
     * @return long length
     * @since 9.9
     */
    DLL longlong getLength();

	/**
	* Will this named object be restored after the Realm Server has been restarted
	*
	* @return boolean flag
	* @since 9.9
	*/
	DLL bool isShared();

  protected:
    nNamedObject(const std::string& name, longlong eid, longlong id, bool persist, bool clusterWide, bool priority, bool shared, longlong queueLength);
    std::string m_name;
    longlong m_eid;
    longlong m_id;
    bool m_bPersist;
    bool m_bClusterWide;
    bool m_bPriorityEnabled;
    longlong m_bQueueLength;
	bool m_bIsShared;

    friend class nChannel;
    friend class nChannelIterator;
    friend class nChannelImpl;

};

}
}
}
}
