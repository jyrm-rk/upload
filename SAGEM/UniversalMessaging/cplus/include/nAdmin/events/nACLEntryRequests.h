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

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclEntry;
}
}
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace nbase::events;
using namespace foundation::security;

class nACLEntryRequests :
    public nSynchronous {
  public:
    nACLEntryRequests(void);
    nACLEntryRequests(unsigned char command, fAclEntry **ppEntries, int numEntry, std::string *pNodes, int numNode, bool bChannels, bool bQueues, bool bRealm);
    virtual ~nACLEntryRequests(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    bool setRealm();
    fAclEntry** getEntries(int& numEntry);
    std::string* getNodes(int& numNode);
    unsigned char getCommand();
    bool setChannels();
    bool setQueues();

    static const unsigned char sAdd = 0;
    static const unsigned char sMod = 1;
    static const unsigned char sDel = 2;

  private:
    static const unsigned char sChannels = 1;
    static const unsigned char sQueues = 2;
    static const unsigned char sP2P = 4;
    static const unsigned char sRealm = 8;

    unsigned char m_command;
    unsigned char m_typeFlag;
    fAclEntry **m_ppEntries;
    int m_nEntry;
    std::string *m_pNodes;
    int m_nNode;
};

}
}
}
}
}
