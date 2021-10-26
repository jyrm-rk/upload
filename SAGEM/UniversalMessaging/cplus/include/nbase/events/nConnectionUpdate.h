/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nCachedChannelAttributes.h"

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fSubject;
}
}
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;
namespace events {

using namespace com::pcbsys::foundation::security;

class nConnectionUpdate :
    public nCachedChannelAttributes {
  public:
    nConnectionUpdate(void);
    virtual ~nConnectionUpdate(void);



    /*nConnectionUpdate(nBaseChannelAttributes* attrib, std::string protocol, std::string Id, fSubject* subject, std::string selector, std::string javaVer="", std::string osVer="", std::string osName="", std::string buildName="", std::string buildDate="");

    nConnectionUpdate(nBaseChannelAttributes* attrib, std::string protocol, std::string Id, fSubject* subject, std::string selector, std::string name, std::string javaVer, std::string osVer, std::string osName, std::string buildName, std::string buildDate);

    nConnectionUpdate(nBaseChannelAttributes* attrib, std::string Id, bool clientClosed) ;

    nConnectionUpdate(nBaseChannelAttributes* attrib, std::string Id, std::string name, bool clientClosed);
    */

    std::string getJavaVersion();

    std::string getOSVersion();

    std::string getOSName();

    std::string getBuildName();

    std::string getBuildDate();

    bool isMulticastEnabled();

    bool requirePriorityConnection();

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    int getState();
    fSubject* getSubject();
    std::string getConnectionId();
    std::string getSelector();
    std::string getProtocol();
    std::string getName();

    static const int add = 0;
    static const int del = 1;
    static const int close = 2;
  protected:
    std::string* myAttributes;
    int myAttributesLen;
    bool _isMulticastEnabled;
    bool _requirePriorityConnection;

  private:
    int m_state;
    fSubject *m_pSubject;
    std::string m_id;
    std::string m_selector;
    std::string m_protocol;
    std::string m_name;


    const static int sJavaVersion = 0;
    const static int sOSVersion = 1;
    const static int sOSName = 2;
    const static int sBuildName = 3;
    const static int sBuildDate = 4;
};

}
}
}
}
}
