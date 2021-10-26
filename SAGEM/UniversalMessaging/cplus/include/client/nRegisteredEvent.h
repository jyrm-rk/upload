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
#include "fObject.h"
#include "fSortedList.h"
#include <stdio.h>
#include <string.h>

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nChannel;
class nDataGroup;
class nEventProperties;
class ChangeContainer;
class EventSink;
class nConsumeEvent;

using namespace foundation::fbase;
using namespace foundation::collections;

/**
 * This class enables a client to maintain a copy of an event, make changes to the properties and then when commit is called
 * only the changes are published to the server. This enables a mechanism whereby only changes are published and not full events
 */
class nRegisteredEvent : Poco::Mutex {
  public:
    nRegisteredEvent(const std::string& keyName, fObject *pVal, nChannel *pSource, bool isTx);
    nRegisteredEvent(nDataGroup *pSource);
    virtual ~nRegisteredEvent(void);

    /**
     * Retrieves the name of the primary key name used for this event.
     *
     * This key name is setup during channel construction using the publish key API
     *
     * @return String name of the key
     */
    const std::string& getPrimaryKeyName();
    /**
     * Retrieves the unique value for the primary key used for this event
     *
     * @return Object value of the key
     */
    Object* getPrimaryKeyValue();
    /**
     * Returns the string tag of the event
     *
     * @return String tag for the event
     */
    const std::string& getTag();
    /**
     * Sets the tag for the event.
     *
     * @param tag String representation of the tag to use
     */
    void setTag(const std::string& tag);
    /**
     * Retrieves the properties for the event. The client can then change the key/value pairs in the properties.
     * When the commitChanges() is called all changes will be sent to the server
     *
     * @return The events nEventProperties
     */
    DLL nEventProperties* getProperties();
    /**
     * Returns the byte array data payload of the event
     *
     * @param dataLength the length of the returned byte array
     * @return unsigned char* of user data
     */
    unsigned char* getData(int& dataLength);
    /**
     * Sets the byte array data payload for the event
     *
     * @param *pData a byte array to be sent
     * @param dataLength the length of pData
     */
    void setData(unsigned char* pData, int dataLength);
    /**
     * Returns the time in milliseconds since the last change was made to the event. If no change then the function
     * will return 0
     *
     * @return time in milliseconds since the last change
     */
    longlong timeSinceLastChange();
    /**
     * Returns the number of changes made since the last commitChanges was called
     *
     * @return int number of changes since the last commitChanges
     */
    int getChangeSize();
    /**
     * Writes all changes to the server and resets any internal counts, timers and copies.
     *
     * @param bReplace, if true the server will replace the referenced event with a complete copy of this event and will
     * not merge any data from previous events.
     *
     * @throws nSecurityException            User is not authorised for the function
     * @throws nSessionPausedException       The session is currently paused, please resume
     * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
     * @throws nSessionNotConnectedException Current session is not connected
     * @throws nTransactionException thrown if any transactional errors occur
     * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
     * @throws nChannelNotFoundException     The channel specified could not be found
     * @throws nUnexpectedResponseException  Internal Error has occured, since we received a response from the server out of sequence
     */
    DLL void commitChanges(bool bReplace = false);

  protected:
    nDataGroup* getDataGroup();

    /**
     * Writes all changes to the server and resets any internal counts, timers and copies
     *
     * @param bReplace, if true the server will replace the referenced event with a complete copy of this event and will
     * not merge any data from previous events.
     *
     * @throws nSecurityException            User is not authorised for the function
     * @throws nSessionPausedException       The session is currently paused, please resume
     * @throws nIllegalArgumentException     Illegal parameter, check the message for more information
     * @throws nSessionNotConnectedException Current session is not connected
     * @throws nRequestTimedOutException     The server has not responded to the request in the timeout period
     * @throws nUnexpectedResponseException  Internal Error has occured, since we received a response from the server out of sequence
     */
    nConsumeEvent* getChangedEvent(bool bReplace);

    std::string m_keyName;

  private:
    void processChanges(nEventProperties *pProps, std::string key, fObject *pVal);
    void registerListener(nEventProperties *pProps, const std::string& path);
    void addToProperties(nEventProperties *pProps, const std::string& key, fObject *pVal);

    nEventProperties *m_pMainProps;
    fSortedList<std::string, fObject*> m_changedProps;
    unsigned char *m_pData;
    int m_dataLength;
    std::string m_tag;

    fObject *m_pKeyValue;
    EventSink *m_pSource;
    bool m_bTransactional;
    longlong m_lastUpdate;

    friend class UpdateListener;
    friend class EventSink;
    friend class nSession;
};

}
}
}
}
