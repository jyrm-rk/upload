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
#include "nSecurityGroup.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

/**
 * Extends the nACLEntry class to expose the Realm specific permissions
 *
 * @see nACLEntry
 */
class nRealmACLEntry :
    public nACLEntry {
  public:
    nRealmACLEntry(void);

    /**
     * Creates a new nRealmACLEntry with the supplied name\@host. This class is used to manage
     * subjects and their privileges they have on a realm.
     *
     * @param name The name of the subject
     * @param *pBitset the bitset representing the privileges of this subject
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    nRealmACLEntry(const std::string& subject, BitArray *pBitset);

    /**
     * Creates a new nRealmACLEntry with the supplied name\@host. This class is used to manage
     * subjects and their privileges they have on a realm.
     *
     * @param name The name of the subject
     * @param host The host name for the subject
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    DLL nRealmACLEntry(const std::string& name, const std::string& host);

	/**
	* Creates a new nRealmACLEntry for the security group. This class is used to manage
	* subjects and their privileges they have on a realm.
	*
	* @param *grp The security group
	* @param *pBitset the bitset representing the privileges of this subject
	* @exception nAdminIllegalArgumentException if an invalid or null argument is passed
	*/
	DLL nRealmACLEntry(nSecurityGroup* grp, BitArray *pBitset);

    /**
     * Creates a new nRealmACLEntry with the supplied name\@host. This class is used to manage
     * subjects and their privileges they have on a realm.
     *
     * @param subject of the form user@host
     * @exception nAdminIllegalArgumentException if an invalid or null argument is passed
     */
    DLL nRealmACLEntry(const std::string& subject);
    virtual ~nRealmACLEntry(void);
    /**
     * Returns the type of the connection details this object represents.  In this case the object represents channel connection details.
     * @return the type of connection details represented
     */
    virtual int getType();

    /**
     * Allows/Disallows this subject the ability to connect and use the realm
     *
     * @param val Boolean value to set
     */
    virtual void setAccessTheRealm(bool val);

    /**
     * Allows/Disallows this subject from accessing the realms Admin API functions
     *
     * @param val Boolean value to set
     */
    virtual void setUseAdminAPI(bool val);

    /**
     * Allows/Disallows setting realm configuration values
     *
     * @param val Boolean value to set
     */
    virtual void setConfigureRealm(bool val);

    /**
     * Allow/Disallows this subject from making/deleting or performing maintenance on any channel on the realm
     *
     * @param val Boolean value to set
     */
    virtual void setManageChannels(bool val);

    /**
     * Allows/Disallows this subject from managing the joins between channels within the namespace
     *
     * @param val Boolean value to set
     */
    virtual void setManageJoins(bool val);

    /**
     * Allows/Disallows this client from adding/removing remote realms into the namespace
     *
     * @param val Boolean value to set
     */
    virtual void setManageRealm(bool val);

    /**
     * Allow/Disallows the subject from overriding the maximum connection count
     *
     * @param val Boolean value to set
     */
    virtual void setOverrideConnectionCount(bool val);

    /**
     * Can this Subject connect and use this realm. If false the subject will be disconnected during
     * the authentication stage.
     *
     * @return The current configuration
     */
    virtual bool canAccessTheRealm();

    /**
     * Can this subject set/get runtime configuration values for the realm
     *
     * @return The current configuration
     */
    virtual bool canConfigureRealm();


    /**
     * Can this subject make/delete or perform maintenance on channels within this realm. This
     * permission is extends only for this realm within the namespace.
     *
     * @return The current configuration
     */
    virtual bool canManageChannels();

    /**
     * Can this subject create/remove/list joins between channels within the namespace
     *
     * @return The current configuration
     */
    virtual bool canManageJoins();

    /**
     * Can this Subject add/remove remote realms into this realms namespace.
     *
     * @return The current configuration
     */
    virtual bool canManageRealm();

    /**
     * Can this subject bypass the Realms maximum connection count. Typically all administrators would
     * have this set so that a realm could be started with the user count set to a low number to allow
     * a managed restart for example. Any user with this set will not check the current user count. This is
     * not a license restriction, rather it is up to the end user to set the user count and these settings
     * accordingly
     *
     * @return The current configuration
     */
    virtual bool canOverrideConnectionCount();

    /**
     * Any subject with this permission set can perform the following functions on a realm
     *
     * Disconnect users from the realm
     * Set ACLs for channels, queues and the realm
     * Retrieve a list of all channels, queues, joins and connected realms
     * Set Client Timeout values
     * Set/Get Realm Configuration values for the realm
     *
     * Some of these functions also depend on other permissions being set as well
     *
     * @return The current configuration
     */
    virtual bool canUseAdminAPI();

    /**
     * Checks if this acl entry allows management of datagroups.
     *
     * @return boolean value true if this acl entry allows management of datagroups, false otherwise.
     */
    virtual bool canManageDataGroups();

    /**
     * Checks if this acl entry allows publishing to the default datagroup.
     *
     * @return boolean value true if this acl entry allows publishing to the default datagroup
     */
    virtual bool canPublishToGlobalDataGroup();

    /**
     * Checks if this acl entry allows taking ownership of datagroups.
     *
     * @return boolean value true if this acl entry can take ownership of datagroups, false otherwise.
     */
    virtual bool canTakeOwnershipOfDataGroup();

    /**
     * Allows or disallows management of datagroups for this acl entry.
     *
     * @param val boolean which when set to true will allow management of datagroups.
     */
    virtual void setManageDataGroups(bool val);

    /**
     * Allows or disallows publishing to the default datagroup for this acl entry.
     *
     * @param val boolean which when set to true will allow publishing to the default datagroup.
     */
    virtual void setPublishToGlobalDataGroup(bool val);

    /**
     * Allows or disallows taking ownership of a datagroup for this acl entry.
     *
     * @param val boolean which when set to true will allow ownership of datagroups.
     */
    virtual void setTakeOwnershipOfDataGroup(bool val);

  public:
    static const int REALM_ADMIN = 4;
    static const int REALM_MANAGE_REALMS = 5;
    static const int REALM_MANAGE_JOINS = 6;
    static const int REALM_MANAGE_CHANNELS = 7;
    static const int REALM_ALLOW_ACCESS = 8;
    static const int REALM_OVERRIDE_CONNECTION_COUNT = 9;
    static const int REALM_CONFIGURATION = 10;
    static const int REALM_MANAGE_P2P_SERVERS = 11;
    static const int REALM_MANAGE_DATA_GROUPS = 12;
    static const int REALM_PUBLISH_GLOBAL_DATA_GROUPS = 13;
    static const int REALM_TAKE_OWNERSHIP_DATA_GROUPS = 14;
};

}
}
}
}
