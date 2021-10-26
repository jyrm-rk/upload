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

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nNamedObject;
}
namespace nbase {
class nBaseChannelAttributes;

namespace events {

using namespace com::pcbsys::nirvana::client;

class nManageNamedSub :
    public nCachedChannelAttributes {
  public:
    nManageNamedSub(void);
    nManageNamedSub(nBaseChannelAttributes *pAttrib, unsigned char cmd, const std::string& name, longlong sessionId, bool persistent,
                    bool clusterWide = false, longlong startEID = -1);
    virtual ~nManageNamedSub(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);
    unsigned char getCommand();
    nNamedObject* getObject();
    void setNameId(longlong id);
    nNamedObject** getList(int& numObject);

    static const int sAdd = 0;
    static const int sDel = 1;
    static const int sGet = 2;
    static const int sUnbind = 3;
    static const unsigned char sIsClusterWide = 0x1;
    static const unsigned char sIsPriorityEnabled = 0x2;
	static const unsigned char sIsShared = 0x4;

  protected:
    std::string m_name;
    unsigned char m_command;
    longlong m_sessionId;
    longlong m_uniqueId;
    longlong m_startEID;
    bool m_bIsPersistent;
    bool m_bIsClusterWide;
    std::list<nNamedObject*> m_list;
    bool m_bIsPriorityEnabled;
	bool m_bIsShared;
};

}
}
}
}
}
