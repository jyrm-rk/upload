/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

/*
Class with constants representing the bit which is toggled in the permission mask in case the corresponding permission is granted. 
The values are mapped to the ones used by the server, if reordered the received results might not be correct.
*/
namespace com {
  namespace pcbsys {
    namespace nirvana {
      namespace nbase {
        class nAclPermission {
        public: 
          static const int ADD_ACL = 0;
          static const int REMOVE_ACL = 1;
          static const int LIST_ACL = 2;
          static const int ACL_FULL = 3;
          static const int CHANNEL_PUB = 5;
          static const int CHANNEL_SUB = 6;
          static const int CHANNEL_PURGE = 7;
          static const int CHANNEL_LAST_EID = 9;
          static const int CHANNEL_POP = 10;
          static const int CHANNEL_NAMED = 11;
        };
      }
    }
  }
}