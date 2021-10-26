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

class nEventListener;
class nChannel;
class nBaseClientException;

using namespace foundation::fbase;
/**
 * This class represents the attributes used for channel subscriptions. It comprises of
 * the channel name, an optional selector, an initial event id, and the listener that will
 * receive the callback for events consumed.
 *
 * This object can be used in conjunction with the nSession.subscribe method that accepts
 * an array of nSubscriptionAttributes objects. Once the method returns from the server,
 * the nSubscriptionAttributes objects can be validated, by checking the wasSuccessful() method.
 *
 * If wasSuccessful() returns true, the nChannel object can be obtained from calling nSubscriptionAttributes.getChannel().
 * If wasSuccessful() returns false, an exception will be found by calling nSubscriptionAttributes.getException()
 *
 * @since 6.0
 */
class nSubscriptionAttributes : public Countable {
  public:
    /**
     * Constructor for setting up the attributes for a subscription to a channel
     *
     * @param name - the full name of the channel
     * @param selector - an optional selector provided for event filtering
     * @param eid - an initial start event id
     * @param *pEventCallback - the nEventListener that will receive the callback when events are published
     * @throws nIllegalArgumentException
     */
    DLL nSubscriptionAttributes(const std::string& name, const std::string& selector, longlong eid, nEventListener *pEventCallback);
    virtual ~nSubscriptionAttributes(void);

    /**
     * Return the name of the channel
     * @return channel name
     */
    virtual const std::string& getChannelName();
    /**
     * Return the selector for event event filtering on this subscription
     * @return the selector string
     */
    virtual const std::string& getSelector();
    /**
     * Return the event id that the subscription will start from
     * @return the event id to start
     */
    virtual longlong getEID();
    /**
     * Return the nEventListener associated with this subscription
     * @return the callback listener
     */
    virtual nEventListener* getListener();
    /**
     * Return whether the channel has been successfully found and subscribed to
     * @return true or false
     */
    virtual bool wasSuccessful();
    /**
     * Returns the valid nChannel object resulting from the subscription request
     * @return an instance of nChannel corresponding to the channel subscribed to
     */
    virtual nChannel* getChannel();
    /**
     * If the channel subscription failed, this method will return a subclass of
     * nBaseClientException that will detail the cause of the failure
     *
     * @return instance of : nSecurityException, nChannelNotFoundException or nIllegalChannelMode
     */
    virtual nBaseClientException* getException();

  protected:
    virtual void setChannel(nChannel *pChannel);
    virtual void setException(nBaseClientException *pException);

  private:
    std::string m_channelName;
    std::string m_selector;
    longlong m_EID;
    nEventListener *m_pCallback;
    nChannel *m_pChannel;
    nBaseClientException *m_pException;

    friend class FindAndSubscribeCallback;
};

}
}
}
}
