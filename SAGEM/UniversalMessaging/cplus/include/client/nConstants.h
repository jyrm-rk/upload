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
#include "fConnectionSettings.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
using namespace com::pcbsys::foundation::io;

/**
 * This class is a container for the various constants that affect the behaviour of
 * various Nirvana Client API calls.
 */
class DLL nConstants {
  public:
    virtual ~nConstants(void);

	nConstants(void);

	/**
	* Specifies the CHANNEL DELETED event ID received as result of channel deletion
	* This event is send only when async subscriber is used
	*/
	static const int CHAN_DELETED_EVENT_ID = -2;

    /**
    * Sets the path to the pem certificate used for SSL client authentication
    */
    static void SetCertificatePath (const std::string& certificatePath);

    /**
    * Sets the password for the pem certificate used for SSL client authentication
    */
    static void SetCertificatePassword (const std::string& certificatePassword);

    /**
    * Sets the path to the CA
    */
    static void SetCAPath (const std::string& CAPath);

    /**
    * Specify a file for the client log messages.  Defaults to stdout.
    */
    static void setClientLogFile(FILE* file);

    /**
    * Return the certificate path used for SSL client authentication
    */
    static const std::string& GetCertificatePath ();

    /**
    * Return the certificate password for the SSL client certificate used for authentication
    */
    static const std::string& GetCertificatePassword ();

    /**
    * Return the CA path
    */
    static const std::string& GetCAPath ();

    /**
     * Returns the configured algoritmgs to use for SSL
     */
    static const std::string& GetAlgorithm();

    /**
     * Returns the configured algoritmgs to use for SSL
     */
    static void SetAlgorithm(const std::string& algorithm);

    /**
     * If set to true then there will be no SSL certificate validation, this is not recommended for production
     * and should only be used during debug
     */
    static void SetRelaxedSSLVerification(bool flag);

    /**
     * If set to true then there will be no SSL certificate validation, this is not recommended for production
     * and should only be used during debug
     */
    static bool GetRelaxedSSLVerification();


    /**
    * Sets the number of keep alives that the client can miss before closing the connection. If 0, the client
    * does not check for any missed keep alives from the server and will continue sending its own
    * keep alive events, until the connection is detected as lost. If > 0, say 1, when the client has not
    * received a message for 1 X the KeepAlive time + 20000ms, the underlying connection will be closed by
    * the client and reconnection will be attempted.
    *
    * @param kas Number of keep alive messages the client will miss before determining the connection as broken.
    */
    static void setPermittedKeepAlivesMissed(int kas);

    /**
    * This returns the current value for the Initial socket connect timeout. This timeout is specified in the actual
    * underlying Socket connect, and enables connections made to non existent or unreachable hosts to be returned within
    * a configurable time frame
    *
    * @return the socket connect timeout value, default is 30000ms
    */

    static int getInitialConnectionTimeout();

    /**
    * This sets the current value for the Initial socket connect timeout. This timeout is specified in the actual
    * underlying Socket connect, and enables connections made to non existent or unreachable hosts to be returned within
    * a configurable time frame.
    *
    * @param timeout the socket connect timeout value to be set, default is 30000ms
    */

    static void setInitialConnectionTimeout(int timeout);

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
    * 2. The realm is really so busy that it has not managed to respond to your request
    * within the specified maximum interval.
    * </p>
    *
    * @return a long specifying the maximum wait time for a protocol request (in ms)
    */

    static long getEVENTWAIT();

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
    * 2. The realm is really so busy that it has not managed to respond to your request
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
     * Converts milliseconds (time since EPOCH) into a time object;
     * @param millis time since EPOCH
     * @return time_t representation of millis
     */
    static time_t milliToDateTime(longlong millis);


    /**
    * Retrieves the subscriber queue low watermark. Each Nirvana subscriber uses
    * a queue to store events retrieved from the server prior to performing the
    * callback to the registered event listeners. When the queue reaches the high
    * watermark the subscription is suspended to allow the event listener to catch
    * up and control the amount of memory used on the client. When the queue reaches
    * the low watermark, the subscription is automatically resumed.
    *
    * @return an int specifying the number of events to be used as a queue low watermark
    */

    static int getSubLowWater();

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
    * Retrieves the subscriber queue high watermark. Each Nirvana subscriber uses
    * a queue to store events retrieved from the server prior to performing the
    * callback to the registered event listeners. When the queue reaches the high
    * watermark the subscription is suspended to allow the event listener to catch
    * up and control the amount of memory used on the client. When the queue reaches
    * the low watermark, the subscription is automatically resumed.
    *
    * @return an int specifying the number of events to be used as a queue high watermark
    */

    static int getSubHighWater();

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
    * Returns the outbound publish queue high watermark. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * @return the outbound connection queue high water mark
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static int getConnectionQueueHighWater();

    /**
    * Sets the outbound publish queue high watermark. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * @param high the outbound connection queue high water mark
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static void setConnectionQueueHighWater(int high);

    /**
    * Returns the outbound publish queue low watermark. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * @return the outbound connection queue low water mark
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static int getConnectionQueueLowWater();

    /**
    * Sets the outbound publish queue low watermark. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * @param low the outbound connection queue low water mark
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static void setConnectionQueueLowWater(int low);

    /**
    * Returns the outbound publish queue block weighting. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a configurable period.
    * The connection block weighting is a value that is applied to the block wait value in order to control the frequency of these notifications.
    *
    * @return the connection queue block weighting
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static int getConnectionBlockWeighting();

    /**
    * Sets the outbound publish queue block weighting. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a configurable period.
    * The connection block weighting is a value that is applied to the block wait value in order to control the frequency of these notifications.
    *
    * @param blockWeighting the connection queue block weighting
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static void setConnectionBlockWeighting(int blockWeighting);

    /**
    * Sets the outbound publish queue block wait time. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a configurable period.
    * This period is called the block wait time
    *
    * @param p_blockWait the connection queue block wait
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static void setBlockLimit(int p_blockWait);

    /**
    * Sets the outbound publish queue access wait time. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a period of time that the queue cannot be accessed.
    * This period is called the block access time
    *
    * @param p_accessWait the connection queue access wait
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static void setAccessWaitLimit(int p_accessWait);

    /**
    * Sets the outbound publish queue push wait time. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a period of time that events cannot be pushed to the queue.
    * This period is called the push wait time
    *
    * @param p_pushWait the connection queue push wait
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static void setPushWaitLimit(int p_pushWait);

    /**
    * Returns the outbound publish queue push wait time. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a period of time that events cannot be pushed to the queue.
    * This period is called the push wait time
    *
    * @return the connection queue push wait
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static int getPushWaitLimit();

    /**
    * Returns the outbound publish queue access wait time. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a period of time that the queue cannot be accessed.
    * This period is called the block access time
    *
    * @return the connection queue access wait
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static int getAccessWaitLimit();

    /**
    * Returns the outbound publish queue block wait time. Each Nirvana session that sends events to the server
    * (e.g. publishers) place events into an outbound queue to be sent to the server. When the queue reaches the high
    * watermark the queue is unavailable to the client session until the queue reaches it's low water mark, i.e.
    * the events are delivered to the server. When the low water mark is reached the queue
    * is automatically resumed.
    *
    * When an outbound queue becomes blocked (unavailable) it is possible to become notified after a configurable period.
    * This period is called the block wait time
    *
    * @return the connection queue block wait
    * @see com.pcbsys.nirvana.client.nConnectionQueueListener
    */

    static int getBlockLimit();

    /**
     * Returns whether a nirvana nSession will attempt to reconnect to the realm
     * after the realm ACL has been revoked. By default, the nSession will not reconnect
     * after one of these incidents, and a manual restart would need to be initiated
     *
     * @return true if reconnect is enabled after realm ACL subject revocation
     */
    static bool attemptReconnectAfterAccessChange();

    /**
     * Sets whether a nirvana nSession will attempt to reconnect to the realm
     * after the realm ACL has been revoked. By default, the nSession will not reconnect
     * after one of these incidents, and a manual restart would need to be initiated
     *
     * @param recon true - will reconnect continually until successful, false, will disabled reconnect
     */
    static void setReconnectAfterAccessChange(bool recon);

    /**
     * Returns whether a nirvana nSession will attempt to immediately reconnect or whether reconnection attempts
     * will back off over time to prevent a network storm where multiple re-connections
     * can occur all at once
     *
     * @return true if reconnect immediately is enabled
     */
    static bool attemptReconnectImmediately();

    /**
     * Sets whether a nirvana nSession will attempt to immediately reconnect or whether reconnection attempts
     * will back off over time to prevent a network storm where multiple re-connections
     * can occur all at once
     *
     * @param recon true - will reconnect immediately, and use the value set in
     * @since 4.0
     */
    static void setReconnectImmediately(bool recon);

    /**
     * Returns the interval value to use between reconnect attempts when the
     * session is set to reconnect immediately
     *
     * @return true if reconnect immediately is enabled
     * @since 4.0
     */
    static long getReconnectInterval();

    /**
     * Returns the interval value to use between reconnect attempts when the
     * session is set to reconnect immediately
     *
     * @param interval value in milliseconds specifying the interval between reconnect attempts
     * @since 4.0
     */
    static void setReconnectInterval(long interval);

    /**
     * Sets the log level for the client. All Nirvana client api code contains useful logging messages. The messages are set at specific levels from 0-7.
     * This method allows you to choose what log level you wish to see. Setting to log level 0 will provide verbose output, whereas level 7 will be fairly quiet.
     *
     * By default, these messages will be sent to the console output
     *
     * @param level the log level you wish to set the client application to for nirvana messages
     */
    static void setClientLogLevel(int level);

    /**
     *  Return an Epoch Date in milliseconds representing the current system date / time
     *  @return Epoch time as a long
     */
    static longlong currentTimeMillis();

    /**
     *  Return current time in nanoseconds
     *  @return current time in nanoseconds
     */
    static longlong nanoTime();

    /**
     *  Decode the array into a string
     *  @param pBuffer the array to decode
     *  @param size the size of the array
     *  @param str the string to decode into
     */
    static void decode (unsigned char *pBuffer, int size, std::string& str);

    /**
     *  Encode the string into an array
     *  @param str the string to encode
     *  @param size the size of the array
     *	@return the encoded array
     */
    static unsigned char* encode (const std::string& str, unsigned int& size);

    /**
     *  Compare 2 strings for equality
     *  @param string1 the 1st string in comparison
     *  @param string2 the 2nd string in comparison
     *	@return result of string1.compare(string2)
     */
    static int compareNoCase (const std::string& string1, const std::string& string2);

    /**
    * Sets the proxy host & port used for http (nhp) communication
    */
    static void SetProxy (const std::string& host, int& port);

    /**
    *  This write handler uses a combination of direct writing and buffered writing to the network
    * depending on client event load
    */
    static const int m_sStandardWriteHandler = fConnectionSettings::sPeakWriteHandler;

    /**
    * This write handler only uses a direct write method to the network layer, this reduces latencies but
    * may increase the cpu used
    */
    static const int m_sDirectWriteHandler = fConnectionSettings::sDirectWriteHandler;

    /**
    *  Allows the client to specify the type of write handling that the client code will employ. Please note
    * this needs to be set prior to any nSession creation.
    *
    * @param type Either sStandardWriteHandler or sDirectWriteHandler
    */
    static void setWriteHandlerType(int type);

    /**
    * Returns the current write handling mode that the client is using
    *
    * @return an int of either sStandardWriteHandler or sDirectWriteHandler
    */
    static int getWriteHandlerType();

    /**
    * Sets the value in ms to wait before sending a Keep Alive.
    * This is applied to the local client only and is NOT sent to the realm.
    */

    static void setKeepAliveInterval(long newVal);

    /**
    * Gets the value in ms to wait before sending a Keep Alive.
    * This is relevant to the local client only.
    */

    static long getKeepAliveInterval();
    static int getHTTPRequestTimeout();
    static void setHTTPRequestTimeout(int newVal);

    /**
    * Sets the number of events that are still to ve delivered to the client
    * @param queueSize number of events that the queue will hold before blocking
    */

    static void setDataGroupQueueSize(int queueSize);

    /**
    *
    *
    * @return The current data group event queue size
    */

    static int getDataGroupQueueSize();

    /**
     * Returns true if the client will maintain third party cookies
     */
    static bool honourThirdPartyCookies();

    /**
     * If honourThirdPartyCookies is set to true then the client will maintain
     * any third party cookies.
     * @param doHonour if true the client will maintain third party cookies.
     * @since 6.1
     */
    static void setHonourThirdPartyCookies(bool doHonour);

    /**
     * Enable the usage of priority queues for this client. This will give delivery preference to messages marked high priority for this client.
     *
     * @param enabled boolean true will enable priority queueing for this client, false will disable it.
     */
    static void setEnabledPriorityQueues(bool enabled);

    /**
     * Get whether priority queueing is enabled for this client.
     *
     * @return true if priority queueing is enabled for this client, false otherwise.
     */
    static bool getEnabledPriorityQueues();

    /**
    * Set the inbound socket buffer size
    *
    * @param bufSize the size in bytes for the inbound buffer size
    */
    static void setSocketReceiveBufferSize(int bufSize);

    /**
     * Set the outbound socket buffer size
     *
     * @param bufSize the size in bytes for the outbound buffer size
     */
    static void setSocketSendBufferSize(int bufSize);

    /**
     * Get the inbound socket buffer size
     *
     * @return the size in bytes for the inbound buffer size
     */
    static int getSocketReceiveBufferSize();

    /**
     * Get the outbound socket buffer size
     *
     * @return the size in bytes for the outbound buffer size
     */
    static int getSocketSendBufferSize();

	/**
	* Get the client build number information
	*
	* @return the client build number information as a string
	*/
	static const std::string& getClientBuildNumber();

  private:
    static std::string m_sCertificatePath;
    static std::string m_sCertificatePassword;
    static std::string m_sCAPath;
    static std::string m_sCipherList;
    static bool m_sslRelaxed;
};

}
}
}
}

