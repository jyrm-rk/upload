/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NMULTICASTCONFIGURATION_H
#define NMULTICASTCONFIGURATION_H

#include "nInterface.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fMulticastConfig;
}
}
}
namespace nirvana {
namespace nAdminAPI {
using namespace com::pcbsys::foundation::drivers::configuration;

class nMulticastConfigurationStatus;
class nMulticastConfiguration : public nInterface, public CountableObject {
  public:
    static const std::string* DigestNames;
    static const int DigestNamesLen;
    static const std::string* EncryptionLevel;
    static const int EncryptionLevelLen;

    /**
     * Creates a new multicast configuration with the supplied values
     *
     * @param multicastAddress The multicast address to use to bind to
     * @param adapter the address of the adapter to bind the multicast too.
     * @param enabled Specifies whether to enable this configuration. Default = true;
     * @throws nAdminIllegalArgumentException if
     */
    DLL nMulticastConfiguration(std::string multicastAddress, std::string adapter, bool enabled=true);

    /**
    * Returns the multicast address for this configuration
    *
    * @return std::string of the address
    */
    DLL std::string getMulticastAddress();

    /**
     * Sets the multicast address for this configuration
     *
     * @param multicastAddress as a std::string
     * @throws nAdminIllegalArgumentException if an invalid multicast address is used
     */
    DLL void setMulticastAddress(std::string multicastAddress);

    /**
     * Gets the allowable size of the outstanding packets queue on the sending side.
     *
     * These packets are outstanding from receivers to be acknowledge
     *
     * @return OutstandingPacketsQueueSize as a int
     */
    DLL int getOutstandingPacketsQueueSize();

    /**
    * Sets the allowable size of the outstanding packets queue on the sending side.
    * These packets are outstanding from receivers to be acknowledge
    *
    * @param outstandingPacketsQueueSize as a int
    */

    DLL void setOutstandingPacketsQueueSize(int outstandingPacketsQueueSize);

    /**
     * Returns the number of packets before sending an ack for received events
     *
     * @return ackWindowSize as a int
     */
    DLL int getAckWindowSize();

    /**
    * Sets the number of packets before sending an ack for received events
    *
    * @param ackWindowSize ackWindowSize as a int
    */
    DLL void setAckWindowSize(int ackWindowSize);

    /**
     * Returns the number of outstanding packets allowed to be on the wire without acknowledgement.
     *
     * @return int amount of packets on the wire.
     */
    DLL int getUnAckedWindowSize();

    /**
    * Returns the number of outstanding packets allowed to be on the wire without acknowledgement.
    *
    * @param unAckedWindowSize amount of packets on the wire.
    */
    DLL void setUnAckedWindowSize(int unAckedWindowSize);

    /**
     * Returns the packet count to wait before rotating the new encryption key into use.
     *
     * @return int packet count
     */
    DLL int getRotateEncryptionKeyCount();

    /**
     * Sets the packet count to wait before rotating the new encryption key into use.
     * @param rotateEncryptionKeyCount int
     */
    DLL void setRotateEncryptionKeyCount(int rotateEncryptionKeyCount);

    /**
     * Returns the time between encryption key changes.
     *
     * @return int the encryption key rotation time
     */
    DLL int getRotateEncryptionKeyTime();

    /**
     * Sets the time between encryption key changes.
     *
     * @param rotateEncryptionKeyTime int
     */
    DLL void setRotateEncryptionKeyTime(int rotateEncryptionKeyTime);

    /**
     * Returns the CRC type for guaranteed data integrity, will need to be compared to nMulticastConfiguration.DigestNames.
     *
     * Possible values are:
     * nMulticastConfiguration.DigestNames[0], disables CRC checking.
     * nMulticastConfiguration.DigestNames[1], uses CRC32 for CRC checks.
     * nMulticastConfiguration.DigestNames[2], uses MD5 digest for CRC checks.
     * nMulticastConfiguration.DigestNames[3], uses SHA-5 digest for CRC checks.
     *
     * @return returns a unsigned char of CRC type
     */
    DLL unsigned char getCRCType();

    /**
     * Sets the CRC type for guaranteed data integrity, will need to be compared to nMulticastConfiguration.DigestNames.
     *
     * Possible values are:
     * 0, disables CRC checking.
     * 1, uses CRC32 for CRC checks.
     * 2, uses MD5 digest for CRC checks.
     * 3, uses SHA-5 digest for CRC checks.
     *
     * @param CRCType one of the DigestNames
     * @throws nAdminIllegalArgumentException if CRCType outside of possible values
     */
    DLL void setCRCType(unsigned char CRCType);

    /**
     * Returns the encryption level, can be one of nMulticastConfiguration.EncryptionLevel
     *
     * Possible values are:
     * nMulticastConfiguration.EncryptionLevel[0], disables encryption.
     * nMulticastConfiguration.EncryptionLevel[1], uses AES-128 encryption.
     * nMulticastConfiguration.EncryptionLevel[2], uses AES-192 encryption.
     * nMulticastConfiguration.EncryptionLevel[3], uses AES-256 encryption.
     *
     * @return unsigned char encryption level
     */
    DLL unsigned char getEncryptionLevel();

    /**
     * Sets the encryption level, can be one of nMulticastConfiguration.EncryptionLevel
     *
     * Possible values are:
     * nMulticastConfiguration.EncryptionLevel[0], disables encryption.
     * nMulticastConfiguration.EncryptionLevel[1], uses AES-128 encryption.
     * nMulticastConfiguration.EncryptionLevel[2], uses AES-192 encryption.
     * nMulticastConfiguration.EncryptionLevel[3], uses AES-256 encryption.
     *
     * @param encryptionLevel one of the above possible values
     * @throws nAdminIllegalArgumentException if encryptionLevel outside of possible values
     */
    DLL void setEncryptionLevel(unsigned char encryptionLevel);

    /**
     * Returns the interval in milliseconds between flushes to the wire for packets.
     *
     * Higher intervals increase latency and throughput.
     *
     * @return int flusher interval
     */
    DLL int getFlusherInterval();

    /**
     * Sets the interval in milliseconds between flushes to the wire for packets.
     *
     * Higher intervals increase latency and throughput.
     *
     * Minimum time between flushes is 1ms
     *
     * @param flusherInterval the time between flushes.
     * @throws nAdminIllegalArgumentException if flusherInterval less than 1
     */
    DLL void setFlusherInterval(int flusherInterval);

    /**
     * Returns the interval between keep alive messages sent.
     *
     * @return int keep alive interval in milliseconds
     */
    DLL int getKeepAliveInterval();

    /**
     * Sets the interval between sending of keep alive messages, must be greater than 0.
     *
     * @param keepAliveInterval interval in milliseconds
     * @throws nAdminIllegalArgumentException if keepAliveInterval less than 1
     */
    DLL void setKeepAliveInterval(int keepAliveInterval);

    /**
     * Returns the number of allowable unprocessed packets on the receiving side whilst rebuilding missed or out of order packets.
     *
     * @return int maxOutstandingPackets
     */
    DLL int getMaxOutstandingPackets();

    /**
     * Sets the number of allowable unprocessed packets on the receiving side whilst rebuilding missed or out of order packets.
     * @param maxOutstandingPackets int
     */
    DLL void setMaxOutstandingPackets(int maximumOutstandingPackets);

    /**
     * Returns the quantity of Nirvana messages per second that when exceeded will enable peak writing mode.
     *
     * @return int Nirvana messages per second for peak writing.
     */
    DLL int getPeakRate();

    /**
     * Sets the quantity of Nirvana messages per second that when exceeded will enable peak writing mode.
     *
     * @param messagesPerSecond Nirvana messages per second for peak writing.
     */
    DLL void setPeakRate(int messagesPerSecond);

    /**
     * Gets the flag to allow use of this configuration in a cluster
     *
     * @return boolean indicating if its enabled or not
     */
    DLL bool isUseForCluster();

    /**
     * Sets the flag to allow use of this configuration in a cluster
     * @param useForCluster boolean indicating whether to use for clustering or not
     */
    DLL void setUseForCluster(bool useForCluster);

    /**
    * Gets the flag to allow use of this configuration for datagroups
    *
    * @return boolean indicating if its enabled or not
    */
    DLL bool isUseForDataGroups();

    /**
     * Sets the flag to allow use of this configuration for datagroups
     * @param useForDataGroups boolean indicating whether to use for channels or not
     */
    DLL void setUseForDataGroups(bool useForDataGroups);

    /**
    * Gets the flag to allow use of this configuration for channels
    *
    * @return boolean indicating if its enabled or not
    */
    DLL bool isUseForChannels();

    /**
     * Sets the flag to allow use of this configuration for channels
     * @param useForChannel boolean indicating whether to use for channels or not
     */
    DLL void setUseForChannel(bool useForChannel);

    /**
     * The time to wait for a client to establish multicast, if they do not receive any multicast data within this time its assumed they are unable to use multicast.
     *
     * @return the time in seconds to wait before removing a client from multicast.
     */
    DLL long getClientEstablishmentTimeout();

    /**
     * The time to wait for a client to establish multicast, if they do not receive any multicast data within this time its assumed they are unable to use multicast.
     * @param clientEstablishmentTimeout seconds to wait before removing a client from trying multicast
     */
    DLL void setClientEstablishmentTimeout(long clientEstablishmentTimeout);

    /**
     * Returns the adapter that will be bound too for sending multicast.
     * @return the adapter address for multicast to bind on.
     */
    DLL const std::string& getAdapter();

    /**
     * Sets the adapter to bind the multicast server to.
     * @param adapter the local adapters IP address for multicast to bind to
     * @throws nAdminIllegalArgumentException if an invalid address is given
     */
    DLL void setAdapter(std::string adapter);

    /**
     * Returns the size of the adapter buffers to use for both sending and receiving of packets
     * @return int adapter buffer size in unsigned chars
     */
    DLL int getAdapterBufferSize();

    /**
     * Sets the size of the adapter buffers to use for both sending and receiving of packets
     * @param adapterBufferSize int size fo adapter buffer in unsigned chars
     */
    DLL void setAdapterBufferSize(int adapterBufferSize);

    /**
     * Returns the multicast traffic class set for this configuration
     * @return unsigned char multicast traffic class
     */
    DLL unsigned char getTrafficClass();

    /**
     * Returns the multicast traffic class set for this configuration
     * @param myQOS multicast traffic class
     */
    DLL void setTrafficClass(unsigned char QOS);

    /**
     * Maximum data size for a datagram, excludes the datagram headers
     * @return int maximum datagram size
     */
    DLL int getPacketSize();

    /**
     * Maximum data size for a datagram, excludes the datagram headers
     * @param myPacketSize int maximum packet size
     */
    DLL void setPacketSize(int PacketSize);

    /**
     * Returns the length of the session ID used for ensuring integrity and increasing security of data
     * @return int the length of the session ID
     */
    DLL int getUniqueSessionIDSize();

    /**
     * Sets the length of the session ID used for ensuring integrity and increasing security of data
     * @param myUniqueSessionIDSize the length of the session ID
     */
    DLL void setUniqueSessionIDSize(int UniqueSessionIDSize);

    /**
     * Returns the TTL for the multicast socket, this is the count of hops a datagram can traverse before being dropped.
     * @return short of hops before dropping packet
     */
    DLL short getTTL();

    /**
     * Sets the TTL for the multicast socket, this is the count of hops a datagram can traverse before being dropped.
     * @param myTTL short count of hops to traverse
     */
    DLL void setTTL(short TTL);


  private:
    std::string myMulticastAddress;

    //
    // Client specific
    //
    int myOutstandingPacketsQueueSize;
    //int myActivePort;
    int myAckWindowSize;

    //
    // Server specific
    //
    long myClientEstablishmentTimeout;
    int myServerUnAckedWindowSize;
    int myRotateEncryptionKeyCount;
    int myRotateEncryptionKeyTime;
    unsigned char myCRCType;
    unsigned char myEncryptionLevel;
    int myFlusherInterval;
    int myKeepAliveInterval;
    int maxOutstandingPackets;
    int myPeakTime;
    int myPeakTimeIntervals;
    int myPeakTimeDelay;
    int myPeakTimeThreshold;
    unsigned char myMulticastUse;

    nMulticastConfigurationStatus** myInstances;
    int myInstancesLen;
    int myPacketSize;
    unsigned char myQOS;
    int myAdapterBufferSize;
    int myUniqueSessionIDSize;
    short myTTL;

    void setup();

    int getType();
    void convert(fDriverConfig *pCfg);



  protected:
    nMulticastConfiguration(std::string name, std::string protocol, std::string adapter, std::string multicastAddress, bool autoStart);

    nMulticastConfiguration(fMulticastConfig* cfg, nInterfaceManager* im);

    void updateInfo(fMulticastConfig* cfg);

    nMulticastConfigurationStatus* findInstance(std::string name);

    void putInstance(nMulticastConfigurationStatus* status);

    void setMulticastUseFlag(bool useFor, unsigned char bit);

    fDriverConfig* convert();

    void convert(fMulticastConfig* cfg);


    friend class nMulticastManager;
    friend class nInterfaceManager;

};


}
}
}
}
#endif
