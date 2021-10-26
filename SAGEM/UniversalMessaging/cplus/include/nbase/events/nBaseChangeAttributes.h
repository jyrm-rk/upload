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
class nBaseChannelAttributes;

namespace events {

class nBaseChangeAttributes : public nCachedChannelAttributes {
  public:
	  nBaseChangeAttributes(void);
	  nBaseChangeAttributes(nBaseChannelAttributes *pAttrib, nBaseChannelAttributes *pNewAttrib, int type);
	  nBaseChangeAttributes(nBaseChannelAttributes *pAttrib, nBaseChannelAttributes *pNewAttrib);
	  virtual ~nBaseChangeAttributes(void);

    virtual int getType();
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();

    virtual nBaseChannelAttributes* getNewAttributes();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    static const int STATUSCHAN = 0;
    static const int TXCHAN = 1;
    static const int USERCHAN = 2;

  private:
    int m_chanType;
    nBaseChannelAttributes *m_pNewAttrib;
};

}
}
}
}
}
