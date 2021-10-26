/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NDATASTREAMNODE
#define NDATASTREAMNODE

#include "nNode.h"
#include "nDataGroupNode.h"
#include "nDataStream.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nDataStream;
}
namespace nAdminAPI {
class nDataGroupNode;
using namespace client;

/**
 * This class is an Admin API wrapper for a Data Stream object (nDataStream)
 *
 * @see nDataStream
 */
class nDataStreamNode : public nNode {

  public:
    /**
     * Get the nDataStream client API object
     *
     * @return the nDataStream object
     */
    DLL nDataStream* getDataStream();

    nDataStreamNode(nDataStream* stream, nDataGroupNode* group);

  protected:
    nDataStream* myStream;


};
}
}
}
}

#endif
