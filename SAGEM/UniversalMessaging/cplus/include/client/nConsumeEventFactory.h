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

class nConsumeEvent;
class nEventProperties;

/**
 * This class is used to facilitate creation of nConsumeEvent objects
 */
class nConsumeEventFactory {
  public:
    nConsumeEventFactory(void);
    virtual ~nConsumeEventFactory(void);

    /**
    * Creates an nConsumeEvent object based on the parameters supplied
    *
    * @param tag The tag for this event
    * @param *pProps The nEventProperties associated with this event
    * @param data The data for this event
    * @param dataLength the length of the data
    * @param TTL the Time To Live for this event
    * @param isPersistent flag to show whether the event is persistent of not
    * @return the newly created nConsumeEvent object
    */
    static nConsumeEvent* create(unsigned char* tag, int tagLength, nEventProperties *pProps, unsigned char* data,
                                 int dataLength, longlong TTL, bool isPersistent);

    /**
    * Creates an nConsumeEvent object based on the parameters supplied
    *
    * @param tag The tag for this event
    * @param tagLength the length of the tag
    * @param data The data for this event
    * @param dataLength the length of the data
    * @param TTL the Time To Live for this event
    * @param isPersistent flag to show whether the event is persistent of not
    * @return the newly created nConsumeEvent object
    */
    static nConsumeEvent* create(unsigned char* tag, int tagLength, unsigned char* data,
                                 int dataLength, longlong TTL, bool isPersistent);

    /**
    * Creates an nConsumeEvent object based on the parameters supplied
    *
    * @param *pProps The nEventProperties associated with this event
    * @param tag The tag for this event
    * @param TTL the Time To Live for this event
    * @param isPersistent flag to show whether the event is persistent of not
    * @return the newly created nConsumeEvent object
    */

    static nConsumeEvent* create(nEventProperties *pProps, std::string& tag, longlong TTL, bool isPersistent);

    /**
    * Creates an nConsumeEvent object based on the parameters supplied
    *
    * @param tag The tag for this event
    * @param pProps event properties
    * @param data The data for this event
    * @param dataLength the length of the data
    * @param TTL the Time To Live for this event
    * @param isPersistent flag to show whether the event is persistent of not
    * @return the newly created nConsumeEvent object
    */
    static nConsumeEvent* create(std::string& tag, nEventProperties *pProps, unsigned char* data, int dataLength,
                                 longlong TTL, bool isPersistent);
};

}
}
}
}
