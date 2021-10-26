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

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {

using namespace com::pcbsys::foundation::fbase;

class MergeManager {
  public:
    MergeManager(void);
    virtual ~MergeManager(void);

    virtual void deleted(Object *pObj) = 0;
    virtual void added(Object *pObj) = 0;
    virtual void merge(Object *pOriginal, Object *pNewObj) = 0;
};

}
}
}
}
