/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nConsumeEvent.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

/**
 * This class represents a Google Protocol Buffer Event. A Google Protocol Buffer Event
 * consists of the serialized Message and a string to identify what type of message is contained.
 * The MessageType attribute in the event header is set to 6 to identify the message as a
 * Protocol buffer event.
 * Optionally a Google Protocol Buffer Event may also contain a tag.
 */
class nProtobufEvent :
    public nConsumeEvent {
  public:
    static const unsigned char GoogleProtocolBufferType = 6;

    virtual ~nProtobufEvent(void);

    /**
    * Constructs a new nProtobufEvent with the message type set to the
    * type name of the message passed in.
    * @param data the constructed message.
    * @param descriptionName the google protocol buffer Description type name
    */
    DLL nProtobufEvent(unsigned char* data, int dataLength,unsigned char* descriptionName, int descriptionLength);

    /**
    * Constructs a new nProtobufEvent with the message type set to the
    * type name of the message passed in.
    * @param tag the event tag String encoded
    * @param data the constructed message.
    * @param descriptionName the google protocol buffer Description type name
    */
    DLL nProtobufEvent(unsigned char* tag, int tagLength, unsigned char* data, int dataLength, unsigned char* descriptionName, int descriptionLength);

    /**
    * Returns the type name of the message in the nProtobufEvent as a String
    * @return the type name of the event's Message as a String
    */
    DLL std::string getTypeName();

    /**
    *	Method to identify whether this event has been constructed with a Google Protocol Buffer message.
    *	Will return true or false
    */
    DLL bool isProtoBuffEvent();

    /**
        * Sets this event's properties
        * @deprecated The method is deprecated in 10.7. Not able to set explicitly properties to a Protobuf Event.
        */

        UM_DEPRECATED DLL void setProperties(nEventProperties* newProperties);
};

}
}
}
}
