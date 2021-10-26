/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nBaseClientException;
}
namespace nbase {

using namespace client;

class nExceptionFactory {
  public:
    nExceptionFactory(void);
    virtual ~nExceptionFactory(void);

    static nBaseClientException *getException(const int id, const std::string& msg);
	static void throwException(const int id, const std::string& msg);

    static const int nChannelNotFound = 0;
    static const int nUnknownBaseRealm = 1;
    static const int nChannelAlreadyExists = 2;
    static const int nBaseRealmAlreadyBound = 3;
    static const int nBaseRealmNotReachable = 4;
    static const int nBaseRealmNotFound = 5;
    static const int nUserAlreadySubscribed = 6;
    static const int nSelectorParser = 7;
    static const int nUserNotSubscribed = 8;
    static const int nExceededLimit = 9;
    static const int nTransactionNoSuchTXID = 10;
    static const int nNameSpaceConfict = 11;
    static const int nDuplicateJoin = 12;
    static const int nNamedBound = 13;
    static const int nNameDoesNotExist = 14;
    static const int nSchedulerGrammer = 15;
    static const int nBaseRealmInUse = 16;
    static const int nClusterNotReady = 17;
    static const int nIllegalChannelMode = 18;
    static const int disconnected = 19;
    static const int reconnected = 20;
    static const int tryAgain = 21;
    static const int nIllegalArgument = 22;
    static const int sessionPaused = 23;
    static const int sessionNotConnected = 24;
    static const int nSecurity = 25;
    static const int nUnexpected = 26;
    static const int nRequestTimedOut = 27;
    static const int nSessionAlreadyInitialised = 28;
    static const int nIllegalState = 29;
    static const int nTransaction = 30;
    static const int nTransactionIncomplete = 31;
    static const int nDataGroupDeleted = 32;
    static const int nDataGroupReadOnly = 33;
	static const int nZoneAlreadyExistsException = 34;
	static const int nZoneDoesNotExistException = 35;
  static const int nPermissionException = 37;
  static const int nPublishPaused = 39;
  static const int nMasterRedirect = 40;
};

}
}
}
}
