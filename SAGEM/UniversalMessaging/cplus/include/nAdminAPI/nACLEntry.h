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
#include "nSubject.h"
#include "nSecurityGroup.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::nirvana::client;
/**
 * Contains the mapping between a subject User\@Host and the privileges they can perform
 * on a secured object such as a Realm, Channel or Queue.
 *
 * On construction of these objects the name string can be set to "*" meaning All users and
 * the host can also be set to "*". For example, all users from a host called test.com can be configured
 * such as *\@test.com or a more insecure method for allowing all administrators access would be
 * administrator\@* (Not recommended).
 */
class nACLEntry : public CountableObject {
  public:
    nACLEntry(void);

    /**
     * Creates a new nACLEntry with the subject being name\@host. There are no
     * default permissions set so this subject can perform NO actions on the secured objects
     *
     * @param name Username/Token for the subject
     * @param host the host they can connect from
     */
    nACLEntry(const std::string& name, const std::string& host);

    /**
     * Creates a new nACLEntry with the subject being name\@host. There are no
     * default permissions set so this subject can perform NO actions on the secured objects
     *
     * @param subject Username/Token for the subject
     * @param *pBitset the bitset denoting the permissions for this acl
     */
    DLL nACLEntry(const std::string& subject, BitArray *pBitset = NULL);

    DLL nACLEntry(nSecurityGroup* grp);

    nACLEntry(nSecurityGroup* grp, BitArray* bs);

    virtual ~nACLEntry(void);

    /**
     * Creates a new nACLEntry with the subject being name\@host. There are no
     * default permissions set so this subject can perform NO actions on the secured objects
     *
     * @return the bitset denoting the permissions for this ACL
     */
	DLL BitArray* getBitSet();
    /**
     * Replace the bit array representing the ACL with *pArray
     * @param *pArray bit array representing an ACL
     */
    void copyBitArray(BitArray *pArray);

    /**
    * This method returns the completed subject User\@Host
    *
    * @return String representation of the subject
    */
    DLL std::string getSubject();

    /**
     * Changes the current setting for this user to allow/disallow ACL listing
     *
     * WARNING: Should be used in conjunction with ModifyACL
     *
     * @param val boolean specifying the permission status
     */
    virtual void setList(bool val);

    /**
      * Changes the current setting for this subject to allow/disallow modifying ACL.
      *
      * WARNING: Should not be given to normal subjects but only to subjects which need
      * to administer the Secure Object.
      *
      * @param val boolean specifying the permission status
      */
    virtual void setModify(bool val);

    /**
      * Sets the subject to have full privileges for this secure object allowing the subject complete
      * control over the secure object
      *
      * WARNING: Use with great caution. Should only set what is required rather than this
      * entry. By default the realm server will automatically set this for the default administrator
      *
      * @param val true for full, false otherwise
      */
    virtual void setFullPrivileges(bool val);

    /**
      * Can this subject list the contents of an ACL
      *
      * @return a boolean indicating the current permission status for this user
      */
    virtual bool canList();

    /**
      * Can this subject modify acl entries in a secure object
      *
      * @return a boolean indicating the current permission status for this user
      */
    virtual bool canModify();

    /**
      * Does this subject have full privileges for the secure object. This privilege enables the
      * subject to perform ANY action against this secure object if set to true.
      *
      * @return a boolean indicating the current permission status for this user
      */
    virtual bool hasFullPrivileges();

    /**
      * Returns the host's name as a string
      *
      * @return a string containing the hostname
      */
    virtual const std::string& getHost();

    virtual bool isGroup();

    virtual bool Equals(nACLEntry *pItem);
    virtual bool Equals(const std::string item);
    virtual bool Equals(longlong aLong);

    /**
     * Returns the name of the ACLEntry
     *
     * @return String name
     */
    virtual const std::string& getName ();

    /**
     * Used to compares this Object with another to determine sorting position
     *
     * @param item Object to compare
     * @return True if this object is less then the passed in object
     */
    virtual bool lessThan(nACLEntry *pItem);
    virtual bool lessThan(const std::string& item);

    /**
     * Required as part of the SortedObject interface. For internal use only
     */
    virtual bool lessThan(longlong aLong);
    virtual void setPermissions(longlong permValue);

  protected:
    nACLEntry(const std::string& name, const std::string& host, BitArray *pBitset);
    virtual int checkMalformedSubject(const std::string& subject);
    virtual void checkInvalidUserAndHost();
    virtual void set(int bit, bool value);

    virtual longlong getPermissions();
    virtual longlong convertBitMap();

    std::string m_name;
    std::string m_host;
    BitArray *m_pBitSet;
    nSubject* m_subject;
    bool m_bHasChanged;

  private:
    int compare(const std::string& item);
    int compare(nACLEntry *pItem);

    static const int ACL_ADD = 0;
    static const int ACL_REMOVE = 1;
    static const int ACL_LIST = 2;
    static const int ACL_ADMIN = 3;

    friend class nACL;
    friend class nChannelACLEntry;
    friend class nInterfaceViaEntry;
    friend class nRealmAdmin;
};

}
}
}
}
