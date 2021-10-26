/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nACLEntry.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class BitArray;
}
}
namespace nirvana {
namespace nAdminAPI {

using namespace foundation::fbase;
/**
 * This contains the user@host parameters which are bound to an Interface. When a client connects the configured interfaces
 * scan the Via list looking for a matching user@*, *@host and user@host. If a match is found and the client is not connecting
 * via that interface the connection is disallowed. A client can appear in more than one interface.
 *
 */
class nInterfaceViaEntry :
    public nACLEntry {
  public:
    /**
     * Creates a new nInterfaceViaEntry
     *
     * @param subject the subject of the entry
     * @param *pBitset a BitArray containing the bitset describing the rights of this subject.
     */
    nInterfaceViaEntry(const std::string& subject);
    nInterfaceViaEntry(const std::string& subject, BitArray *pBitset);
    nInterfaceViaEntry(const std::string& name, const std::string& host);
    virtual ~nInterfaceViaEntry(void);
    /**
     * Returns the type of this object, for internal use only
     * @return the type of this object
     */
    virtual int getType();

  protected:
    nInterfaceViaEntry(const std::string& name, const std::string& host, BitArray *pBitset);

  private:
    void setConnect(bool val);

    static const int INTERFACE_CONNECT = 5;
};

}
}
}
}
