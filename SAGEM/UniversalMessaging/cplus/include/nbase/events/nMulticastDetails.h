/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NMULTICASTDETAILS_H
#define NMULTICASTDETAILS_H

#include "nSynchronous.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
namespace drivers {
namespace configuration {
class fMulticastConfig;
}
}
}
namespace nirvana {
namespace nbase {
namespace events {
using namespace com::pcbsys::foundation::drivers::configuration;
using namespace com::pcbsys::foundation::io;

class nMulticastDetails : public nSynchronous {

  private:
    short myStreamId;
    std::string myLocalIPAddress;
    unsigned char myCommand;

    fMulticastConfig* myConfig;

    longlong myResourceId;

  public:
    static const unsigned char sAdd = 1;
    static const unsigned char sDelete = 2;
    static const unsigned char sRemove = 3;
    static const unsigned char sPing = 4;
    static const unsigned char sInsync = 5;

    nMulticastDetails();

    nMulticastDetails(short streamId, fMulticastConfig* cfg, std::string localIPAddress);

    nMulticastDetails(short streamId, unsigned char command);

    nEvent* createInstance();

    short getStreamId();

    void setCommand(unsigned char val);

    unsigned char getCommand();

    longlong getResourceId();

    void setResourceId(longlong id);

    void setStreamId(short myStreamId);

    fMulticastConfig* getConfig();

    void setConfig(fMulticastConfig* config);

    std::string getLocalIPAddress();

    void setLocalIPAddress(std::string myLocalIPAddress);

    void performWrite(fEventOutputStream* oos);

    void performRead(fEventInputStream* ois);

    ~nMulticastDetails();

    int getType();
    const std::string getTypeString();


};
}
}
}
}
}
#endif
