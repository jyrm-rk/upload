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
#include <string.h>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nHeader;
}
namespace client {

using namespace nbase;
using namespace foundation::fbase;

/**
 * The nEventAttributes class is used by the nConsumeEvent object in order to store standard header values associated with nirvana client, p2p and JMS events.
 *
 * <p>
 *
 * Not all values are set all the time. Some values are only set by the realm server, whereas other values are available to be programatically set.
 *
 * <p>
 *
 * The majority of values are specific to JMS Message headers, and as such would not be required to be used by a standard nConsumeEvent
 *
 * @since 4.0
 */
class nEventAttributes : public CountableObject {
  public:

    /**
    * Generate a new nEventAttributes object
    */
    nEventAttributes(void);
    virtual ~nEventAttributes(void);

    /**
    * Obtain the application id allocated to the event
    *
    * @return the application id
    */
    DLL unsigned char* getApplicationId();

    /**
    * Obtain the application id length allocated to the event
    *
    * @return the application id length
    */
    DLL int getApplicationIdLength();

    /**
    * Obtain the correlation id allocated to the event (JMS specific)
    *
    * Third-party monitoring and instrumentation solution *may* use this field, and non-JMS applications
    * should be aware that using it themselves *may* break these third-party solutions.
    *
    * @return the correlation id
    */
    DLL unsigned char* getCorrelationId();

    /**
    * Obtain the correlation id length allocated to the event (JMS specific)
    *
    * @return the correlation id length
    */
    DLL int getCorrelationIdLength();

    /**
    * Obtain the message id allocated to the event (JMS specific)
    *
    * @return the message id
    */
    DLL unsigned char* getMessageId();

    /**
    * Obtain the message id length allocated to the event (JMS specific)
    *
    * @return the message id length
    */
    DLL int getMessageIdLength();

    /**
    * Obtain the publisher host allocated to the event
    *
    * @return the publisher host
    */
    DLL unsigned char* getPublisherHost();

    /**
    * Obtain the length of the publisher host allocated to the event
    *
    * @return the length of the publisher host
    */
    DLL int getPublisherHostLength();

    /**
    * Obtain the publisher name allocated to the event
    *
    * @return the publisher name
    */
    DLL unsigned char* getPublisherName();

    /**
    * Obtain the length of the publisher name allocated to the event
    *
    * @return the length of the publisher name
    */
    DLL int getPublisherNameLength();

    /**
    * Obtain the time stamp allocated to the event
    *
    * @return the time stamp represented as a long value
    */
    DLL longlong getTimestamp();

    /**
    * Obtain the subscriber host allocated to the event
    * @param *pSubHost The subscriber host of the event
    * @param subHostLength The length of the subscriber host
    *
    * @return the subscriber host represented as a byte array value
    */
    DLL void setSubscriberHost(unsigned char *pSubHost, int subHostLength);

    /**
    * Set the subscriber name given to this event
    *
    * @param *pSubName the subscriber name of the event
    * @param subNameLength the length of the subscriber name
    */
    DLL void setSubscriberName(unsigned char *pSubName, int subNameLength);

    /**
    * Set the array of subscriber names this event will be delivered to
    *
    * @param *pSubName the subscriber name of the event
    * @param arrayLength the number of subscriber names in the array
    */
    DLL void setSubscriberNames(std::string *pSubName, int arrayLength);

    /**
    * Obtain the id associated with the dead event, if the event is consumed from a stores used as a dead event store
    *
    * @return the dead event id
    */

    DLL longlong getDeadEID();

    /**
    * Obtain the dead event store name allocated to the event if one exists
    *
    * @return the dead event store used by the channel from which this event came represented as a byte array value
    */

    DLL unsigned char* getDeadEventChannel();
    DLL int getDeadEventChannelLength();

    /**
    * Obtain the delivery mode used for this event
    *
    * @return the byte value that represents the delivery mode
    */

    DLL unsigned char getDeliveryMode();

    /**
    * Set the delivery mode
    * @param deliveryMode the byte value representing the delivery mode
    */

    DLL void setDeliveryMode(unsigned char deliveryMode);

    /**
    * Obtain the destination allocated to the event
    *
    * @return the destination represented as a byte array value
    */

    DLL unsigned char* getDestination();
    DLL int getDestinationLength();

    /**
    * Set the destination given to this event
    *
    * @param *pDestination the byte array value representing the destination used by the event
    * @param destinationLength the length of the pDestination array
    */

    DLL void setDestination(unsigned char *pDestination, int destinationLength);

    /**
    * Obtain the expiration value allocated to the event
    *
    * @return the expiration represented as a long value
    */

    DLL longlong getExpiration();

    /**
    * Set the event expiration value
    *
    * @param expiration the long value representing the expiration of the event
    */

    DLL void setExpiration(longlong expiration);

    /**
    * Obtain the join channel allocated to the event if the event was originally published via a channel join
    *
    * @return the joined channel represented as a byte array value
    */

    DLL unsigned char* getJoinChannel();
    DLL int getJoinChannelLength();

    /**
    * Obtain the realm on which the join channel exists if the event was originally published via a channel join
    *
    * @return the joined channel's realm represented as a byte array value
    */

    DLL unsigned char* getJoinRealm();
    DLL int getJoinRealmLength();

    /**
    * Obtain the join path allocated to the event as it travels through the joined channels if the event was originally published via a channel join
    *
    * @return the join path of the event, represented as a byte array value
    */

    DLL unsigned char* getJoinPath();
    DLL int getJoinPathLength();

    /**
    * Obtain the eid of the original event from the join channel
    *
    * @return the eid of the event from the joined channel represented as a long value
    */

    DLL longlong getJoinEID();

    /**
    * Obtain the type of the event
    *
    * @return the type represented as a byte value
    */

    DLL unsigned char getMessageType();

    /**
    * Set the event type
    *
    * @param messageType the byte value representing the type of the event
    */

    DLL void setMessageType(unsigned char messageType);

    /**
    * Obtain the priority allocated to the event
    *
    * @return the priority represented as a byte value
    */

    DLL unsigned char getPriority();

    /**
    * Set the event priority
    *
    * @param myPriority the byte value representing the priority
    */

    DLL void setPriority(unsigned char myPriority);

    /**
    * Obtain the number of times the event has been redelivered. Only relevant for events delivered on queues
    *
    * @return the number of times the event has been redelivered via the queue
    */

    DLL int getRedeliveredCount();

    /**
    * Obtain the reply to name allocated to the event
    *
    * @return the reply to name represented as a byte array value
    */

    DLL unsigned char* getReplyToName();
    DLL int getReplyToNameLength();

    /**
    * Set the reply to name given to this event
    *
    * @param replyToName the byte array value representing the reply to name of the event
    * @param replyToNameLength the length of the replyToName array
    */

    DLL void setReplyToName(unsigned char* replyToName, int replyToNameLength);

    /**
    * Obtain the reply type represented as a byte value
    *
    * @return the reply type
    */

    DLL unsigned char getReplyType();

    /**
    * Set the reply type
    *
    * @param replyType the byte representation of the reply type
    */

    DLL void setReplyType(unsigned char replyType);

    /**
    * Obtain the subscriber host allocated to the event
    *
    * @return the subscriber host represented as a byte array value
    */

    DLL unsigned char* getSubscriberHost();
    DLL int getSubscriberHostLength();

    /**
    * Obtain the subscriber id allocated to the event
    *
    * @return the subscriber id represented as an int value
    */

    DLL int getSubscriberId();

    /**
    * Set the subscriber id given to this event
    *
    * @param subId the byte array value representing the subscriber id of the event
    */

    DLL void setSubscriberId(int subId);

    /**
    * Obtain the subscriber name allocated to the event
    *
    * @return the subscriber name represented as a byte array value
    */

    DLL unsigned char* getSubscriberName();
    DLL int getSubscriberNameLength();

    /**
    * Obtain the arbitrary value given to this event to represent it's type
    *
    * @return the message type represented as a byte array value
    */

    DLL unsigned char* getEventType();
    DLL int getEventTypeLength();

    /**
    * Set the arbitrary event type given to this event
    *
    * @param type the byte array value representing the type of the event
    * @param typeLength the length of the type array
    */

    DLL void setEventType(unsigned char* type, int typeLength);

    /**
    * Obtain the user id allocated to the event
    *
    * @return the user id represented as a byte array value
    */

    DLL unsigned char* getUserId();
    DLL int getUserIdLength();

    /**
    * Set the user id given to this event
    *
    * @param userId the byte array value representing the user id of the event
    * @param userIdLength the length of the userId array
    */

    DLL void setUserId(unsigned char* userId, int userIdLength);

    /**
    * Set the application id given to this event
    *
    * @param *pApplicationId the byte array value representing the application id of the event
    * @param applicationIdLength the length of the pApplicationId array
    */

    DLL void setApplicationId(unsigned char* pApplicationId, int applicationIdLength);

    /**
    * Set the event correlation id (JMS specific)
    *
    * Third-party monitoring and instrumentation solution *may* use this field, and non-JMS applications
    * should be aware that using it themselves *may* break these third-party solutions.
    *
    * @param pCorrelationId the byte array value representing the correlation id of the event
    * @param correlationIdLength the length of the pCorrelationId array
    */

    DLL void setCorrelationId(unsigned char* pCorrelationId, int correlationIdLength);

    /**
    * Set the event message id (JMS specific)
    *
    * @param MessageId the byte array value representing the message id of the event
    * @param messageIdLength the length of the MessageId array
    */

    DLL void setMessageId(unsigned char* MessageId, int messageIdLength);

    /**
    * Set the publisher host value given to this event
    *
    * @param pPubHost the byte array value representing the publisher host of the event
    * @param pubHostLength the length of the pPubHost array
    */

    DLL void setPublisherHost(unsigned char* pPubHost, int pubHostLength);

    /**
    * Set the publisher name given to this event
    *
    * @param pPubName the byte array value representing the publisher name of the event
    * @param pubNameLength the length of the pPubName array
    */

    DLL void setPublisherName(unsigned char* pPubName, int pubNameLength);

    /**
    * If this flag is true, the event will be merged with the existing event on this Channel / Data Group
    *
    * @return true if event can be merged
    */

    DLL bool allowMerging();

    /**
    * Sets whether this event can be merged at the server for the Channel or Data Groups
    * @param flag true to permit the merge, false if not
    */

    DLL void setAllowMerge(bool flag);

    /**
    * Indicates if this event was created by a nRegisteredEvent
    * @return true if this event comes from a nRegisteredEvent
    */

    DLL bool isRegistered();

    /**
    * Indicates if this event is a delta event
    * @return true if this event is a delta derived from a registered event update, false if the event is a full event (snapshot)
    */

    DLL bool isDelta();

    /**
    * Specifies a message type for event of JMS base Message Impl
    */
    const static unsigned char JMS_BASE_MESSAGE_TYPE = 0;

    /**
     * Specifies a message type for event of JMS MapMessage
     */
    const static unsigned char JMS_MAP_MESSAGE_TYPE = 1;

    /**
     * Specifies a message type for event of JMS BytesMessage
     */
    const static unsigned char JMS_BYTES_MESSAGE_TYPE = 2;

    /**
     * Specifies a message type for event of JMS ObjectMessage
     */
    const static unsigned char JMS_OBJECT_MESSAGE_TYPE = 3;

    /**
     * Specifies a message type for event of JMS StreamMessage
     */
    const static unsigned char JMS_STREAM_MESSAGE_TYPE = 4;

    /**
     * Specifies a message type for event of JMS TextMessage
     */
    const static unsigned char JMS_TEXT_MESSAGE_TYPE = 5;

  private:
    nHeader *m_pHeader;
    nHeader* getHeader();
    nEventAttributes(nHeader *pHeader);

    friend class nConsumeEvent;

};

}
}
}
}
