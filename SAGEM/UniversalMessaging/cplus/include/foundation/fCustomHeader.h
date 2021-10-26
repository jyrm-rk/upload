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
#include "fEventOutputStream.h"
#include "fEventInputStream.h"

using namespace com::pcbsys::foundation::io;
using namespace std;

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {

class fCustomHeader {

  public:
    fCustomHeader();

    fCustomHeader(std::string key, std::string value, std::string userAgents);

    std::string getMyKey();

    std::string getMyValue();

    std::string getMyUserAgents();

    void setMyValue(std::string myValue);


    void setMyUserAgents(std::string userAgents);


    void writeExternal(fEventOutputStream* eos);

    void readExternal(fEventInputStream* eis);

  private:
    std::string myKey;
    std::string myValue;
    std::string myUserAgents;

};

}
}
}
}
}
