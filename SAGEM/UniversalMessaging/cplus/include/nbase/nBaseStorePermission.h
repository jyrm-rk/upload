/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nAclPermission.h"
#include "nIllegalArgumentException.h"
#include "Poco/Exception.h"
#include "fBase.h"
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>

using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::nirvana::client;
using namespace com::pcbsys::foundation::fbase;


namespace com {
  namespace pcbsys {
    namespace nirvana {
      namespace nbase {
        class nBaseStorePermission {
        public:
          nBaseStorePermission(std::string user, std::string host, longlong permission_mask);
          nBaseStorePermission(std::string name, longlong permission_mask, bool is_group);
          nBaseStorePermission(std::string name, longlong permission_mask, bool is_group, bool validate);
          ~nBaseStorePermission();
          nBaseStorePermission();
          nBaseStorePermission(const nBaseStorePermission& permission);
          bool isGroup();
          std::string getSubject();
          std::string getName();
          std::string getHost();
          long getPermissions();
          bool canManage();
          bool canPurge();
          bool canGetLastEid();
          bool canWrite();
          bool canRead();
          bool canPop();
          bool canUseNamedSubscription();
          bool hasFullPrivileges();

        private:
          bool checkBit(int bitIndex);
          void validateUserHost(std::string user, std::string host);
          void validateMask(longlong mask);
          void validateSubjectFormat(std::string subject);
          void init(std::string name, longlong permission_mask, bool is_group, bool validate);

          std::string user;
          std::string host;
          bool is_group;
          longlong permission_mask;
        };
      }
    }
  }
}