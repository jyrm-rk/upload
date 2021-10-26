/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nBaseConsumeEvent.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nChannelQueue;
}
namespace client {

class nEventAttributes;
class nChannelImpl;

using namespace foundation::fbase;
using namespace nbase;

/**
 * This class represents a Nirvana event, which consists of either a tag and some
 * data or an event dictionary and some data.
 */
class nConsumeEvent :
    public nBaseConsumeEvent, public CountableObject {
  public:

    DLL void deleteProperties();

    DLL virtual ~nConsumeEvent(void);

    /**
    * Constructs a new nConsumeEvent with the specified event properties and data.
    * The event properties can be used to create filter rules.
    *
    * @param *pProperties the collection of key-value pairs that can be used for filter rules
    * @param data the event data byte[] encoded
    * @param dataLength the length of the data
    */
    DLL nConsumeEvent(nEventProperties *pProperties, unsigned char* data, int dataLength);

    /**
    * Constructs a new nConsumeEvent with the specified tag, event properties and data.
    * The event properties can be used to create filter rules.
    *
    * @param tag the event tag as a string
    * @param *pProperties the collection of key-value pairs that can be used for filter rules
    * @param data the event data byte[] encoded
    * @param dataLength the length of the data
    */
    DLL nConsumeEvent(const std::string& tag, nEventProperties *pProperties, unsigned char* data, int dataLength);

    /**
    * Constructs a new nConsumeEvent with the specified tag, event properties and data.
    * The event properties can be used to create filter rules.
    *
    * @param tag the event tag byte[] encoded
    * @param tagLength the length of the tag
    * @param *pProperties the collection of key-value pairs that can be used for filter rules
    * @param data the event data byte[] encoded
    * @param dataLength the length of the data
    */
    DLL nConsumeEvent(unsigned char* tag, int tagLength, nEventProperties *pProperties, unsigned char* data, int dataLength);

    /**
    * Constructs a new nConsumeEvent with the specified event tag and data
    *
    * @param tag the event tag byte[] encoded
    * @param tagLength the length of the tag
    * @param data the event data byte[] encoded
    * @param dataLength the length of the data
    */
    DLL nConsumeEvent(unsigned char* tag, int tagLength, unsigned char* data, int dataLength);

    /**
    * Constructs a new nConsumeEvent with the specified event tag and data
    *
    * @param tag the event tag as a string
    * @param data the event data byte[] encoded
    * @param dataLength the length of the data
    */
    DLL nConsumeEvent(const std::string& tag, unsigned char* data, int dataLength);

    /**
    * Constructs a new nConsumeEvent with the specified event properties and tag.
    * The event properties can be used to create filter rules.
    *
    * @param *pProperties the collection of key-value pairs that can be used for filter rules
    * @param tag the event tag
    */

    DLL nConsumeEvent(nEventProperties *pProperties, std::string& tag);

    /**
    * When you subscribe to a channel, and the channel's data contains a finite and reasonably static set of events,
    * the last event in the channel is sent and marked as the end of the channel.
    *
    * @return bool flag indicating if this is the last event in the channel
    * @since 4.0
    */
    DLL bool isEndOfChannel();

    /**
    * Method indicating whether there is an nEventAttributes associated with this event
    *
    * @return whether the nEventAttributes exists for this event
    * @since 4.0
    * @see nEventAttributes
    */

    DLL bool hasAttributes();

    /**
    * Method that returns the nEventAttributes for this event
    *
    * @return the nEventAttributes for this event
    * @since 4.0
    * @see nEventAttributes
    */
    DLL nEventAttributes* getAttributes();

    /**
    * Sends an ack for this event to the server
    *
    * @exception Exception If unable to send the rollback request to the server
    */

    DLL void ack();

    /**
    * This function will return the name of the channel / queue that the event was delivered from.
    *
    * @return the name of the channel or queue
    */

    DLL std::string getChannelName();

    /**
    * Gets the event data set for this event
    *
    * @return a unsigned char[] containing the encoded event data in the form it travels
    *         on the network
    */

    DLL unsigned char* getEventData();
    DLL int getEventDataLength();

    /**
    * Gets the unique (for its channel) event id value
    *
    * @return a long specifying the unique (for its channel) event id attribute
    */

    DLL longlong getEventID();

    /**
    * Gets the event tag set for this event
    *
    * @return a string specifying the event tag set for this event
    */

    DLL std::string& getEventTag();

    /**
    * This function will return the fully qualified name of the channel / queue that the event was delivered from.
    *
    * @return the fully qualified name of the channel or queue
    * @exception nBaseClientException If the fully qualified name is not set
    * @since 3.1
    */

    DLL std::string getFullChannelName();

    /**
    * Gets this event's properties
    *
    * @return the collection of key-value pairs used to create filter rules
    */

    DLL nEventProperties* getProperties();

    /**
    * Sets this event's properties
    *
    */

    DLL void setProperties(nEventProperties* newProperties);

    /**
    * Return the id of the user that published this event. This value will be obtained from the nEventAttributes associated with this event.
    * @return the user who published this event
    * @since 4.0
    * @see nEventAttributes
    */

    DLL void getPublishUser(std::string& pubUser);

    /**
    * Return the host name from which the event was published. This value will be obtained from the nEventAttributes associated with this event.
    * @return the host name from which the event was published
    * @since 4.0
    * @see nEventAttributes
    */

    DLL void getPublishHost(std::string& pubHost);

    /**
    * Returns the digital signature of the event if it was signed by the publisher else it returns
    * null.
    *
    * @return Variable length byte[] of the signature
    */

    DLL unsigned char* getSignature();
    DLL int getSignatureLength();

    /**
    * Return the time stamp of this event. This value will be obtained from the nEventAttributes associated with this event.
    * @return the time stamp when the event was received by the server
    * @since 4.0
    * @see nEventAttributes
    */

    DLL longlong getTimestamp();

    /**
    * Returns how long the event will be stored on disk in a mixed channel
    *
    * @return Long millisecond time to keep on the server
    */

    DLL longlong getTTL();

    /**
    * Sets the TTL for this event. On a mixed channel this time is how long the event is kept
    *
    * @param ttl Time in milliseconds
    */

    DLL void setTTL(longlong ttl);

    /**
    * Returns the persistent flag. If true the event is stored to disk on the server
    *
    * @return bool flag
    */

    DLL bool isPersistent();

    /**
    * Sets the persistent flag. On mixed channels, if set, will cause this event to be stored to disk
    *
    * @param flag bool flag
    */

    DLL void setPersistent(bool flag);

    /**
    * Returns whether the event is transient. If the event itself is transient, it will never be stored
    * either in memory or on disk by the realm server, but simply discarded once it has been delivered
    * to any consumers. This is the equivalent of publishing events on a Transient channel, however
    * allows the transience to be specified on a per event basis.
    *
    * @return whether the event is transient
    * @see nChannelAttributes
    * @since 4.0
    */

    DLL bool isTransient();

    /**
    * Sets whether the event is transient. If the event itself is transient, it will never be stored
    * either in memory or on disk by the realm server, but simply discarded once it has been delivered
    * to any consumers. This is the equivalent of publishing events on a Transient channel, however
    * allows the transience to be specified on a per event basis.
    *
    * Note: Transient events are not supported for queues since 10.5. Setting this flag will not
    * have any effect for events published to a queue and the events will be stored even
    * if there are no active consumers.
    *
    * @param flag whether the event is transient
    */

    DLL void setTransient(bool flag);

    /**
    * Tells the server that it does not ack this event.
    *
    * @exception Exception If unable to send the rollback request to the server
    */
    DLL void rollback();

    /**
     * Method that sets the nEventAttributes for this event
     *
     * @param *pAttributes nEventAttributes for this event
     * @since 4.0
     * @see nEventAttributes
     */
    DLL void setAttributes(nEventAttributes *pAttributes);

    virtual int getType();

    /**
    *	Method to identify whether this event has been constructed with a Google Protocol Buffer message.
    *	Will return true or false
    */
    DLL virtual bool isProtoBuffEvent();

    /**
    * Sets the session name that will be the only consumer of this event. By setting this, no other subscribers, either on a queue or channel will consume this event.
    *
    * @param subName - the subscriber name, equal to the session name of the designated user
    * @param length - the length of the array
    */
    DLL void setSubscriberName(unsigned char* subName, int length);

    /**
    * Sets the session names that will be the only consumers of this event. By setting this, no other subscribers, either on a queue or channel will consume this event.
    * @throws nIllegalArgumentException This exception is thrown if the mySubName array is larger than 32767
    * @param subName - the subscriber names, equal to the session names of the designated users
    * @param length - the length of the array
    */
    DLL void setSubscriberNames(std::string* subName, int length);

    /**
    * Sets the host name or ip address representing the consumers of this event. By setting this, only connections matching the host name or ip address will consume this event. Wildcard * are also supported, so you can have *.abc.com fore example
    *
    * @param host - the host name or ip address of connections that will consume this event
    * @param length - the length of the array
    */
    DLL void setSubscriberHost(unsigned char* host, int length);

    /**
    * Get the name of the nDataGroup that this event was published to
    * Returns the name
    * @return
    */

    DLL const std::string& getDataGroupName();

    /**
    * Get the event header
    * Returns a pointer to the event header
    * @return
    */

    DLL nHeader* getHeader();

    void setHeader(nHeader *pHeader);

  protected:
    void setChannel(nChannelImpl *pChan);
    
    /**
     * Sets the ID of the queue reader this event is received with. Must be used only if event is received from a queue store.
     * The queue reader is required for acknowledgment and rollback operations, if not specified the server will need to determine which reader
     * has received this event, which might have suboptimal performance.
     */
    void setQueueReaderId(longlong queueReaderId);

  private:
    nEventAttributes *m_pAttributes;
    void setEndOfChannel(bool flag);
    void setNameId(longlong id);
    void setEventID(longlong id);
    void setDataGroupName(const std::string& name);

    std::string m_dataGroupName;

    friend class nChannelImpl;
    friend class nChannelIterator;
    friend class nSession;
    friend class nConsumeEventConverter;
    friend class nDataGroupPumpImpl;
    friend class nQueueSyncReader;
    friend class eventConsumerWrapper;
};

}
}
}
}
