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
#include "fBase.h"
#include "nSecurityGroup.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

/**
 * Allows the ability to programmatically allow or deny access to a service
 *
 * @see nACLEntry
 */
class nServiceACLEntry :
    public nACLEntry {
  public:
    nServiceACLEntry(void);

    /**
     * Creates a new nServiceACLEntry for the name/@host supplied.
     *
     * By default this subject has NO privileges and they must be set.
     *
     * @param name Name for the subject
     * @param host Host name for the subject
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     *
     * @see nACLEntry
     */
    DLL nServiceACLEntry(const std::string& name, const std::string& host);

    /**
     * Creates a new nServiceACLEntry for the name/@host supplied.
     *
     * By default this subject has NO privileges and they must be set.
     *
     * @param subject Name for the subject
     * @param *pBitset a BitArray indicating the privileges associated with this ACL
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     *
     * @see nACLEntry
     */
    nServiceACLEntry(const std::string& subject, BitArray *pBitset);

	/**
	* Creates a new nServiceACLEntry for the security group supplied.
	*
	* By default this subject has NO privileges and they must be set.
	*
	* @param *grp The security group to create the ACL for
	* @param *pBitset a BitArray indicating the privileges associated with this ACL
	* @exception nAdminIllegalArgumentException if an invalid or null argument is passed
	*
	* @see nACLEntry
	*/
	nServiceACLEntry(nSecurityGroup* grp, BitArray *pBitset);

    virtual ~nServiceACLEntry(void);

    /**
     * Allow or deny the subject to connect to the service
     *
     * @param val boolean value
     */
    virtual void setConnect(bool val);

    /**
     * Can the subject connect to the service
     *
     * @return current state
     */
    virtual bool canConnect();

    nServiceACLEntry(const std::string& subject);

  protected:
    nServiceACLEntry(const std::string& name, const std::string& host, BitArray *pBitset);

private:
	static const int CHANNEL_ADMIN = 4; // Not Used
	static const int CHANNEL_JOIN = 8; // Not Used
	static const int CHANNEL_LAST_EID = 9;
  public:
    static const int CHANNEL_PUB = 5;
    static const int CHANNEL_SUB = 6;
    static const int CHANNEL_PURGE = 7;
    static const int CHANNEL_POP = 10;
};

}
}
}
}
