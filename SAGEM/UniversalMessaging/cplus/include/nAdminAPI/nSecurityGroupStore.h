/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NSECURITYGROUPSTORE_H
#define NSECURITYGROUPSTORE_H


#include "fBase.h"
#include "Observer.h"
#include "Observable.h"
#include "fSortedList.h"
#include "Poco/SynchronizedObject.h"
#include <list>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclGroup;
class fSubject;
class fDeregisterGroupUpdate;
}
}
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::security;
using namespace com::pcbsys::foundation::collections;

class nSecurityGroupStore : public Observer, public Observable {

  private:
    fSortedList<std::string, fAclGroup*>* groups;

  public:
    nSecurityGroupStore(std::list<fAclGroup*>* initialGroups);

    /**
     * Add a group to this store
     *
     * @param group the fACLGroup to be added to the store.
     */
    virtual void addGroup(fAclGroup* group);

    /**
     * Add a collection of members to all gorups in the provided list.
     *
     * @param groupNames an array of groupNames for these Subjects to be added to, as Strings.
	 * @param numGroupNames length of the groupNames array.
     * @param members A collection of Fsubjects to be added to all of the groups.
     */
    virtual void addGroupMembers(std::string* groupNames, int numGroupNames, std::list<fSubject*>* members);

    /**
     * Add groups to this store.
     *
     * @param groups a collection of fAclGroups to be added to the store.
     */
    virtual void addGroups(std::list<fAclGroup*>* groups);

    /**
     * remove a group from the store
     *
     * @param group the fAclGroup to be removed
     */
    virtual void deleteGroup(fAclGroup* group);

    /**
     * Remove a set of groups
     *
     * @param groups the names of the groups to be removed as an array of strings.
	 * @param numGroups length of groups array.
     */
    virtual void deleteGroups(std::string* groups, int numGroups);

    /**
     * Delete a set of members from each of a set of groups
     *
     * @param groups an array of the names of the groups the members should be removed from (as Strings).
	 * @param numGroups length of groups array.
     * @param members the string representation of the members to be removed rom each group.
	 * @param numMembers length of members array.
     */
    virtual void deleteGroupMembers(std::string* groups, int numGroups, std::string* members, int numMembers);

    /**
     * Return the fACLGroup which corresponds with a particular String (if present)
     *
     * @param groupName the name of the group to be retrieved.
     * @return the fACLGroup corresponding with this name
     */
    virtual fAclGroup* getGroup(std::string groupName);

    /**
     * Returns a collection of fACLGroups which are in this store
     *
     * @return the fACLGroups in this store.
     */
    virtual std::list<fAclGroup*>* getGroups();

    /**
     * Used internall to monitor changes to groups
     *
     * @param observable
     * @param pArg
     */
    virtual void update(Observable *pObs, void *pArg);
};
}
}
}
}

#endif
