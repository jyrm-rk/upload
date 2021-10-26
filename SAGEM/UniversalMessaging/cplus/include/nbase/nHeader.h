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
#include "fExternalable.h"
#include "fEventDictionary.h"
#include <string.h>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

using namespace com::pcbsys::foundation::fbase;

class nHeaderIterator;

class nHeader :
    public fExternalable, public Countable {
  public:
    nHeader(void);
    virtual ~nHeader(void);

    virtual void writeExternal(fEventOutputStream *pOstream);
    virtual void readExternal(fEventInputStream *pIstream);

    unsigned char* getPubHost();
    int getPubHostLength();
    unsigned char* getPubName();
    int getPubNameLength();
    longlong getTimestamp();
    unsigned char getDeliveryMode();
    void setDeliveryMode(unsigned char myDeliveryMode);
    unsigned char getMessageType();
    void setMessageType(unsigned char type);
    unsigned char getPriority();
    void setPriority(unsigned char priority);
    unsigned char getReplyType();
    void setReplyType(unsigned char replyType);
    bool isAllowedMerge();
    void setAllowMerge(bool merge);
    bool isSubNameArray();
    unsigned char** getSubNames();
    void setSubNames(std::string* mySubNames, int namesLength);
    void setRegistered(bool flag);
    bool isRegistered();
    void setDelta(bool delta);
    bool isDelta();
    longlong getOriginalTransactionEID();
    void setOriginalTransactionEID(longlong originalTransactionEID);

    /**
    * Get an iterator of all the header values. Always returns the current values of the header. You have control over the life cycle of the iterator object
    * Returns an iterator
    * @return
    */

    DLL nHeaderIterator* getIterator();

    longlong m_timestamp;
    longlong m_expiration;
    unsigned char* m_pCorrelationId;
    unsigned int m_correlationIdLength;
    unsigned char* m_pMessageId;
    unsigned int m_messageIdLength;
    unsigned char* m_pType;
    unsigned int m_typeLength;
    unsigned char* m_pDestination;
    unsigned int m_destinationLength;
    unsigned char* m_pApplicationId;
    unsigned int m_applicationIdLength;
    unsigned char* m_pUserId;
    unsigned int m_userIdLength;
    unsigned char* m_pReplyToName;
    unsigned int m_replyToNameLength;
    unsigned char* m_pPubName;
    unsigned int m_pubNameLength;
    unsigned char* m_pPubHost;
    unsigned int m_pubHostLength;
    bool m_bRedelivered;
    unsigned char* m_pSubName;
    unsigned int m_subNameLength;
    unsigned char* m_pSubHost;
    unsigned int m_subHostLength;
    unsigned char* m_pJoinChannel;
    unsigned int m_joinChannelLength;
    unsigned char* m_pJoinBaseRealm;
    unsigned int m_joinBaseRealmLength;
    unsigned char* m_pJoinPath;
    unsigned int m_joinPathLength;
    unsigned char* m_pDeadEventChannel;
    unsigned int m_deadEventChannelLength;
    longlong m_joinEID;
    longlong m_deadEID;
    int m_subId;
    int m_redeliveredCount;
    
    short ToShort(unsigned char* data);
    unsigned char* ToByte (short data);

  protected:
    unsigned char m_replyType;
    unsigned char m_deliveryMode;
    unsigned char m_priority;
    unsigned char m_messageType;


  private:
    bool m_bAllowMerge;
    bool m_isSubNameArray;
    bool m_bRegistered;
    bool m_bDelta;
    bool m_bOriginalTransactionEID;
};

}
}
}
}
