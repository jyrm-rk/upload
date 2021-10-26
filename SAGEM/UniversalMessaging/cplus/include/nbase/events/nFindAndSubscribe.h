/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSynchronous.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventOutputStream;
class fEventInputStream;
}
}
namespace nirvana {
namespace client {
class nBaseClientException;
}
namespace nbase {

class nBaseSubscriptionAttributes;
class nBaseChannelAttributes;

namespace events {

using namespace foundation::io;
using namespace client;

class nFindAndSubscribe :
    public nSynchronous {
  public:
    nFindAndSubscribe(void);
    nFindAndSubscribe(nBaseSubscriptionAttributes **ppChannelNames, int nChannelName);
    virtual ~nFindAndSubscribe(void);

    virtual nBaseSubscriptionAttributes** getSubscriptionAttributes(int& nSubAttr);
    virtual nBaseChannelAttributes** getAttributes(int& nAttribute);
    virtual void setAttributes(fExternalable **ppAttrib, unsigned char *pAttribTypes, int nAttrib);
    virtual nBaseClientException** getExceptions(int& nException);
    virtual void setSubscriptionAttributes(nBaseSubscriptionAttributes **ppNames, int nName);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performWrite(fEventOutputStream *pOos);
    virtual void performRead(fEventInputStream *pOis);

  private:
    static const unsigned char CHANNEL = 0;
    static const unsigned char SECURITY = 1;
    static const unsigned char EXCEPTION = 2;

    nBaseSubscriptionAttributes **m_ppSubAttr;
    int m_nSubAttr;
    fExternalable **m_ppAttributes;
    unsigned char *m_pAttributeTypes;
    int m_nAttribute;
};

}
}
}
}
}
