/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nACLEntry.h"
#include "nSecurityGroup.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
/**
 * Extends the nACLEntry class to supply Channel/Queue specific security settings
 *
 * @see nACLEntry
 */
class nChannelACLEntry :
    public nACLEntry {
  public:
    nChannelACLEntry(void);

    /**
     * Creates a new nChannelACLEntry for the name@host supplied. By default this
     * subject has NO privileges and they must be set.
     *
     * @see nACLEntry
     * @param subject of the form user@host
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    nChannelACLEntry(const std::string& subject);

    /**
     * Creates a new nChannelACLEntry for the name@host supplied. By default this
     * subject has NO privileges and they must be set.
     *
     * @see nACLEntry
     * @param subject of the form user@host
     * @param copy An nACLEntry to copy the current permissions from
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    nChannelACLEntry(const std::string& subject, nACLEntry *pCopy);

    /**
     * Creates a new nChannelACLEntry for the name@host supplied. By default this
     * subject has NO privileges and they must be set.
     *
     * @see nACLEntry
     * @param grp group name
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    nChannelACLEntry(nSecurityGroup* grp);

    /**
     * Creates a new nChannelACLEntry for the name@host supplied. By default this
     * subject has NO privileges and they must be set.
     *
     * @see nACLEntry
     * @param grp group name
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
	nChannelACLEntry(nSecurityGroup* grp, BitArray* pBs);

    /**
     * Creates a new nChannelACLEntry for the name\@host supplied. By default this
     * subject has NO privileges and they must be set.
     *
     * @see nACLEntry
     * @param name Name for the subject
     * @param host Host name for the subject
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    DLL nChannelACLEntry(const std::string& name, const std::string& host);


    /**
     * Creates a new nChannelACLEntry for the name\@host supplied. By default this
     * subject has NO privileges and they must be set.
     *
     * @see nACLEntry
     * @param subject Name for the subject
     * @param *pBitset the bitset denoting the permissions for this nACLEntry
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    nChannelACLEntry(const std::string& subject, BitArray *pBitset);

    virtual ~nChannelACLEntry(void);

    /**
     * Returns the type of the ACL this entry represents.  In this case the ACL entry represents a channel ACL entry.
     * @return the type of this ACL entry.
     */
    virtual int getType();

    /**
     * Allow/Disallow this subject from getting the last EID from the Channel
     *
     * @param val a Boolean flag indicating the subject's permission status
     */
    virtual void setGetLastEID(bool val);

    /**
     * Allow/Disallow this subject from reading from the Channel/Queue
     *
     * @param val a bool flag indicating the subject's permission status
     */
    virtual void setRead(bool val);

    /**
     * Allow/Disallow this subject from writing to the Channel/Queue
     *
     * @param val a Boolean flag indicating the subject's permission status
     */
    virtual void setWrite(bool val);

    /**
     * Allow/Disallow this subject from purging events from the queue/channel
     *
     * @param val a Boolean flag indicating the subject's permission status
     */
    virtual void setPurge(bool val);

    /**
     * Allow/Disallow this subject from popping events from a queue
     *
     * @param val a Boolean flag indicating the subject's permission status
     */
    virtual void setPop(bool val);

    /**
     * Allow/Disallow this subject from creating a named subscription to a Channel
     *
     *  @param val a Boolean flag indicating the subject's permission status
     */
    virtual void setUseNamedSubscription(bool val);

    /**
     * Can this subject get the last event id from the Channel. The Queue does not support this function
     *
     * @return The current subject permission status as a boolean
     */
    virtual bool canGetLastEID();

    /**
    * Can the subject read from the Queue/Channel. If true the subject can pop/peek a queue and subscribe
    * to a channel
    *
    * @return The current subject permission status as a boolean
    */
    virtual bool canRead();

    /**
     * Can this subject write to the Queue/Channel. If the secure object is a Channel it
     * means the subject can publish to it, if it is a Queue the subject can push on to the
     * queue.
     *
     * @return The current subject permission status as a boolean
     */
    virtual bool canWrite();

    /**
     * Can this subject remove events from the Channel/Queue using the purge methods.
     *
     * @return The current subject permission status as a boolean
     */
    virtual bool canPurge();

    /**
     * Can this subject POP events from a Queue. Since a POP is an atomic read/write operation since
     * it removes the event from the queue. However a user can pop events but might not be permitted
     * to write events to the queue.
     *
     * @return The current subject permission status as a boolean
     */
    virtual bool canPop();

    /**
     * Can this subject use a named subscription on the Channel.
     *
     * When using a named subscription, the state of the last Event received by the subscription is kept by the Server.
     *
     * If the Connection is dropped and restarted with the same name, the server will automatically start the subscription from where the last event received, without the user needing to supply an Event ID to start from.
     *
     * @return The current subject permission status as a boolean
     */
    virtual bool canUseNamedSubscription();

  protected:
    nChannelACLEntry(const std::string& name, const std::string& host, BitArray *pBitset);

  private:
    static const int CHANNEL_ADMIN = 4; //Not Used
    static const int CHANNEL_JOIN = 8; // Not Used
  public:
	static const int CHANNEL_PUB = 5;
	static const int CHANNEL_SUB = 6;
	static const int CHANNEL_PURGE = 7;
	static const int CHANNEL_LAST_EID = 9;
	static const int CHANNEL_POP = 10;
	static const int CHANNEL_NAMED = 11;
};

}
}
}
}
