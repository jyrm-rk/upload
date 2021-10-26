/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nPublished.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

class nJoinInfoCache;

class nPublishedJoin :
    public nPublished {
  public:
    nPublishedJoin(void);
    virtual ~nPublishedJoin(void);

    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();

    static void getJoinFromCache(unsigned char *join, int joinLength, std::string& strJoin);

    static nJoinInfoCache *spMyJoinCache;

  private:
    int m_hopCount;
    unsigned char *m_pJoinInfo;
    unsigned int m_joinInfoLength;
    std::string m_strJoinInfo;
    bool m_bIsRoutable;
    longlong m_remoteId;
};

}
}
}
}
}
