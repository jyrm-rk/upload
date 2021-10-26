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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nProtobufEvent;

/**
 * This class is used to facilitate creation of nConsumeEvent objects
 */
class nProtobufEventFactory {
  public:
    nProtobufEventFactory(void);
    virtual ~nProtobufEventFactory(void);

    /**
	 * Creates an nProtobufEvent object based on the parameters supplied
	 * @param tag The tag for this event as a unsigned char*
	 * @param tagLength The length of the tag
	 * @param data The serialized message as a unsigned char*
	 * @param dataLength The length of the data
	 * @param TTL the Time To Live for this event
	 * @param isPersistent flag to show whether the event is persistent of not
	 * @return the newly created nProtobufEvent object
	 */
    static nProtobufEvent* create(unsigned char* tag, int tagLength, unsigned char* data, int dataLength, longlong TTL, bool isPersistent);
};

}
}
}
}
