/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nBaseStorePermission.h"
#include "nChannelAttributes.h"
#include <string>
#include <vector>

using namespace com::pcbsys::nirvana::nbase;

/**
* Class that provides ability for setting specific Channel/Queue security settings.
*/
namespace com {
  namespace pcbsys {
    namespace nirvana {
      namespace client {
        class nStorePermission {
        public:
          /**
          * Creates a new nStorePermission object for the group with the provided name and the given permission mask.
          *
          * @param groupName      name of the group
          * @param permissionMask permission mask to be applied to the Channel/Queue
          * @return new nStorePermission instance
          * @throws nIllegalArgumentException if an invalid or empty group name is passed
          * @since 9.12
          */
          DLL static nStorePermission* createForGroup(std::string group_name, longlong permission_mask);
          /**
          * Creates a new nStorePermission object for teh supplied user@host and the given permission mask.
          *
          * @param user           name of the user
          * @param host           name of the host
          * @param permissionMask permission mask to be applied to the Channel/Queue
          * @return new nStorePermission instance
          * @throws nIllegalArgumentException if an invalid or empty user or host is passed
          * @since 9.12
          */
          DLL static nStorePermission* createForUser(std::string user, std::string host, longlong permission_mask);
          /**
          * Creates a new nStorePermission object for teh supplied user@host and the given permission mask.
          *
          * @param subject        String in the form user@host
          * @param permissionMask permission mask to be applied to the Channel/Queue
          * @return new nStorePermission instance
          * @throws nIllegalArgumentException if an invalid subject is passed
          * @since 9.12
          */
          DLL static nStorePermission* createForUser(std::string subject, longlong permission_mask);
          /* Destructor */
          DLL ~nStorePermission();
          /* Copy constructor */
          DLL nStorePermission(const nStorePermission& permission);
          /**
          * Checks whether the current instance containing information about the permissions
          * to be set on a Queue/Channel has been created for a group or for a single user.
          *
          * @return <code>true</code> if the permission entry has been created for a group,
          * <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool isGroup();
          /**
          * Returns the complete subject in the format user@host. In case a group permission is created, the name of the group
          * is returned.
          *
          * @return String representation of the subject
          * @since 9.12
          */
          DLL std::string getSubject();
          /**
          * Returns the name of the group or the user for this permission entry.
          *
          * @return group or user name
          * @since 9.12
          */
          DLL std::string getName();
          /**
          * Returns the host name for which the permission entry has been created. In case a group permission is created
          * <code>null</code> is returned.
          *
          * @return the name of the host
          * @since 9.12
          */
          DLL std::string getHost();
          /**
          * Returns the permissions to be applied on a Channel/Queue as long.
          *
          * @return permission mask to be set on a Channel/Queue
          * @since 9.12
          */
          DLL longlong getPermissions();
          /**
          * Checks whether the specified user has permission to add and remove other permissions.
          *
          * @return <code>true</code> if the user has manage permissions, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool canManage();
          /**
          * Checks whether the specified user can purge events from the Queue/Channel.
          *
          * @return <code>true</code> if the user has purge permission, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool canPurge();
          /**
          * Checks whether the specified user has permission to access last event id. This is applicable only for Channels.
          *
          * @return <code>true</code> if the user can access last event id, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool canGetLastEventId();
          /**
          * Checks whether the specified user has permission to write to a destination. Write permission is equivalent
          * to publish for a Channel and push for a Queue respectively.
          *
          * @return <code>true</code> if the user has permission to write, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool canWrite();
          /**
          * Checks whether the specified user has permission to read from a destination. Read permission is equivalent
          * to subscribe for a Channel and peek for a Queue respectively.
          *
          * @return <code>true</code> if the user has permission to read, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool canRead();
          /**
          * Checks whether the specified user has permission to pop from a Queue. This is applicable only for Queues.
          *
          * @return <code>true</code> if the user can pop events, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool canPop();
          /**
          * Checks whether the specified user has permission to to use named subscription. This is applicable only for Channels.
          *
          * @return <code>true</code> if the user is authorized to use named subscriptions, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool canUseNamedSubscription();
          /**
          * Checks whether the specified user has full privileges for the Queue/Channel.
          *
          * @return <code>true</code> if the user has full privileges set, <code>false</code> otherwise
          * @since 9.12
          */
          DLL bool hasFullPrivileges();

        protected:
          static std::vector<nBaseStorePermission>* getBaseStorePermissions(const std::vector<nStorePermission>& permissions, int destination_type);
          void validateUsage(int destination_type) const;
          nBaseStorePermission* store_permission;

        private:
          nStorePermission(std::string user, std::string host, longlong permission_mask);
          nStorePermission(std::string name, longlong permission_mask, bool is_group);

          friend class nSession;
        };
      }
    }
  }
}