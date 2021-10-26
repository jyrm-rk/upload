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

#include <string>
#include <stdio.h>
#include "Exception.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
/**
 * This exception forms the base for all client exceptions
 */
class DLL nBaseClientException :
    public com::pcbsys::foundation::fbase::Exception {
  public:
    /**
     * Creates the exception with the specified message
     *
     * @param msg Message string
     */
    nBaseClientException(std::string msg);

    virtual int getType();
    virtual std::string getTypeString();

    static const int SECURITYEXCEPTION = 1000;
    static const int SESSIONNOTCONNECTEDEXCEPTION = 1001;
    static const int SESSIONALREADYINITIALISEDEXCEPTION = 1002;
    static const int REALMUNREACHABLEEXCEPTION = 1003;
    static const int ILLEGALARGUMENTEXCEPTION = 1004;
    static const int SESSIONPAUSEDEXCEPTION = 1005;
    static const int REQUESTTIMEDOUTEXCEPTION = 1006;
    static const int ILLEGALCHANNELMODE = 1007;
    static const int CHANNELNOTFOUNDEXCEPTION = 1008;
    static const int UNKNOWNREMOTEREALMEXCEPTION = 1009;
    static const int CHANNELALREADYSUBSCRIBED = 1010;
    static const int SELECTORPARSEREXCEPTION = 1011;
    static const int TRANSACTIONNOSUCHTXIDEXCEPTION = 1012;
    static const int CHANNELALREADYEXISTSEXCEPTION = 1013;
    static const int REALMNOTFOUNDEXCEPTION = 1014;
    static const int NAMEALREADYBOUNDEXCEPTION = 1015;
    static const int NAMEDOESNOTEXISTEXCEPTION = 1016;
    static const int DUPLICATEJOINEXCEPTION = 1017;
    static const int NAMESPACECONFLICTEXCEPTION = 1018;
    static const int REALMINUSEEXCEPTION = 1019;
    static const int REALMEXCEEDEDLIMITEXCEPTION = 1020;
    static const int REALMALREADYBOUNDEXCEPTION = 1021;
    static const int USERNOTSUBSCRIBED = 1022;
    static const int UNEXPECTEDRESPONSEEXCEPTION = 1023;
	static const int PUBLISHPAUSEDEXCEPTION = 1024;
	static const int MASTERREDIRECTEXCEPTION = 1025;

};

}
}
}
}
