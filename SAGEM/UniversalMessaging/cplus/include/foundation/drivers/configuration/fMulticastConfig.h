/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FMULTICASTCONFIG_H
#define FMULTICASTCONFIG_H

#include <fDriverConfig.h>
#include "Poco/Net/IPAddress.h"




namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fMulticastConfig : public fDriverConfig {

    /*
    Mapping to super class variables:

      myAdapter = Adapter to bind to, can not be 0.0.0.0

      WriteBufferSize = UDP packet size
      ReadBufferSize = allocated buffer space for the socket, by default it is 1000 * the packet size
      myPort = the initial port to bind to
      myPoolSize = Max port range to use
      myBacklog = QOS byte map
      myAuthTimeOut = Packet TTL
      enableWebSockets = Enable Compression
      selectorPoolSize = Cookie Size;
      allowNIO = Enable Encryption

     */



  private:
    std::string myMulticastAddress;

//
// Client specific
//
    int myOutstandingPacketsQueueSize;
    int myActivePort;
    int myAckWindowSize;

//
// Server specific
//
    longlong myClientEstablishmentTimeout;
    int myServerUnAckedWindowSize;
    int myRotateEncryptionKeyCount;
    int myRotateEncryptionKeyTime;
    unsigned char myMode;
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
    std::string myLocalBindingAdapter;

    void setup();

  public:

    static const unsigned char sNoSignature =0;
    static const unsigned char sCRC32Signature = 1;
    static const unsigned char sMD5Signature = 2;
    static const unsigned char sSHASignature = 3;


    static const unsigned char sNoEncryption = 0;
    static const unsigned char sAES_128 = 1;
    static const unsigned char sAES_192 = 2;
    static const unsigned char sAES_256 = 3;

    static const unsigned char sAckMode = 0;
    static const unsigned char sNackMode = 1;
    static const unsigned char sBroadcast = 2;


    static const int sDigestNamesLen = 4;
    static const std::string sDigestNames[sDigestNamesLen];

    static const int sEncryptionTypeLen = 4;
    static const std::string sEncryptionType[sEncryptionTypeLen];

    static const int sEncryptionLevelLen = 4;
    static const int sEncryptionLevel[sEncryptionLevelLen];

    static const int sEncryptionNameLen = 4;
    static const std::string sEncryptionName[sEncryptionNameLen];

    static std::string sEncryptionAESEncryptionPadding;


    static const unsigned char sClusterUse = 1;
    static const unsigned char sDataGroupUse = 2;
    static const unsigned char sChannelUse = 4;

    fMulticastConfig();

    fMulticastConfig(std::string name, std::string adapter, int port);

    fMulticastConfig(std::string name, std::string adapter, int port, bool autoStart);

    fMulticastConfig(std::string name, std::string protocol, std::string adapter, int port, bool autoStart);

    virtual ~fMulticastConfig() {}

    void update(fMulticastConfig* cfg);

    void update(Observable* obs, void* o) {

    };

    std::string getMulticastAddress();

    void setMulticastAddress(std::string address);

    std::string getBindingAdapter();

    void setBindingAdapter(std::string adapter);

    int getType();

    int getPacketSize();

    void setPacketSize(int size);

    int getAdapeterBufferSize();

    void setAdapterBufferSize(int size);

    int getFirstPort();

    void setFirstPort(int port);

    int getLastPort();

    void setLastPort(int port);

    unsigned char getQOS();

    void setQOS(unsigned char qos);

    short getTTL();

    void setTTL(short ttl);

    int getUnAckedWindowSize();

    void setUnAckedWindowSize(int size);

    int getRotateEncryptionKeyCount();

    void setRotateEncryptionKeyCount(int count);

    int getRotateEncryptionKeyTime();

    void setRotateEncryptionKeyTime(int time);

    unsigned char getSignatureType();

    void setSignatureType(unsigned char type);

    bool enableCompression();

    void setEnableCompression(bool flag);

    unsigned char getEncryptionLevel();

    void setsEncryptionLevel(unsigned char level);

    void setUniqueSessionIdSize(int size);

    int getUniqueSessionIdSize();

    int getFlushInterval();

    void setFlushInterval(int interval);

    int getOutstandingPacketsQueueSize();

    void setOutstandingPacketsQueueSize(int size);

    bool enableEncryption();

    void setEnableEncryption(bool flag);

    int getKeepAliveTime();

    void setKeepAliveTime(int time);

    int getActivePort();

    void setActivePort(int port);

    int getMaxOutstandingPackets();

    void setMaxOutstandingPackets(int size);

    int getPeakTime();

    void setPeakTime(int myPeakTime);

    int getPeakTimeIntervals();

    void setPeakTimeIntervals(int myPeakTimeIntervals);

    int getPeakTimeDelay();

    void setPeakTimeDelay(int myPeakTimeDelay);

    int getPeakTimeThreshold();

    void setPeakTimeThreshold(int myPeakTimeThreshold);

    void setAckWindowSize(int size);

    int getAckWindowSize();

    void setMulticastUse(unsigned char multicastUse);

    unsigned char getMulticastUse();

    longlong getClientEstablishmentTimeout();

    void setClientEstablishmentTimeout(long clientEstablishmentTimeout);

    std::string getLocalBindingAdapter();

    void setLocalBindingAdapter(std::string localBindingAdapter);

    unsigned char getMode();

    void readExternal(fEventInputStream* eis);

    void writeExternal(fEventOutputStream* eos);

    fMulticastConfig* getClone();

};
}
}
}
}
}

#endif

