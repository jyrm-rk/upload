/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NSECURITYGROUPMANAGER_H
#define NSECURITYGROUPMANAGER_H



#include "fBase.h"
#include "Observable.h"
#include "Observer.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclGroup;
class fSubject;
}
}
namespace nirvana {
namespace client {
class nSubject;
}
namespace nAdmin {
class nAdminSession;
namespace events {
class nGroupEvent;
}
}
namespace nAdminAPI {
class nRealmNode;
class nSecurityGroup;
class nSecurityGroupStore;

using namespace com::pcbsys::nirvana::client;
using namespace com::pcbsys::nirvana::nAdmin::events;
using namespace com::pcbsys::nirvana::nAdmin;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::security;

DLL class nSecurityGroupManager : public Observable, public Observer {

  private:
    nAdminSession* mySession;
    nSecurityGroupStore* store;
    nRealmNode* myNode;
    std::list<nSecurityGroup*>* convertToAdminAPI(std::list<fAclGroup*>* groups);

  public:
    /**
     * Create a new nSecurityGroupManager for the nRealmNode provided
     *
     * @param node the realmNode which this securityGroupManager will control.
     */
    nSecurityGroupManager(nRealmNode* node);
    ~nSecurityGroupManager();

    /**
     * Register a new group with the Nirvana Realm.
     * @param name - the name of the group to register
     * @throws nBaseClientException if the group could not be registered on the realm.
     */
    virtual void registerSecurityGroup(std::string name);

    /**
     * Remove a member of a group.
     * @param group - The name of the group to remove the member from.
     * @param Name - The subject to be removed from the group.
     * @throws nBaseClientException if the member could not be removed form the group
     */
    virtual void removeSecurityGroupMember(std::string group, std::string name);

    /**
     *  Remove a member from a security group.
     * @param group The group which the member should be removed from
     * @param sub The subject to be removed from the group
     * @throws nBaseClientException if the subject could not be removed from the build
     */
    virtual void removeSecurityGroupMember(nSecurityGroup* group, nSubject* sub);

    /**
     * Remove a collection of group members from a given group.
     * @param group The group these members should be removed from
     * @param subsToRemove The members to be removed from the group
     * @throws nBaseClientException if the members could not be removed from the specified group
     */
    virtual void removeSecurityGroupMembers(nSecurityGroup* group, std::list<nSubject*>* subsToRemove);

    /**
     * Remove a collection of group members from a given group.
     * @param group The group these members should be removed from
     * @param subsToRemove The members to be removed from the group
	 * @param numSubsToRemove length of subsToRemove array.
     * @throws nBaseClientException if the members could not be removed from the specified group
     */
    virtual void removeSecurityGroupMembers(nSecurityGroup* group, std::string* subsToRemove, int numSubsToRemove);

    /**
     * Remove a set of members from a set of security groups
     * @param groups The groups the specified members should eb removed from
	 * @param numGroups length of groups array.
     * @param subsToRemove The members to be removed from the specified groups
	 * @param numSubsToRemove length of subsToRemove array.
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void removeSecurityGroupMembers(nSecurityGroup** groups, int numGroups, std::string* subsToRemove, int numSubsToRemove);

    /**
     * Deregister a security group on the realm. This will also remove the group from all ACLs it is currently part of.
     * @param name the name a the group to be deregistered
     * @throws nBaseClientException if the group cannot be deregistered from the realm
     */
    virtual void deregisterSecurityGroup(std::string name);

    /**
     * Deregister a security group on the realm. This will also remove the group from all ACLs it is currently part of.
     * @param name the name a the group to be deregistered
     * @throws nBaseClientException if the group cannot be deregistered from the realm
     */
    virtual void deregisterSecurityGroup(nSecurityGroup* grp);

    /**
     * Register a collection of nSubject members as members of a security group
     * @param group The group to add the specified members to
     * @param members The collection of (nSubject) members to add to the group
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void registerGroupMembers(nSecurityGroup* group, std::list<nSubject*>* members);

    /**
     * Register a collection of fSubject members as members of a security group
     * @param name The name of the group to add the specified members to
     * @param members The collection of (nSubject) members to add to the group
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void registerGroupMembers(std::string name, std::list<fSubject*>* members);

    /**
     * Register an nSubject member as a members of a security group
     * @param group The group to add the specified member to
     * @param member The (nSubject) member to add to the group
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void registerGroupMember(nSecurityGroup* group, nSubject* member);

    /**
     * Register an nSubject member as a members of a security group
     * @param group The name of the group to add the specified member to
     * @param member The (nSubject) member to add to the group
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void registerGroupMember(std::string group, nSubject* member);

    /**
     * Register a collection of (nSubject) members as a members in each of a collection of security groups
     * @param groups The groups to add the specified mebers to
     * @param subs The members to add to each of the specified groups
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void registerGroupMembers(std::list<nSecurityGroup*>* groups, std::list<nSubject*>* subs);

    /**
     * Returns a collection containing all groups currently registered on the realm.
     * @return a collection of nSecurityGroups, containing all groups currently registered on the realm.
     */
    virtual std::list<nSecurityGroup*>* getGroups();

    virtual nSecurityGroupStore* getStore();

    virtual void process(nGroupEvent* grpEvt);

    /**
     * Used internally to monitor changes to the security groups.
     *
     * @param observable
     * @param pArg
     */
    virtual void update(Observable *pObs, void *pArg);

    /**
     * Register a new security group on the realm
     * @param grp the nSecurityGroup to be registered with the realm
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void registerSecurityGroup(nSecurityGroup* grp);

    /**
     * Register a collection of security groups on the realm
     * @param groups the nSecurityGroups to be registered with the realm
     * @throws nBaseClientException if the operation cannot be performed
     */
    virtual void registerSecurityGroups(std::list<nSecurityGroup*>* groups);

};
}
}
}
}

#endif
