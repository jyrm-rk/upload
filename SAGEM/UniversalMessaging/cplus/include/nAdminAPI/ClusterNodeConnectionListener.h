/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nAPIConnectionListener.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nClusterNode;

class ClusterNodeConnectionListener :
    public nAPIConnectionListener {
  public:
    ClusterNodeConnectionListener(nClusterNode *pCl);
    virtual ~ClusterNodeConnectionListener(void);

    virtual void add(nConnectionDetails *pCd);
    virtual void del(nConnectionDetails *pCd);

  private:
    nClusterNode *m_pCluster;
};

}
}
}
}
