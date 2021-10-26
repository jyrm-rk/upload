/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEvent.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nHeader;

namespace events {

class nBasePublishEvent :
    public nEvent {
  public:
    nBasePublishEvent(void);
    nBasePublishEvent(int id, longlong uniqueId, unsigned char *tag, int tagLength,
                      unsigned char *data, int dataLength, unsigned char type,
                      fEventDictionary *pDictionary, longlong ttl, bool persist,
                      unsigned char *signature, int signatureLength);
    virtual ~nBasePublishEvent(void);

    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    longlong getChannelAttributesId();
    bool isTimeOuts();
    fEventDictionary* getDictionary();
    unsigned char* getData ();
    int getDataLength ();
    longlong getTTL();
    bool isPersistent();
    bool isTransient();
    unsigned char* getTag();
    int getTagLength();
    unsigned char* getSignature();
    int getSignatureLength();
    bool isEndOfChannel();
    nHeader* getHeader();
    void setTransient(bool aTransient);
    void setEndOfChannel(bool endOfChannel);
    void setHeader(nHeader *pHeader);
    virtual unsigned int getPriority();

    static const unsigned char sIsDom;
    static const unsigned char sIsTimeOuts;
    static const unsigned char sHasSignature;

    void setIsDDD(bool flag);


  protected:
    longlong m_channelAttribId;
    unsigned char m_type;
    unsigned char *m_pData;
    unsigned int m_dataLength;
    longlong m_TTL;
    bool m_bIsPersist;
    unsigned char* m_pTag;
    unsigned int m_tagLength;
    unsigned char* m_pSignature;
    unsigned int m_signatureLength;
    bool m_bIsEndOfChannel;
    nHeader* m_pHeader;
    bool m_bOldFormat;
    bool m_bIsTransient;
    bool myIsDDD;
};

}
}
}
}
}
