/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */

#include "fBase.h"
#include <vector>

/**
* Class responsible for generating the permission mask to be applied to a Queue/Channel.
*/
namespace com {
  namespace pcbsys {
    namespace nirvana {
      namespace client {
        class nStorePermissionGenerator {
        public:
          /**
          * Generates the permission mask from the vector of the specified permissions.
          *
          * @param permission vector
          * @return the generated permission mask
          * @since 9.12
          */
          DLL static longlong getStorePermissions(std::vector<int>& permissions);
        };
      }
    }
  }
}