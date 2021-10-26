/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NSECURITYGROUP_H
#define NSECURITYGROUP_H



#include "nSubject.h"
#include "fBase.h"
#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fACLGroup;
class fSubject;
}
}
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::security;
using namespace com::pcbsys::nirvana::client;

/**
 * This class represents a "Security Group" that contains entries for nSubject objects, and other nSecurityGroup objects.
 *
 * The class can be used in conjunction with the nACLEntry (and any subclass of this object) in order to add
 * nSecurityGroup objects into nACL objects for Nirvana Realm ACLs, Channel / Queue ACLs or Interface Via Lists.
 */
class nSecurityGroup : public nSubject {

  public:
    /**
     * Construct the nSecurityGroup with it's name
     * 
     * @param name the name of the group
    */
    DLL nSecurityGroup(std::string name);

    virtual ~nSecurityGroup();
    /**
    * Construct the nSecurityGroup with a name and members
    *
    * @param name the name of the security group
    * @param members the initial members of the group
    * @param numMembers the number of members
    */
    DLL nSecurityGroup(std::string name, nSubject** members, int numMembers);

    /**
     * Constructor for nSecurity Group taking an fACLGroup representation of a group
     *
     * @param group the fACLGroup to generate this SecurityGroup from.
     */
    DLL nSecurityGroup(fAclGroup* group);

    /**
    * Add a member to the group
    *
    * @param member the member to add
    */
    DLL virtual void add(nSubject* member);

    /**
    * Checks whether this nSecurityGroup contains a specific nSubject
    * @param member the member to check within this group and sub groups
    * @return true if the member exists, else false
    */
    DLL virtual bool contains(nSubject* member);

    /**
    * Checks whether this nSecurityGroup contains a specific member (could be another nSecurityGroup or an nSubject
    * @param member the member to check within this group and sub groups
    * @return true if the member exists, else false
    */
    DLL virtual bool contains(std::string member);

    /**
    * Locate the nSubject within this nSecurityGroup or it's member nSecurityGroup objects
    * @param member the member being searched for
    * @return the nSubject or nSecurityGroup that represents the nSubject passed in
    */
    DLL virtual nSubject* lookup(nSubject* member);

    /**
    * Gets the subject for the group
    * @return the subject
    */
    DLL virtual fAclGroup* getSubject();

    /**
    * Gets the members for the group
    * @return list of the members subjects
    */
    DLL virtual std::list<nSubject*>* getMembers();

  private:
    std::list<nSubject*>* convertToAdminAPI(std::list<fSubject*>* members);
};
}
}
}
}

#endif
