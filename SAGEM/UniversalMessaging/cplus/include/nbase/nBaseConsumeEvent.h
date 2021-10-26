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
#include "nQueueTransactionStatus.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nConsumeEvent;
class nEventProperties;
}
namespace nbase {

class nChannelQueue;
class nHeader;

using namespace client;
using namespace events;

class nBaseConsumeEvent {
  public:
    virtual ~nBaseConsumeEvent(void);

    DLL int getEventDataLength();
    DLL longlong getEventID();
    DLL std::string& getEventTag();

    DLL void setProperties(nEventProperties* newProperties);
    DLL unsigned char* getEventData();
    DLL nEventProperties* getProperties();

  protected:
    nBaseConsumeEvent(nEventProperties *pProperties, unsigned char* data, int dataLength);
    nBaseConsumeEvent(const std::string& tag, nEventProperties *pProperties, unsigned char* data, int dataLength);
    nBaseConsumeEvent(unsigned char* tag, int tagLength, nEventProperties *pProperties, unsigned char* data, int dataLength);
    nBaseConsumeEvent(unsigned char* tag, int tagLength, unsigned char* data, int dataLength);
    nBaseConsumeEvent(const std::string& tag, unsigned char* data, int dataLength);
    nBaseConsumeEvent(nEventProperties *pProperties, std::string& tag);
    void setTTL(longlong ttl);
    void setPersistent(bool flag);
    void setEventID(longlong newID);
    void setSignature(unsigned char* sign, int signLength);
    void ack();
    void setHeader(nHeader *pHeader);
    void setTransient(bool transient);
    void rollback();

    bool isPersistent();
    bool isTransient();
    int getSignatureLength();
    longlong getTTL();


    unsigned char* getSignature();
    nHeader* getHeader();

    longlong m_id;
    nChannelQueue *m_pChannel;
    unsigned char* m_pSignature;
    int m_signatureLength;
    bool m_bHasAcked;
    bool m_bIsEndOfChan;
    nHeader *m_pHeader;
    nEventProperties* m_pProperties;
    longlong m_queueReaderId = nQueueTransactionStatus::UNKNOWN_READER_UNIQUE_ID;

  private:

    bool m_bPersist;
    bool m_bTransient;

    int m_eventDataLength;
    int m_eventTagLength;

    longlong m_eventID;
    longlong m_TTL;

    unsigned char* m_pEventData;
    unsigned char* m_pEventTagBytes;
    std::string m_eventTag;

    friend class nConsumeEvent;
    friend class nClientChannelList;
    friend class nPushTask;
    friend class nConsumeEventConverter;
    friend class nRegisteredEventManager;

};

}
}
}
}
