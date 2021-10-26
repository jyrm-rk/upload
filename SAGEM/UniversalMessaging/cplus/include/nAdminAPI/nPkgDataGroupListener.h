/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NPKGDATAGROUPLISTENER
#define NPKGDATAGROUPLISTENER

#include "nDataGroupListener.h"
#include "nDataGroupNode.h"
#include "nDataStreamNode.h"
#include "Poco/SynchronizedObject.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nDataGroupListener;
class nDataGroup;
class nDataStream;
}
namespace nAdminAPI {
class nDataGroupNode;
class nDataStreamNode;
class nDataGroupsContainer;
using namespace client;

class nPkgDataGroupListener : public nDataGroupListener, public Poco::SynchronizedObject {
  public:
    nPkgDataGroupListener();

    void setContainer(nDataGroupsContainer* cont);

    void addDataGroup(nDataGroupNode* node);

    void addedStream(nDataGroup* group, nDataStream* stream, int count);

    void deletedStream(nDataGroup* group, nDataStream* stream, int count, bool serverRemoved);

    void createdGroup(nDataGroup* group);

    void addedGroup(nDataGroup* to, nDataGroup* group, int count);

    void removedGroup(nDataGroup* from, nDataGroup* group, int count);

    void deletedGroup(nDataGroup* group);

    nDataGroupNode* getDataGroup(longlong id);

  private:
    void doRemove(nDataGroup* from, nDataGroup* group);
    nDataGroupsContainer* myContainer;
    std::map<longlong,nDataGroupNode*> *myDataGroups;

};
}
}
}
}
#endif
