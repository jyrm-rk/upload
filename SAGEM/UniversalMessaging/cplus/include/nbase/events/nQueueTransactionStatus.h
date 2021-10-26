/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nCachedChannelAttributes.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

class nQueueTransactionStatus :
    public nCachedChannelAttributes {
  public:
    nQueueTransactionStatus();
    nQueueTransactionStatus(longlong readerUniqueId, longlong uniqueId, longlong eid, bool committed);
    virtual ~nQueueTransactionStatus(void);

    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual void setSync(bool flag);
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual longlong getReaderUniqueId();

    longlong m_eid;
    bool m_bIsCommitted;

    /// <summary>
    /// Represents unknown reader. Using this reader identifier will request that the Universal Messaging server tries to identify the reader
    /// which performs this queue transaction request automatically. This will typically be less performant and must be used only
    /// in case the reader cannot be identified for some reason.
    /// </summary>
    static const longlong UNKNOWN_READER_UNIQUE_ID = 0;

  private:
    /// <summary>
    /// An identifier that uniquely identifies the reader which performs this queue operation within the session.
    /// This will be paired with the connection id to uniquely identify the reader within the Universal Messaging server.
    /// </summary>
    /// <returns>An identifier that uniquely identifies the reader which performs this queue operation within the session</returns>
    longlong m_readerUniqueId;
};

}
}
}
}
}
