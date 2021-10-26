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
namespace nbase {

/**
 * This class is a container for the various constants that affect the behaviour of
 * various Nirvana Client API calls.
 */
class nBaseConstants {
  public:
    nBaseConstants(void);
    virtual ~nBaseConstants(void);

    static void setReconnectImmediately(bool newval);

    /**
     * Returns whether a nirvana nSession will attempt to immediately reconnect or whether reconnection attempts
     * will back off over time to prevent a network storm where multiple re-connections
     * can occur all at once
     *
     * @return true if reconnect immediately is enabled
     */
    static bool getReconnectImmediately();
    static void setReconnectInterval(long newval);

    /**
     * Returns the interval value to use between reconnect attempts when the
     * session is set to reconnect immediately
     *
     * @return true if reconnect immediately is enabled
     * @since 4.0
     */
    static long getReconnectInterval();

    /**
     * This is the maximum time the client API will wait for a response to a specific
     * request from the Nirvana realm. The default value is 60 secs and typically if
     * you get a nRequestTimedOutException the cause would be:
     *
     * <p>
     * 1. There is a protocol mismatch between the client library in use and server
     * you are connected to.
     * </p>
     * <p>
     * 2. The realm is really so busy that has not managed to respond to your request
     * within the specified maximum interval.
     * </p>
     *
     * Calling this method will only have effect on the local client. Alternatively if
     * you change this value through on the realm configuration using the Admin API,
     * all subsequent Nirvana clients that connect will be affected.
     *
     */
    static void setEVENTWAIT(long newval);

    /**
     * This is the maximum time the client API will wait for a response to a specific
     * request from the Nirvana realm. The default value is 60 secs and typically if
     * you get a nRequestTimedOutException the cause would be:
     *
     * <p>
     * 1. There is a protocol mismatch between the client library in use and server
     * you are connected to.
     * </p>
     * <p>
     * 2. The realm is really so busy that has not managed to respond to your request
     * within the specified maximum interval.
     * </p>
     *
     * @return a long specifying the maximum wait time for a protocol request (in ms)
     */
    static long getEVENTWAIT();
    static void setTXPUBWAIT(long newval);

    /**
     * Sets the subscriber queue low watermark. Each Nirvana subscriber uses
     * a queue to store events retrieved from the server prior to performing the
     * callback to the registered event listeners. When the queue reaches the high
     * watermark the subscription is suspended to allow the event listener to catch
     * up and control the amount of memory used on the client. When the queue reaches
     * the low watermark, the subscription is automatically resumed.
     *
     * @param low the low water ,ark for the subscriber
     */
    static void setSubLowWater(int low);

    /**
     * Retrieves the subscriber queue low watermark. Each Nirvana subscriber uses
     * a queue to store events retrieved from the server prior to performing the
     * callback to the registered event listeners. When the queue reaches the high
     * watermark the subscription is suspended to allow the event listener to catch
     * up and control the amount of memory used on the client. When the queue reaches
     * the low watermark, the subscription is automatically resumed.
     *
     * @return an int specifiying the number of events to be used as a queue low watermark
     */
    static int getSubLowWater();

    /**
     * Sets the subscriber queue high watermark. Each Nirvana subscriber uses
     * a queue to store events retrieved from the server prior to performing the
     * callback to the registered event listeners. When the queue reaches the high
     * watermark the subscription is suspended to allow the event listener to catch
     * up and control the amount of memory used on the client. When the queue reaches
     * the low watermark, the subscription is automatically resumed.
     *
     * @param high sets the subscriber high water mark
     */
    static void setSubHighWater(int high);

    /**
     * Retrieves the subscriber queue high watermark. Each Nirvana subscriber uses
     * a queue to store events retrieved from the server prior to performing the
     * callback to the registered event listeners. When the queue reaches the high
     * watermark the subscription is suspended to allow the event listener to catch
     * up and control the amount of memory used on the client. When the queue reaches
     * the low watermark, the subscription is automatically resumed.
     *
     * @return an int specifiying the number of events to be used as a queue high watermark
     */
    static int getSubHighWater();

    /**
     * Returns whether a nirvana nSession will attempt to reconnect to the realm
     * after the realm ACL has been revoked. By default, the nSession will not reconnect
     * after one of these incidents, and a manual restart would need to be initiated
     *
     * @return true if reconnect is enabled after realm ACL subject revocation
     */
    static bool doReconnectAfterACLRevoked();
    static void setReconnectAfterACLRevoked(bool recon);

    static std::string validate(std::string& name);

    static longlong nanoTime();
    static longlong currentTimeMillis();

    static int getInitialConnectionTimeout();
    static void setInitialConnectionTimeout(int timeout);
    static int getConnectionQueueHighWater();
    static void setConnectionQueueHighWater(int high);
    static int getConnectionQueueLowWater();
    static void setConnectionQueueLowWater(int low);
    static int getConnectionBlockWeighting();
    static void setConnectionBlockWeighting(int low);
    static void setBlockLimit(int blockWait);
    static int getBlockLimit();
    static void setAccessWaitLimit(int accessWait);
    static int getAccessWaitLimit();
    static void setPushWaitLimit(int pushWait);
    static int getPushWaitLimit();
    static std::string validateMountPoint(std::string& name);
    static void setKeepAliveInterval(long newVal);
    static long getKeepAliveInterval();
    static bool isOldMergeBehaviour();
    static void setOldMergeBehaviour(bool oldMergeBehaviour);

    static int findNextPowerOfTwo(int value);

    static void setPermittedKeepAlivesMissed(int kas);


    static const int CHAN_MODE_NORMAL = 100;
    static const int CHAN_MODE_QUEUE  = 101;

    static const int CHAN_RELIABLE    = 1;
    static const int CHAN_PERSISTENT  = 2;
    static const int CHAN_MIXED       = 3;

	static const int DICTIONARY_STAMPING_ENABLED = 1;
	static const int DICTIONARY_STAMPING_DISABLED = -1;
	static const int DICTIONARY_STAMPING_DEFAULT = 0;

    static const int SERVER_DEFAULT_STORE_EVENTS_PER_SPINDLE = 0;
	static const bool SERVER_DEFAULT_STORE_CAPACITY_HONORING = false;
	static const bool SERVER_DEFAULT_STORE_AUTO_MAINTANANCE = false;

    static const std::string sRealmSpecific;
    static const std::string sStatusChannelName;
    static const std::string sTXChannelName;

    static bool honourThirdPartyCookies();
    static void setHonourThirdPartyCookies(bool doHonour);

    static void parkNanos(int nanos);

  private:
    static std::string checkName(std::string& name);

    static bool sReconnectImmediately;
    static long sReconnectInterval;
    static bool sReconnectAfterAccessRevoked;
    static long EVENTWAIT;
    static long TXPUBWAIT;
    static int sSubLowWater;
    static int sSubHighWater;
    static bool sOldMergeBehaviour;
    static bool sHonourThirdPartyCookies;
};

}
}
}
}

