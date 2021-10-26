/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NDELETECHANNELS_H
#define NDELETECHANNELS_H

#include "nBaseBatchedChannel.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

class nDeleteChannels : public nBaseBatchedChannel {

  public:
    nEvent* createInstance();

    nDeleteChannels();

    nDeleteChannels(std::vector<fExternalable*>* channels);

    fExternalable* getRequestAttribute();

    int getType();

    const std::string getTypeString();

}; // End of nMakeChannel Class
}
}
}
}
}

#endif
