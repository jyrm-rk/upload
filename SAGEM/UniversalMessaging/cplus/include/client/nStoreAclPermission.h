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
#include "nAclPermission.h"

/*
Classes representing various permissions that can be set from the client while creating queues and channels.
*/
namespace com {
  namespace pcbsys {
    namespace nirvana {
      namespace client {
        class DLL nPermission {
        public:
          /*
          Grants permissions for managing acl entires for the store.
          */
          static const int MANAGE_ACL;
          /*
          Grants full privileges on the store if set.
          */
          static const int FULL_PRIVILEGE;
          /*
          Grants permissions to purge from the store if set.
          */
          static const int PURGE;
        };

        class DLL nChannelPermission : public nPermission {
        public:
          /*
          Grants permissions to publish to a channel.
          */
          static const int PUBLISH;
          /*
          Grants permissions to subscribe to a channel.
          */
          static const int SUBSCRIBE;
          /*
          Grants permissions for getting last event id from a channel.
          */
          static const int LAST_EID;
          /*
          Grants permissions for using named subscription on a channel.
          */
          static const int NAMED;
        };

        class DLL nQueuePermission : public nPermission {
        public:
          /*
          Grants permissions to push events to a queue.
          */
          static const int PUSH;
          /*
          Grants permissions to peek events from a queue.
          */
          static const int PEEK;
          /*
          Grants permissions to pop from a queue.
          */
          static const int POP;
        };
      }
    }
  }
}