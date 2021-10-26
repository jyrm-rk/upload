/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nBaseConstants.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;
struct ProtobufDescriptor;
}
namespace client {
class nRealm;
class nChannelPublishKeys;
class nAbstractChannel;
class nStoreProperties;
using namespace com::pcbsys::nirvana::nbase;

/**
 * This class is a container for the attributes necessary to create or locate a Nirvana channel or queue.
 */
class nChannelAttributes : public com::pcbsys::foundation::fbase::CountableObject {
  public:

    /**
    * Default constructor
    */

    DLL nChannelAttributes(void);

    /**
    * Constructs from the base attribute class
    *
    * @param attr Base class used to construct this class
    */

    nChannelAttributes(nBaseChannelAttributes *pAttr);

    /**
    * Constructs from the name of the channel, useful when finding existing channels
    * @param name of the channel and uses defaults for the other parameters
    * @throws nIllegalArgumentException thrown if an name is illegal
    */

    DLL nChannelAttributes(std::string name);

    /**
    * Constructs a nChannelAttributes object with the values specified.
    *
    * @param name A string specifying the channel name
    * @param maxEvents An int specifying the maximum number of events this
    * channel can contain (i.e. the capacity)
    * @param ttl An int specifying the Time To Live (TTL) for events published in this
    * channel (i.e. the age)
    * @param type An int specifying the channel type. Valid values are nBaseConstants.CHAN_RELIABLE or
    * nBaseConstants.CHAN_PERSISTENT
    * @param *pRealm A nRealm object specifying the realm this channel exists within
    * @exception nIllegalArgumentException is thrown if an incorrect parameter is passed to the constructor
    */
    DLL nChannelAttributes(std::string name, int maxEvents, longlong ttl, int type, nRealm *pRealm = NULL);

    DLL virtual ~nChannelAttributes(void);

    /**
    * Set the channel name for this channel attribute object. If the channel
    * begins with '/', a realm path is also created and the channel is marked as
    * external.
    *
    * @param channelName A string specifying the name of the channel for this
    * channel attribute object.
    *
    * @exception nIllegalArgumentException is thrown if an incorrect value is passed
    */
    DLL void setName (std::string channelName);

    /**
    * Gets the channel name
    *
    * @return A string specifying the name value of the channel
    */
    DLL const std::string getName();

    /**
    * Returns either channel (CHANNEL_MODE) or queue (QUEUE_MODE)
    *
    * @return the channel mode specified in this channel attributes
    */
    DLL int getChannelMode();

    /**
    * Sets the channel mode as either a queue or a channel. These are specified as :
    *
    * nChannelAttributes.QUEUE_MODE & nChannelAttributes.CHANNEL_MODE
    *
    * @param mode - one of the supported modes, either queue or channel
    *
    * @throws nIllegalArgumentException if the specified channel mode not one of the support modes
    */
    DLL void setChannelMode(int mode);

    /**
    * Gets the Unique ID value for the channel
    *
    * @return A long specifying the current Unique ID value for the channel
    */
    DLL longlong getUniqueId();

    /**
    * Sets the type of channel.
    *
    * @param type An int specifying the channel type.
    *
    * @exception nIllegalArgumentException is thrown if an illegal channel type is specified
    */
    DLL void setType(int type);

    /**
    * Sets the maximum number of events the channel can contain. (i.e. the capacity)
    *
    * @param value An int specifying the max number of events
    * @exception nIllegalArgumentException is thrown if an incorrect value is passed
    */
    DLL void setMaxEvents(int value);

    /**
    * Sets the Time To Live (TTL) value for each event contained in the channel
    *
    * @param value A long specifying the new TTL value
    * @exception nIllegalArgumentException is thrown if an invalid TTL value is specified
    */
    DLL void setTTL(longlong value);

    /**
    * Specifies whether this channel is a cluster channel, where it will exist in all member nodes within the cluster.
    *
    * @param flag is this channel to exist across all cluster realms
    */
    DLL void setClusterWide(bool flag);

    /**
    * Sets the realm the channel exists within, marking the channel as external.
    * If the realm is not set, it is implied that the channel exists within the
    * realm you have a session to and use this object.
    *
    * @param *pRealm An nRealm object specifying the realm the channel exists within
    */
    DLL void setRealm(nRealm *pRealm);

    /**
    * Is this channel cluster wide
    * @return if this channel is cluster wide
    */

    DLL bool isClusterWide();

    /**
    * Gets the channel type
    *
    * @return an int specifying the channel's type, which will be equal to one of :
    * <p><KBD>
    *    nChanneAttributes.MIXED_TYPE <br>
    *    nChanneAttributes.PERSISTENT_TYPE <br>
    *    nChanneAttributes.RELIABLE_TYPE <br>
    * </KBD>
    * <p>
    */

    DLL int getType();

    /**
    * Gets the full name of a channel, including the realm path if set.
    *
    * @return A string specifying the full name of a channel.
    * @exception nBaseClientException is thrown if the name value is not set
    */

    DLL std::string getFullName();

    /**
    * Sets the channel keys for this channel
    *
    * @param **ppKeys An array of nChannelPublishKeys to be assigned to this channel
    * @param numKey length of the array
    */

    DLL void setPublishKeys(nChannelPublishKeys **ppKeys, int numKey);

    /**
    * Gets the channel keys for this channel
    *
    * @param numKey the number of publish keys
    *
    * @return nChannelPublishKeys[] The currently configured publish keys for this channel
    */

    DLL nChannelPublishKeys** getPublishKeys(int& numKey);

    /**
    * Gets the realm this channel exists within.
    *
    * @return an nRealm object specifying the realm this channel exists within
    * within the realm you have a session to and use this object.
    */

    DLL nRealm* getRealm();

    /**
    * Gets the Time To Live (TTL) value that will be applied to each event contained in the channel
    *
    * @return A long specifying the current TTL value setting for the channel
    */

    DLL longlong getTTL();

    /**
    * Gets the isExternal flag to find out if the channel is marked as external.
    *
    * @return  A bool specifying whether this channel is external or not
    */

    DLL bool isExternal();

    /**
    * Specifies whether this channel will use the JMS Style fanout engine. For more information on this, please see the version 4.0 documentation.
    *
    * @return whether events are delivered via the JMS fanout engine.
    * @since 4.0
    */

    DLL bool isJMSEngine();

    /**
    * Set the dead event handler store for this channel / queue. When events reach there ttl or the channel hits its ttl, but have not been consumed, they can be placed in a dead event store.
    *
    * <p>
    *
    * Setting the dead event store to be another valid channel or queue will enable this functionality and allow you to keep track of events that have died in this manner.
    * @param *pStore the channel or queue to be set as the dead event store
    */

    DLL void setDeadEventHandler(nAbstractChannel *pStore);

    /**
    * Sets whether to use the JMS style fanout engine. Not applicable to queues.
    *
    * @param useJMSEngine use the JMS fanout engine
    * @since 4.0
    */

    DLL void useJMSEngine(bool useJMSEngine);

    /**
    * Specifies whether this channel will use the Merge and Update Style fanout engine. For more information on this, please see the version 5.0 documentation.
    *
    * @return whether events are delivered via the Merge and update fanout engine.
    * @since 5.0
    */

    DLL bool isMergeEngine();

    /**
    * Sets whether to use the Merge fanout engine
    *
    * @param useMergeEngine use the Update and Merge fanout engine
    * @since 5.0
    */

    DLL void useMergeEngine(bool useMergeEngine);

    /**
    *  Returns the nStoreProperties objec.
    *
    * @since 5.0
    *
    */

    DLL nStoreProperties* getProperties();

	/**
	* get protobuf descriptos array
	*
	* @return vector from ProtobufDescriptor* objects. User has the responsibility to free the memory allocated for each ProtobufDescriptor object
	*
	* @since 9.9
	*
	*/
	DLL std::vector<ProtobufDescriptor*> getProtobufDescriptors();


	/**
	* set protobuf descriptos array
	*
	* @param descriptors- Contains descriptors data.
	*
	* @since 9.9
	*
	*/
	DLL void setProtobufDescriptors(const std::vector<ProtobufDescriptor*> &descriptors);

    /**
    * Specifies a reliable (in memory but with EIDs retained) channel type
    */
    static const int RELIABLE_TYPE = nBaseConstants::CHAN_RELIABLE;
    /**
    * Specifies a persistent (on disk) channel type
    */
    static const int PERSISTENT_TYPE = nBaseConstants::CHAN_PERSISTENT;
    /**
    * Specifies a mixed (persistence and ttl set on a per event basis) channel type
    */
    static const int MIXED_TYPE = nBaseConstants::CHAN_MIXED;
    
    /**
    * Specifies a channel (or topic) mode for the pub/sub model
    */
    static const int CHANNEL_MODE = nBaseConstants::CHAN_MODE_NORMAL;

    /**
    * Specifies a queue (point 2 point) mode for the queue model
    */
    static const int QUEUE_MODE = nBaseConstants::CHAN_MODE_QUEUE;

	/**
	* Dictionary stamping state - ENABLED
	*/
	static const int DICTIONARY_STAMPING_ENABLED = nBaseConstants::DICTIONARY_STAMPING_ENABLED;

	/**
	* Dictionary stamping state - DISABLED
	*/
	static const int DICTIONARY_STAMPING_DISABLED = nBaseConstants::DICTIONARY_STAMPING_DISABLED;

	/**
	* Dictionary stamping state - DEFAULT
	* By default the engine will fall back to the server-wide configuration setting
	*/
	static const int DICTIONARY_STAMPING_DEFAULT = nBaseConstants::DICTIONARY_STAMPING_DEFAULT;

    /**
    * Allow everyone to create a named object on this channel
    */
    static const long sAllowNamedAccess = 2048;

    /**
    * Allow everyone to pop events from the queue, (Only valid on Queues)
    */
    static const long sAllowQueuePopAccess = 1024;

    /**
    * Get the last known Event ID on the channel / queue
    */
    static const long sAllowLastEIDAccess = 512;

    /**
    * Allow everyone to purge events from the channel ( Only valid on channels )
    */
    static const long sAllowPurgeAccess = 128;

    /**
    * Allow everyone to subscribe to the channel ( Only valid on channels )
    */
    static const long sAllowSubscribeAccess = 64;

    /**
    * Allow everyone to write events to the channel / queue
    */
    static const long sAllowPublishAccess = 32;

    /**
    * Allow everyone to do everything on the channel / queue (Use with extreme caution since it bypasses any security checks for this channel / queue )
    */
    static const long sAllowFullAccess = 8;

    /**
    *  Allow everyone to read the ACL lists
    */
    static const long sAllowReadACLAccess = 4;

    /**
    * Allow everyone to add / remove acl entries on the channel / queue
    */
    static const long sAllowManageACLAccess = 2 + 1;

    /**
    * Sets the Unique ID value for the channel
    *
    * @param id A long specifying the new unique id value
    */

    void setUniqueId(longlong id);
    void setInternalName(std::string nameEx);

    /**
    * Gets the maximum number of events the channel can contain. (i.e. the capacity)
    *
    * @return An int specifying the maximum number of events this channel can
    * currently contain (i.e. the current capacity)
    */

    DLL int getMaxEvents();

  protected:
    nStoreProperties* m_pProperties;
    nBaseChannelAttributes* getBaseAttributes();
    nBaseChannelAttributes* getBaseAttributesValidate();

    friend class nChannelImpl;
    friend class nChannelIterator;
    friend class nSession;
    friend class nTransaction;
    friend class nQueueSyncReader;
    friend class nChannel;

  private:
    void initDefaultValues();
    nBaseChannelAttributes *m_pAttributes;
};

}
}
}
}
