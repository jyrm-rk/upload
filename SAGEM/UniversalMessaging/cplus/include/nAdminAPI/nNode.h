/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"
#include "fSortedList.h"
#include "fBase.h"
#include "nSecurityGroup.h"
#include "Poco/SynchronizedObject.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclEntry;
class fAclList;
}
}
namespace nirvana {
namespace nAdminAPI {

class nACL;
class nACLEntry;

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::collections;
using namespace com::pcbsys::foundation::security;
/**
 * All classes that exist in the Nirvana Realm NameSpace extend this object. This object
 * contains generic functions such as getName and getAbsolutePath etc.
 */
class nNode :
    public Observable {
  public:
    nNode(void);
    virtual ~nNode(void);


    /**
     * Returns true if this nNode can be removed
     *
     * @return bool true if the nNode can be removed
     */
    virtual bool IsRemovable();


    /**
     * Check if this nNode is the same as the nNode passed in
     *
     * @param *PItem the nNode to compare this nNode to
     * @return bool true if the nNode matches this nNode
     */
    virtual bool Equals(nNode *pItem);

    /**
     * Check if the string passed in matches the name of this nNode
     *
     * @param item the string to compare the name of this node to
     * @return bool true if the string matches the name of this nNode
     */
    virtual bool Equals(const std::string& item);

    /**
     * Returns the name of this nNode
     *
     * @return string containing the name of this nNode
     */
    const std::string& getInternalName();

    /**
     * Returns the name of the node
     *
     * @return string name of the node
     */
    DLL const std::string& getName();

    /**
     * Returns this nodes parent node. If this node is the root it will return null
     *
     * @return nNode of the parent
     */
    virtual nNode* getParent();

    /**
     * This method returns the relative path from this node to the nNode passed.
     * Note. It is assumed that the nNode passed is a parent node, this method will not locate nodes in
     * different parts of the tree.
     *
     * @param nNode *ptop Node to get relative path to
     * @return String path relative to the node passed in
     */
    virtual std::string getRelativePath(nNode *pTop);

    /**
     * Converts from a long to a bitArray used to specify ACL properties
     *
     * @param priv a longlong representation of the ACL properties to set
     * @return BitArray the BitArray generated from the longlong
     */
    virtual BitArray* convertLong(longlong priv);

    /**
     * Adds a specific acl entry to the leaf node acl
     *
     * @param subject the subject the ACL is assigned to
     * @param *pBs the bitArray representing the ACL settings to be used
     * @exception nInsufficientPrivilegesException If the user is not permissioned to perform this operation
     * @exception nNodeException if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    virtual nACLEntry* createACLEntry(const std::string& subject, BitArray *pBs);

	/**
	* Adds a specific security group to the leaf node acl
	*
	* @param *grp the security group the ACL is assigned to
	* @param *pBs the bitArray representing the ACL settings to be used
	* @exception nInsufficientPrivilegesException If the user is not permissioned to perform this operation
	* @exception nNodeException if the ACLs being set are invalid
	* @exception nBaseAdminException if unable to perform the operation, check the message for further information
	*/
	virtual nACLEntry* createACLEntry(nSecurityGroup* grp, BitArray *pBs);
    /**
     * This function walks the tree to the root to generate a fully qualified name for this node
     *
     * @return String full path and name
     */
    virtual const std::string& getAbsolutePath();

    virtual bool Equals(longlong aLong);
    virtual bool lessThan(nNode *pItem);
    virtual bool lessThan(const std::string& item);
    virtual bool lessThan(longlong aLong);

  protected:
    nNode(const std::string& name, nNode *pParent);

    virtual nACL* convertToAdminAPI(fAclList* vec);
    virtual nACLEntry* convertToAdminAPI(fAclEntry *pAcl);
    virtual int compare(nNode *pItem);
    virtual int compare(const std::string& item);
    virtual void setHasChanged(bool changed);
    virtual void convertTofAclList(nACL *pAcls, fAclList* list);
    virtual fAclEntry* convertTofAclList(nACLEntry *pEntry);
    virtual longlong convertBitMap(BitArray& bs);
    virtual nNode* getRootNode();
    virtual void hasUpdated();

    std::string m_name;
    nNode *m_pParent;
    std::string m_absolutePath;
    Poco::SynchronizedObject m_waitObject;

    friend class nPkgAdminListener;
    friend class nLeafNode;
    friend class nContainer;
};

}
}
}
}
