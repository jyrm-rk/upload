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
#include "fBaseTransportObject.h"
#include "nBaseRealm.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fEventDictionary;
}
}
namespace nirvana {
namespace client {
class nChannelPublishKeys;
}
namespace nbase {

class nBaseRealm;
struct ProtobufDescriptor;

using namespace foundation::fbase;
using namespace client;

class nBaseChannelAttributes :
    public fBaseTransportObject, public CountableObject {
  public:
    nBaseChannelAttributes(void);
    nBaseChannelAttributes(std::string name, int maxEvents, longlong ttl, int type);

    nBaseChannelAttributes(nBaseChannelAttributes& rhs);

    virtual ~nBaseChannelAttributes(void);

    void setChannelMode(int mode);
    int getChannelMode();
    longlong getUniqueId();
    void readExternal (fEventInputStream *pIstream);
    void writeExternal (fEventOutputStream *pOstream);
    void setName(std::string channelName);
    std::string getName();
    void setMaxEvents(int value);
    int getMaxEvents();
    void setTTL(longlong value);
    longlong getTTL();
    void setChannelType(int aType);
    int getChannelType();
    void setUniqueId(longlong id);
    void setPublishKeys(nChannelPublishKeys** ppKeys, int nKey);
    nChannelPublishKeys** getPublishKeys(int& nKey);
    void setClusterWide(bool flag);
    bool isClusterWide();
    void setRealm(nBaseRealm *pRealm);
    std::string getFullName();
    nBaseRealm* getRealm();
    bool isUseJMSEngine();
    void setUseJMSEngine(bool useJMSEngine);
    bool isExternal();
    void setDeadEventHandler(longlong chan);
    bool isEventUpdateEngine();
    void setEventUpdateEngine(bool eventUpdateEngine);
    void setPriority(int priorityLevel);
    int getPriority();
    bool hasMetaData();
    fEventDictionary* getMetaData ();

	std::vector<ProtobufDescriptor*> getProtobufDescriptors();
	void setProtobufDescriptors(const std::vector<ProtobufDescriptor*> & descriptors);

    static std::string sMergeClassname;
    static std::string sSyncOnWrite;
    static std::string sSyncBatchSize;
    static std::string sSyncTime;
    static std::string sHonorCapacity;
    static std::string sPerformMaint;
    static std::string sEnableCaching;
    static std::string sEnableStoreBuffering;
    static std::string sStoreBufferSize;
    static std::string sCacheOnReload;
    static std::string sFanoutArchiveTarget;
    static std::string sResourcePriority;
	static std::string sProtobufDescriptors;
    static std::string sEnableMulticast;
	static std::string sStampDictionary;
	static std::string sMultiFileEventsPerSpindle;

  protected:
    void unpack(unsigned char *pMeta, int metaLength);
    unsigned char* pack(int& metaLength);

    int m_channelMode;
    longlong m_uniqueId;
    int MAXEVENTS;
    longlong TTL;
    int m_type;
    std::string m_name;
    unsigned char *m_pNameBytes;
    unsigned int m_nameLength;
    nBaseRealm *m_pRealm;
    int m_nKey;
    nChannelPublishKeys **m_ppKeys;
    bool m_bIsClusterWide;
    bool m_bUseJMSEngine;
    longlong m_deadEventStoreId;
    bool m_bEventUpdateEngine;
    fEventDictionary *m_pMetaDictionary;
};

}
}
}
}
